//
// Created by Arkadiy Simonov on 03.10.2024.
//

#include "AbstractImageLoader.h"
#include "Hdf5HelperFuncitons.h"

AbstractImageLoader::AbstractImageLoader(const ReconstructionParameters & par) {
    filename_template = par.data_filename_template;
    frame_increment = par.frame_increment;
    last_frame_number = par.last_image;
    current_frame_number = par.first_image;
}

void AbstractImageLoader::load_mask(string mask_filename) {
    if(mask_filename != "") {
        // load mask
        if(!file_exists(mask_filename)) {
            throw FileNotFound(mask_filename);
        }

        H5File file(mask_filename, H5F_ACC_RDONLY);
        auto sz = getDatasetDimensions(file, "data");
        if(sz[0]!=m_dim2 || sz[1]!=m_dim1) {
            std::stringstream message;
            message << "Error: incorrect mask dimensions. Expected " << m_dim1 << "x" << m_dim2 << " found " << sz[0] <<"x" << sz[1] << "." << endl;
            throw MaskError(message.str());
        }
        mask = readVector<int>(file, "data");
        mask_is_defined = true;
    }
}