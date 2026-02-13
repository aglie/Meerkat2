//
// Created by Arkadiy Simonov on 03.10.2024.
//

#include "HDFImageLoader.h"
#include <memory>

HDF5ImageLoader::HDF5ImageLoader(ReconstructionParameters par) :
    AbstractImageLoader(par), reader(par.data_filename_template, par.hdf5_dataset_name) {

    current_frame_number-=frame_increment;

    //allocate memory
    m_dim1=reader.dim1();
    m_dim2=reader.dim2();
    initialize_buffers();

    load_frame_to_buffer();
}

bool HDF5ImageLoader::load_next_frame() {
    //TODO: here if there are no frames in the file, increment file number

    current_frame_number+=frame_increment;
    if (current_frame_number > last_frame_number)
        return false;

    if(!next_frame_f.valid())
        load_frame_to_buffer();

    next_frame_f.get();
    std::swap(data, buffer);

    if (current_frame_number + frame_increment <= last_frame_number)
        load_frame_to_buffer();

    return true;
}

void HDF5ImageLoader::load_frame_to_buffer() {
    next_frame_f = async(launch::async, //async|deferred
                         [=](int current_frame_number)
                         {
                             reader.read_frame(current_frame_number, buffer.data());
                         }, current_frame_number);
}