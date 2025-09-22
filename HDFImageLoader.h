//
// Created by Arkadiy Simonov on 03.10.2024.
//

#ifndef MEERKAT2_HDFIMAGELOADER_H
#define MEERKAT2_HDFIMAGELOADER_H

#include "AbstractImageLoader.h"
#include "HDFDataReader.h"

#include <future>


class HDF5ImageLoader : public AbstractImageLoader {
public:
    HDF5ImageLoader(ReconstructionParameters par);
    bool load_next_frame() override;

protected:
    void load_frame_to_buffer() override;

private:
    HDFDataReader reader;
    std::future<void> next_frame_f;
};

#endif //MEERKAT2_HDFIMAGELOADER_H
