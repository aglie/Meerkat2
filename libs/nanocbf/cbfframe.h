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

//todo: rename CbfFrame -> CBFFrame
//TODO: width, height, headers -> interface?? just to be able to work with an interface later???
//TODO: do I need overload over some datatypes?
//TODO: might be useful to just read headers without reding the data itself, thought not soooo important


#ifndef CBFFRAME_H
#define CBFFRAME_H

#include <vector>
#include <string>
#include <cstdint>

namespace nanocbf {

class CbfFrame {
public:
    CbfFrame();
    CbfFrame(const std::string &filename);
    ~CbfFrame();
    
    // Read CBF file
    bool read(const std::string& filename);
    
    // Write CBF file
    bool write(const std::string& filename) const;
    
    // Get error message
    const std::string& getError() const { return m_error; }
    
    // Public accessible fields
    std::string header;         // User-provided header content (everything after data_filename section)
    std::vector<int32_t> data;  // 1D vector of pixel data
    int width;
    int height;
    
private:
    static const std::vector<uint8_t> CBF_MAGIC;
    static const std::string CBF_TAIL;
    
    std::string m_error;
    
    // Binary data compression/decompression
    std::vector<uint8_t> compressData(const std::vector<int32_t>& data) const;
    std::vector<int32_t> decompressData(const std::vector<uint8_t>& compressed, int width, int height) const;
    
    // Utility functions
    void writeInt16LE(std::vector<uint8_t>& buffer, int16_t value) const;
    void writeInt32LE(std::vector<uint8_t>& buffer, int32_t value) const;
    uint16_t readInt16LE(const uint8_t* buffer) const;
    uint32_t readInt32LE(const uint8_t* buffer) const;
    
    // Parse binary header info from text header
    bool parseBinaryInfo(const std::string& header, int& width, int& height, int& dataSize) const;
    
    // Generate the _array_data.data section with binary metadata
    std::string generateArrayDataSection(const std::vector<uint8_t>& compressedData) const;
    
    // Generate CBF header prefix with version and data section name
    std::string generateCbfPrefix(const std::string& filename) const;
    
    // Generate minimal default header if user header is empty
    std::string generateDefaultHeader() const;
    
    // Extract filename without extension and path
    std::string extractBaseName(const std::string& filepath) const;
    
    // Generate MD5 hash
    std::string generateMD5(const std::vector<uint8_t>& data) const;
    
    // MD5 implementation helper functions
    static std::string bytesToHex(const uint8_t* bytes, size_t length);
    static std::string bytesToBase64(const uint8_t* bytes, size_t length);
    static void md5Transform(uint32_t state[4], const uint8_t block[64]);
    static void md5Update(uint32_t state[4], uint64_t& count, uint8_t buffer[64], const uint8_t* input, size_t length);
    static void md5Final(uint8_t digest[16], uint32_t state[4], uint64_t count, uint8_t buffer[64]);
};

} // namespace nanocbf

#endif // CBFFRAME_H