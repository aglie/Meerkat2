//
// Created by Arkadiy on 20/03/2016.
//

#include <assert.h>
#include <regex>
#include <iomanip>
#include <sstream>
#include <future>
#include <iostream>
#include "ImageLoader.h"
#include "cbf.h"

CBFFile::CBFFile(string filename) {

    size_t numread, nelem, elsize;

    unsigned int compression;

    int id, elsigned, elunsigned, maxel, minel;

    int i, j, k;

    /* Read the input test file */

    if (!(in = fopen(filename.c_str(), "rb")))
        throw FileNotFound(filename);


    const char *byteorder;

    size_t padding;

    throws_cbf_errors(cbf_make_handle(&incbf));
    throws_cbf_errors(cbf_read_file(incbf, in, MSG_DIGEST));
    throws_cbf_errors(cbf_rewind_datablock(incbf));
    throws_cbf_errors(cbf_rewind_category(incbf));
    throws_cbf_errors(cbf_find_column(incbf, "data"));
    throws_cbf_errors(cbf_rewind_row(incbf));

    throws_cbf_errors (cbf_get_integerarrayparameters_wdims(incbf, &compression, &id, &elsize, &elsigned,
                                                      &elunsigned, &nelem, &maxel, &minel, &byteorder, &m_dim1, &m_dim2,
                                                      &m_dim3, &padding))

//    fprintf(stderr, "testflat: element size %ld, element signed %d, element unsigned %d\n",
//            (long) elsize, elsigned, elunsigned);
//    fprintf(stderr, "testflat: byte order %s, dimensions %ld, %ld, padding %ld\n",
//            byteorder, (long) dim1, (long) dim2, (long) padding);
//
//    if (compression != CBF_BYTE_OFFSET)
//        fprintf(stderr, "testflat: Compression %x instead of CBF_BYTE_OFFSET\n", compression);
//
//    if (elsize != sizeof(int))
//        fprintf(stderr, "testflat: element size %ld instead of %d\n", (long) elsize, (int) sizeof(int));

}
void CBFFile::read_data(int* out) {
    size_t numread;
    throws_cbf_errors (cbf_get_integerarray(incbf, NULL,
                                            out, sizeof(int), 0,
                                            dim1()*dim2(), &numread))

    if (numread != dim1()*dim2()) throw CBFError(10000);
}

CBFFile::~CBFFile() {
    throws_cbf_errors (cbf_free_handle (incbf));
//    fclose(in);
}

ImageLoader::ImageLoader(ExperimentalParameters exp, ReconstructionParameters par) :
    current_frame_number(par.first_image),
    filename_template (par.data_filename_template),
    last_frame_number (par.last_image)
{
    // Get cbflib
    // build it
    // find example of loading a cbf file data header (I will need data size from it to initialize)
    // find example of loading cbf data
    // put it all together
    // run
    // pass tests
    // make function filetemplate -> filename
    // put it all together

    //check all the needed files exist
    //get file size
    //allocate memory
    CBFFile first_frame(current_frame_filename());
    --current_frame_number;

    m_dim1=first_frame.dim1();
    m_dim2=first_frame.dim2();

    data = (int *)malloc(sizeof(int)*m_dim1*m_dim2);
    buffer = (int *)malloc(sizeof(int)*m_dim1*m_dim2); //Tick-tock buffer.
    // One way to increase speed would be to read and reconstruct several images at a time
    // possibly it will be cool to shuffle bytes by staggering them together along z??? or actually it should not.

    load_frame_to_buffer();
}

void ImageLoader::load_frame_to_buffer() {
    next_frame_f = async(launch::async, //async|deferred
            [=](int current_frame_number)
            {
                CBFFile frame(format_template(filename_template, current_frame_number+1));
                assert(frame.dim1() == ny() and frame.dim2() == nx());
                frame.read_data(buffer);
    }, current_frame_number);
}

template <typename T>
void swap_a_for_b(T& a, T& b) {
    T t=a;
    a=b;
    b=t;
}

bool ImageLoader::load_next_frame() {
    if (++current_frame_number > last_frame_number)
        return false;

    next_frame_f.get();
    swap_a_for_b(data, buffer);

    if (current_frame_number+1 <= last_frame_number)
        load_frame_to_buffer();

    return true;
}

corrected_frame_dt ImageLoader::current_frame(size_t x, size_t y) {
    return data[x * ny() + y];
}

/// Replaces ??? in the format file with the image number. Example whatever???.cbf, 2 -> whatever002.cbf
string ImageLoader::format_template(string format, size_t N) {
    smatch m;
    regex r("\\?+");

    assert(regex_search (format, m, r));

    ostringstream formatted_n;
    formatted_n << setfill('0') << setw(m[0].length()) << N;

    return regex_replace(format, r, formatted_n.str());
}
