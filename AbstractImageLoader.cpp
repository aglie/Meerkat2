//
// Created by Arkadiy Simonov on 03.10.2024.
//

#include "AbstractImageLoader.h"

#include "Hdf5HelperFuncitons.h"

AbstractImageLoader::AbstractImageLoader(ReconstructionParameters par) {
    if(par.mask_filename != "") {
        // load mask
        if(!file_exists(par.mask_filename)) {
            throw FileNotFound(par.mask_filename);
        }

        H5File file(par.mask_filename, H5F_ACC_RDONLY);
        auto sz = getDatasetDimensions(file, "data");
        if(sz[0]!=m_dim2 || sz[1]!=m_dim1) {
            std::stringstream message;
            message << "Error with input mask dimensions. Expected " << m_dim1 << "x" << m_dim2 << " found " << sz[0] <<"x" << sz[1] << "." << endl;
            throw MaskError(message.str());
        }
        mask = readVector<int>(file, "data");
        mask_is_defined = true;
    }
}