//
// Created by Arkadiy Simonov on 03.10.2024.
//

#ifndef MEERKAT2_ABSTRACTIMAGELOADER_H
#define MEERKAT2_ABSTRACTIMAGELOADER_H

#include <vector>
#include <string>
#include "ReconstructionParameters.h"

class AbstractImageLoader {
public:
    explicit AbstractImageLoader(const ReconstructionParameters & par);
    virtual ~AbstractImageLoader() = default;

    virtual bool load_next_frame() = 0;
    inline bool should_reconstruct(size_t x, size_t y) {
        return should_reconstruct(xy2index(x,y));
    };

    inline bool should_reconstruct(size_t ind) {
        if(mask_is_defined)
            return (current_frame(ind) >= 0) && mask[ind];
        else
            return current_frame(ind) >= 0;
    }

    inline corrected_frame_dt current_frame(size_t x, size_t y) {
        return data[xy2index(x, y)];
    };

    inline corrected_frame_dt current_frame(size_t ind) {
        return data[ind];
    }

    void initialize_buffers() {
        data = vector<int> (m_dim1*m_dim2);
        buffer = vector<int> (m_dim1*m_dim2);
    }

    int ny() const { return m_dim1; }
    int nx() const { return m_dim2; }
    int current_frame_no() const { return current_frame_number; }

    void load_mask(string mask_filename);

protected:
    virtual void load_frame_to_buffer() = 0;

    size_t frame_increment;
    size_t m_dim1, m_dim2;
    int current_frame_number, last_frame_number;
    std::vector<int> data;
    std::vector<int> buffer;
    std::vector<int> mask;
    bool mask_is_defined;
    std::string filename_template;

    inline size_t xy2index(size_t x,size_t y) {
        return x * ny() + y;
    }
};

#endif //MEERKAT2_ABSTRACTIMAGELOADER_H
