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
#include "CBFDataReader.h"


ImageLoader::ImageLoader(ReconstructionParameters par) :
    current_frame_number(par.first_image),
    filename_template (par.data_filename_template),
    last_frame_number (par.last_image),
    frame_increment(par.frame_increment)
{
    //get file size

    CBFDataReader first_frame(current_frame_filename());
    current_frame_number-=frame_increment;

    //allocate memory
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
                CBFDataReader frame(format_template(filename_template, current_frame_number + frame_increment));
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
    current_frame_number+=frame_increment;
    if (current_frame_number > last_frame_number)
        return false;

    next_frame_f.get();
    swap_a_for_b(data, buffer);

    if (current_frame_number+frame_increment <= last_frame_number)
        load_frame_to_buffer();

    return true;
}

corrected_frame_dt ImageLoader::current_frame(size_t x, size_t y) {
    return data[x * ny() + y];
}


