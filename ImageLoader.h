//
// Created by Arkadiy on 20/03/2016.
//

#ifndef MEERKAT2_IMAGELOADER_H
#define MEERKAT2_IMAGELOADER_H


#include <future>
#include "misc.h"
#include "cbf.h"
#include "ReconstructionParameters.h"


class CBFError : std::exception {
public:
    CBFError(int code, string filename): code(code), filename(filename) {}
    ~CBFError() throw() {}
    int code;
    string filename;
};

#define throws_cbf_errors(x) {int err; err = (x); if (err) throw CBFError(err,filename());}

class CBFFile {
public:
    CBFFile(string filename);
    size_t dim1() {return m_dim1;}
    size_t dim2() {return m_dim2;}
    size_t dim3() {return m_dim3;}
    void read_data(int* out);
    ~CBFFile();

    string filename() {return m_filename;};

private:
    string m_filename;
    size_t m_dim1, m_dim2, m_dim3;

    cbf_handle incbf = NULL;
    FILE *in;
};

class ImageLoader {

public:
    ImageLoader(ReconstructionParameters par);
    bool load_next_frame();
    bool should_reconstruct(size_t x, size_t y) {return current_frame(x,y) >= 0;}
    corrected_frame_dt current_frame(size_t,size_t);

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
    string filename_template;
    string current_frame_filename() {
        return format_template(filename_template, current_frame_number);
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
