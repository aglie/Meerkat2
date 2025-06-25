//
// Created by Arkadiy Simonov on 03.10.2024.
//

#include "CBFImageLoader.h"

#include <assert.h>
#include "CBFDataReader.h"

CBFImageLoader::CBFImageLoader(ReconstructionParameters par) :
        AbstractImageLoader(par)
{
    //get file size
    CBFDataReader first_frame(current_frame_filename());
    current_frame_number-=frame_increment;

    //allocate memory
    m_dim1=first_frame.dim1();
    m_dim2=first_frame.dim2();
    initialize_buffers();
    load_frame_to_buffer();
}

void CBFImageLoader::load_frame_to_buffer() {
    next_frame_f = async(launch::async, //async|deferred
                         [=](int current_frame_number)
                         {
                             CBFDataReader frame(format_template(filename_template, current_frame_number + frame_increment));
                             assert(frame.dim1() == ny() and frame.dim2() == nx());
                             frame.read_data(buffer.data());
                         }, current_frame_number);
}

bool CBFImageLoader::load_next_frame() {
    current_frame_number+=frame_increment;
    if (current_frame_number > last_frame_number)
        return false;

    next_frame_f.get();
    std::swap(data, buffer);

    if (current_frame_number+frame_increment <= last_frame_number)
        load_frame_to_buffer();

    return true;
}


