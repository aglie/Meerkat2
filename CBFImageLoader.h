//
// Created by Arkadiy Simonov on 03.10.2024.
//

#ifndef MEERKAT2_CBFIMAGELOADER_H
#define MEERKAT2_CBFIMAGELOADER_H

#include <future>
#include "AbstractImageLoader.h"
#include "CBFDataReader.h"


class CBFImageLoader : public AbstractImageLoader {
public:
    CBFImageLoader(ReconstructionParameters par);
    bool load_next_frame() override;

protected:
    void load_frame_to_buffer() override;

private:
    std::future<void> next_frame_f;

    string current_frame_filename() {
        return format_template(filename_template, current_frame_number);
    }
};


#endif //MEERKAT2_CBFIMAGELOADER_H
