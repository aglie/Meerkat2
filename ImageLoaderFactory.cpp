//
// Created by Arkadiy Simonov on 03.10.2024.
//

#include "ImageLoaderFactory.h"
#include "CBFImageLoader.h"
#include "HDFImageLoader.h"
#include <filesystem>
#include <memory>

std::unique_ptr<AbstractImageLoader> createImageLoader(ReconstructionParameters par) {
    std::string extension = std::filesystem::path(par.data_filename_template).extension().string();
    if (extension == ".cbf") {
        return std::make_unique<CBFImageLoader>(par);
        // return NULL;
    } else if (extension == ".h5" || extension == ".hdf5") {
        return std::make_unique<HDF5ImageLoader>(par);
    } else {
        throw std::runtime_error("Unsupported file type: " + extension);
    }
}