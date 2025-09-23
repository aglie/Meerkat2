/*
 * MIT License
 * 
 * Copyright (c) 2025 Arkadiy Simonov and Vadim Dyadkin
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "cbfframe.h"
#include <fstream>
#include <sstream>
#include <regex>
#include <iomanip>
#include <cstring>

namespace nanocbf {
    // CBF magic number and tail
    const std::vector<uint8_t> CBFFrame::CBF_MAGIC = {0x0C, 0x1A, 0x04, 0xD5};
    const std::string CBFFrame::CBF_TAIL = std::string(4095, '\0') + "\r\n--CIF-BINARY-FORMAT-SECTION----\r\n;\r\n\r\n";

    CBFFrame::CBFFrame() : width(0), height(0) {}
    CBFFrame::CBFFrame(const std::string& filename) : width(0), height(0) {
      read(filename);
    }

    CBFFrame::~CBFFrame() {}

    bool CBFFrame::read(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            m_error = "Could not open file: " + filename;
            return false;
        }

        // Read entire file
        std::vector<uint8_t> fileData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        // Find _array_data.data section (this is where user header should end)
        std::string fileContent(fileData.begin(), fileData.end());
        size_t arrayDataPos = fileContent.find("_array_data.data");
        if (arrayDataPos == std::string::npos) {
            m_error = "Could not find _array_data.data section";
            return false;
        }

        // Find binary format section start
        size_t binaryStartPos = fileContent.find("--CIF-BINARY-FORMAT-SECTION--", arrayDataPos);
        if (binaryStartPos == std::string::npos) {
            m_error = "Could not find --CIF-BINARY-FORMAT-SECTION-- marker";
            return false;
        }

        // Find binary format section end
        size_t binaryEndPos = fileContent.find("--CIF-BINARY-FORMAT-SECTION----", binaryStartPos);
        if (binaryEndPos == std::string::npos) {
            m_error = "Could not find --CIF-BINARY-FORMAT-SECTION---- end marker";
            return false;
        }

        // Extract text header (everything before _array_data.data section)
        // Need to find the actual start of user content (after data_filename section)
        size_t dataPos = fileContent.find("data_");
        if (dataPos == std::string::npos) {
            m_error = "Could not find data_ section";
            return false;
        }

        // Find end of data_filename line
        size_t dataEndPos = fileContent.find("\n", dataPos);
        if (dataEndPos == std::string::npos) {
            m_error = "Could not find end of data_ line";
            return false;
        }

        // Skip the empty line after data_filename
        size_t headerStartPos = dataEndPos + 1;
        while (headerStartPos < fileContent.size() &&
               (fileContent[headerStartPos] == '\r' || fileContent[headerStartPos] == '\n')) {
            headerStartPos++;
        }

        // Extract header from after data section to before _array_data.data
        header = fileContent.substr(headerStartPos, arrayDataPos - headerStartPos);

        // Extract binary section header (between the section markers)
        std::string binaryHeader = fileContent.substr(binaryStartPos, binaryEndPos - binaryStartPos);

        // Parse binary info from binary section header
        int dataSize;
        if (!parseBinaryInfo(binaryHeader, width, height, dataSize)) {
            return false;
        }

        // Find magic number after the binary section header
        auto magicIt = std::search(fileData.begin() + binaryStartPos, fileData.end(), CBF_MAGIC.begin(), CBF_MAGIC.end());
        if (magicIt == fileData.end()) {
            m_error = "Could not find CBF magic number after binary section header";
            return false;
        }

        // Extract binary data (after magic number)
        size_t binaryDataStart = std::distance(fileData.begin(), magicIt) + CBF_MAGIC.size();
        if (binaryDataStart + dataSize > fileData.size()) {
            m_error = "File truncated - not enough binary data";
            return false;
        }

        std::vector<uint8_t> binaryData(fileData.begin() + binaryDataStart, fileData.begin() + binaryDataStart + dataSize);

        // Decompress binary data
        data = decompressData(binaryData, width, height);

        return true;
    }

    bool CBFFrame::write(const std::string& filename) const {
        if (data.empty() || width == 0 || height == 0) {
            return false;
        }

        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return false;
        }

        // Compress binary data first to get size and MD5
        std::vector<uint8_t> compressed = compressData(data);

        // Write CBF prefix (version and data section name)
        std::string cbfPrefix = generateCbfPrefix(filename);
        file.write(cbfPrefix.c_str(), cbfPrefix.size());

        // Write user header or default header if empty
        std::string headerToWrite = header.empty() ? generateDefaultHeader() : header;
        file.write(headerToWrite.c_str(), headerToWrite.size());

        // Generate and write _array_data.data section
        std::string arrayDataSection = generateArrayDataSection(compressed);
        file.write(arrayDataSection.c_str(), arrayDataSection.size());

        // Write magic number
        file.write(reinterpret_cast<const char*>(CBF_MAGIC.data()), CBF_MAGIC.size());

        // Write compressed binary data
        file.write(reinterpret_cast<const char*>(compressed.data()), compressed.size());

        // Write tail
        file.write(CBF_TAIL.c_str(), CBF_TAIL.size());

        return true;
    }


    bool CBFFrame::parseBinaryInfo(const std::string& header, int& width, int& height, int& dataSize) {
        std::regex widthRegex(R"(X-Binary-Size-Fastest-Dimension:\s+(\d+))");
        std::regex heightRegex(R"(X-Binary-Size-Second-Dimension:\s+(\d+))");
        std::regex sizeRegex(R"(X-Binary-Size:\s+(\d+))");
        std::regex md5Regex(R"(Content-MD5:\s+([^\r\n]+))");

        std::smatch match;

        if (!std::regex_search(header, match, widthRegex)) {
            m_error = "Could not find width in header";
            return false;
        }
        width = std::stoi(match[1].str());

        if (!std::regex_search(header, match, heightRegex)) {
            m_error = "Could not find height in header";
            return false;
        }
        height = std::stoi(match[1].str());

        if (!std::regex_search(header, match, sizeRegex)) {
            m_error = "Could not find data size in header";
            return false;
        }
        dataSize = std::stoi(match[1].str());

        // MD5 is optional - some files may not have it
        if (std::regex_search(header, match, md5Regex)) {
            // Store MD5 for potential validation (though we don't validate it currently)
            std::string md5Hash = match[1].str();
            // Could add validation here if needed: validateMD5(md5Hash, binaryData);
        }

        return true;
    }

    std::vector<uint8_t> CBFFrame::compressData(const std::vector<int32_t>& data) const {
        std::vector<uint8_t> compressed;

        int32_t currentValue = 0;
        for (int32_t pixel : data) {
            int32_t delta = pixel - currentValue;

            if (delta >= -127 && delta <= 127) {
                // 8-bit delta
                compressed.push_back(static_cast<uint8_t>(delta));
            } else if (delta >= -32767 && delta <= 32767) {
                // 16-bit delta
                compressed.push_back(0x80);
                writeInt16LE(compressed, static_cast<int16_t>(delta));
            } else {
                // 32-bit delta
                compressed.push_back(0x80);
                writeInt16LE(compressed, static_cast<int16_t>(0x8000));
                writeInt32LE(compressed, delta);
            }

            currentValue = pixel;
        }

        return compressed;
    }

    std::vector<int32_t> CBFFrame::decompressData(const std::vector<uint8_t>& compressed, int width, int height) const {
        std::vector<int32_t> data;
        data.reserve(width * height);

        int32_t currentValue = 0;
        size_t pos = 0;

        while (pos < compressed.size() && data.size() < width * height) {
            int8_t delta8 = static_cast<int8_t>(compressed[pos++]);

            if (static_cast<uint8_t>(delta8) == 0x80) {
                // 16-bit or 32-bit delta
                if (pos + 1 >= compressed.size()) break;

                int16_t delta16 = readInt16LE(&compressed[pos]);
                pos += 2;

                if (static_cast<uint16_t>(delta16) == 0x8000) {
                    // 32-bit delta
                    if (pos + 3 >= compressed.size()) break;

                    int32_t delta32 = readInt32LE(&compressed[pos]);
                    pos += 4;

                    currentValue += delta32;
                } else {
                    currentValue += delta16;
                }
            } else {
                // 8-bit delta
                currentValue += delta8;
            }

            data.push_back(currentValue);
        }

        return data;
    }

    void CBFFrame::writeInt16LE(std::vector<uint8_t>& buffer, int16_t value) const {
        buffer.push_back(static_cast<uint8_t>(value & 0xFF));
        buffer.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
    }

    void CBFFrame::writeInt32LE(std::vector<uint8_t>& buffer, int32_t value) const {
        buffer.push_back(static_cast<uint8_t>(value & 0xFF));
        buffer.push_back(static_cast<uint8_t>((value >> 8) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((value >> 16) & 0xFF));
        buffer.push_back(static_cast<uint8_t>((value >> 24) & 0xFF));
    }

    uint16_t CBFFrame::readInt16LE(const uint8_t* buffer) const {
        return static_cast<uint16_t>(buffer[0]) | (static_cast<uint16_t>(buffer[1]) << 8);
    }

    uint32_t CBFFrame::readInt32LE(const uint8_t* buffer) const {
        return static_cast<uint32_t>(buffer[0]) |
               (static_cast<uint32_t>(buffer[1]) << 8) |
               (static_cast<uint32_t>(buffer[2]) << 16) |
               (static_cast<uint32_t>(buffer[3]) << 24);
    }

    std::string CBFFrame::generateArrayDataSection(const std::vector<uint8_t>& compressedData) const {
        std::string md5Hash = generateMD5(compressedData);

        std::ostringstream oss;
        oss << "_array_data.data\r\n"
            << ";\r\n"
            << "--CIF-BINARY-FORMAT-SECTION--\r\n"
            << "Content-Type: application/octet-stream;\r\n"
            << "     conversions=\"x-CBF_BYTE_OFFSET\"\r\n"
            << "Content-Transfer-Encoding: BINARY\r\n"
            << "X-Binary-Size: " << compressedData.size() << "\r\n"
            << "X-Binary-ID: 1\r\n"
            << "X-Binary-Element-Type: \"signed 32-bit integer\"\r\n"
            << "X-Binary-Element-Byte-Order: LITTLE_ENDIAN\r\n"
            << "Content-MD5: " << md5Hash << "\r\n"
            << "X-Binary-Number-of-Elements: " << (width * height) << "\r\n"
            << "X-Binary-Size-Fastest-Dimension: " << width << "\r\n"
            << "X-Binary-Size-Second-Dimension: " << height << "\r\n"
            << "X-Binary-Size-Padding: 4095\r\n\r\n";

        return oss.str();
    }

    std::string CBFFrame::generateCbfPrefix(const std::string& filename) const {
        std::string baseName = extractBaseName(filename);

        std::ostringstream oss;
        oss << "###CBF: VERSION 1.5 generated by nanocbf\r\n"
            << "data_" << baseName << "\r\n\r\n";

        return oss.str();
    }

    std::string CBFFrame::generateDefaultHeader() const {
        std::ostringstream oss;
        oss << "_array_data.header_convention \"nanocbf empty\"\r\n"
            << "_array_data.header_contents\r\n"
            << ";\r\n"
            << ";\r\n\r\n";

        return oss.str();
    }

    std::string CBFFrame::extractBaseName(const std::string& filepath) const {
        // Find last slash or backslash for directory separation
        size_t lastSlash = filepath.find_last_of("/\\");
        std::string filename = (lastSlash == std::string::npos) ? filepath : filepath.substr(lastSlash + 1);

        // Remove .cbf extension if present
        size_t dotPos = filename.find_last_of('.');
        if (dotPos != std::string::npos && filename.substr(dotPos) == ".cbf") {
            filename = filename.substr(0, dotPos);
        }

        // Replace all whitespace characters with underscores
        for (char& c : filename) {
            if (std::isspace(c)) {
                c = '_';
            }
        }

        return filename;
    }

    // Complete MD5 implementation
    std::string CBFFrame::generateMD5(const std::vector<uint8_t>& data) const {
        // MD5 initialization
        uint32_t state[4] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476};
        uint64_t count = 0;
        uint8_t buffer[64] = {0};

        // Process the data
        md5Update(state, count, buffer, data.data(), data.size());

        // Finalize and get digest
        uint8_t digest[16];
        md5Final(digest, state, count, buffer);

        // Convert to base64 for CBF format
        return bytesToBase64(digest, 16);
    }

    std::string CBFFrame::bytesToHex(const uint8_t* bytes, size_t length) {
        std::ostringstream oss;
        for (size_t i = 0; i < length; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(bytes[i]);
        }
        return oss.str();
    }

    std::string CBFFrame::bytesToBase64(const uint8_t* bytes, size_t length) {
        const char* b64_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
        std::string result;

        for (size_t i = 0; i < length; i += 3) {
            uint32_t chunk = (bytes[i] << 16) |
                            (i + 1 < length ? bytes[i + 1] << 8 : 0) |
                            (i + 2 < length ? bytes[i + 2] : 0);

            result += b64_chars[(chunk >> 18) & 0x3F];
            result += b64_chars[(chunk >> 12) & 0x3F];
            result += (i + 1 < length) ? b64_chars[(chunk >> 6) & 0x3F] : '=';
            result += (i + 2 < length) ? b64_chars[chunk & 0x3F] : '=';
        }

        return result;
    }

    // MD5 round functions
    #define F(x, y, z) ((x & y) | (~x & z))
    #define G(x, y, z) ((x & z) | (y & ~z))
    #define H(x, y, z) (x ^ y ^ z)
    #define I(x, y, z) (y ^ (x | ~z))

    // Rotate left
    #define ROTLEFT(a, b) ((a << b) | (a >> (32 - b)))

    void CBFFrame::md5Transform(uint32_t state[4], const uint8_t block[64]) {
        uint32_t a = state[0], b = state[1], c = state[2], d = state[3];
        uint32_t x[16];

        // Convert block to 32-bit words
        for (int i = 0; i < 16; ++i) {
            x[i] = block[i*4] | (block[i*4+1] << 8) | (block[i*4+2] << 16) | (block[i*4+3] << 24);
        }

        // MD5 round constants
        static const uint32_t k[64] = {
            0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
            0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
            0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
            0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
            0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
            0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
            0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
            0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
        };

        static const int s[64] = {
            7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
            5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
            4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
            6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
        };

        // MD5 main loop
        for (int i = 0; i < 64; ++i) {
            uint32_t f, g;

            if (i < 16) {
                f = F(b, c, d);
                g = i;
            } else if (i < 32) {
                f = G(b, c, d);
                g = (5 * i + 1) % 16;
            } else if (i < 48) {
                f = H(b, c, d);
                g = (3 * i + 5) % 16;
            } else {
                f = I(b, c, d);
                g = (7 * i) % 16;
            }

            f = f + a + k[i] + x[g];
            a = d;
            d = c;
            c = b;
            b = b + ROTLEFT(f, s[i]);
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
    }

    void CBFFrame::md5Update(uint32_t state[4], uint64_t& count, uint8_t buffer[64], const uint8_t* input, size_t length) {
        size_t bufferIndex = count % 64;
        count += length;

        if (bufferIndex + length >= 64) {
            size_t firstChunk = 64 - bufferIndex;
            std::memcpy(buffer + bufferIndex, input, firstChunk);
            md5Transform(state, buffer);

            for (size_t i = firstChunk; i + 64 <= length; i += 64) {
                md5Transform(state, input + i);
            }

            size_t remaining = length - ((length - firstChunk) / 64) * 64 - firstChunk;
            std::memcpy(buffer, input + length - remaining, remaining);
        } else {
            std::memcpy(buffer + bufferIndex, input, length);
        }
    }

    void CBFFrame::md5Final(uint8_t digest[16], uint32_t state[4], uint64_t count, uint8_t buffer[64]) {
        size_t bufferIndex = count % 64;
        buffer[bufferIndex++] = 0x80;

        if (bufferIndex > 56) {
            std::memset(buffer + bufferIndex, 0, 64 - bufferIndex);
            md5Transform(state, buffer);
            bufferIndex = 0;
        }

        std::memset(buffer + bufferIndex, 0, 56 - bufferIndex);

        uint64_t bitCount = count * 8;
        for (int i = 0; i < 8; ++i) {
            buffer[56 + i] = (bitCount >> (i * 8)) & 0xFF;
        }

        md5Transform(state, buffer);

        for (int i = 0; i < 4; ++i) {
            digest[i*4]     = (state[i]) & 0xFF;
            digest[i*4 + 1] = (state[i] >> 8) & 0xFF;
            digest[i*4 + 2] = (state[i] >> 16) & 0xFF;
            digest[i*4 + 3] = (state[i] >> 24) & 0xFF;
        }
    }
}
