//
// Created by Arkadiy on 20/03/2016.
//

#ifndef MEERKAT2_IMAGELOADER_H
#define MEERKAT2_IMAGELOADER_H


#include <future>
#include "misc.h"
#include "ReconstructionParameters.h"


class ImageLoader {
public:
    ImageLoader(ReconstructionParameters par);
    bool load_next_frame();
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

    ~ImageLoader() {
        free(data);
        free(buffer);
    }
    int ny() {return m_dim1;}
    int nx() {return m_dim2;}
    int curernt_frame_no() {return current_frame_number;}

private:
    size_t frame_increment;
    void load_frame_to_buffer();
    future<void> next_frame_f;
    size_t  m_dim1, m_dim2;
    int current_frame_number, last_frame_number;
    int * data;
    int * buffer;
    vector<int> mask;
    bool mask_is_defined;
    string filename_template;
    string current_frame_filename() {
        return format_template(filename_template, current_frame_number);
    }

    inline size_t xy2index(size_t x,size_t y) {
        return x * ny() + y;
    }


    //#TODO: maybe add scale 'median' where scale is defined as a median of a frame divided by a median of a first frame?
//    if scale is None:
//    scale = np.ones(last_image-first_image+1)
//    else:
//    assert(len(scale)==last_image-first_image+1)

// Should apply instrumental corrections (possibly later absorption correction)

//    corrections = correction_coefficients(h, instrument_parameters, medium, polarization_factor,
//                                          polarization_plane_normal, wavelength, wavevector)
};


#endif //MEERKAT2_IMAGELOADER_H
