//
// Created by Arkadiy Simonov on 02.10.2024.
//

#include "HDFDataReader.h"
#include "H5Cpp.h"

using namespace H5;

#include <stdexcept>
#include <iostream>
#include <filesystem>

//TODO: delete this once everything works
//std::pair<std::string, std::string> parseHDF5FilenameAndDataset(const std::string& filename_and_dataset) {
//    size_t colonPos = filename_and_dataset.find(':');
//    if (colonPos == std::string::npos) {
//        throw std::invalid_argument("Invalid filename and dataset format. Expected 'filename.h5:/dataset'");
//    }
//
//    std::string filename = filename_and_dataset.substr(0, colonPos);
//    std::string dataset_name = filename_and_dataset.substr(colonPos + 1);
//
//    return std::make_pair(filename, dataset_name);
//}

#include "H5PLextern.h"
#include "bitshuffle/bitshuffle.h"
#include "bitshuffle/bshuf_h5filter.h"



HDFDataReader::HDFDataReader(string filename, string dataset_name) :
    m_filename(filename), m_dataset_name(dataset_name) {

    // Check if file exists
    if (!std::filesystem::exists(filename)) {
        std::cerr << "Error: File does not exist: " << filename << std::endl;
        throw std::runtime_error("File not found");
    }



// Read in the files
    try {

        /*
 * Similarly, check for availability of the shuffle filter.
 */
        auto avail = H5Zfilter_avail(H5Z_FILTER_SHUFFLE);
        if (!avail) {
            std::cout << "Shuffle filter not available.\n";
        }

        in = H5File(filename, H5F_ACC_RDONLY);
        dataset = in.openDataSet(dataset_name);

        // If we reach here, file and dataset were opened successfully
        std::cout << "Successfully opened file: " << filename << " and dataset: " << dataset_name << std::endl;

        // Perform your operations with the file and dataset here

        /*
  * Get dataspace of the dataset.
  */
        DataSpace dataspace = dataset.getSpace();
/*
 * Get the number of dimensions in the dataspace.
 */
        int rank = dataspace.getSimpleExtentNdims();

        assert(rank==3);
/*
 * Get the dimension size of each dimension in the dataspace and
 * display them.
 */
        hsize_t dims_in[3];
        int ndims = dataspace.getSimpleExtentDims( dims_in, NULL);
        assert(ndims == 3);

        m_no_frames = dims_in[0], m_dim1 = dims_in[1], m_dim2 = dims_in[2];

    } catch (H5::FileIException& file_error) {
        std::cerr << "Error opening file: " << filename << std::endl;
        std::cerr << "Error details: " << file_error.getDetailMsg() << std::endl;
        throw std::runtime_error("HDF5 file error");
    } catch (H5::DataSetIException& dataset_error) {
        std::cerr << "Error opening dataset: " << dataset_name << " in file: " << filename << std::endl;
        std::cerr << "Error details: " << dataset_error.getDetailMsg() << std::endl;
        throw std::runtime_error("HDF5 dataset error");
    } catch (H5::Exception& hdf5_error) {
        std::cerr << "An HDF5 error occurred while processing file: " << filename << std::endl;
        std::cerr << "Error details: " << hdf5_error.getDetailMsg() << std::endl;
        throw std::runtime_error("HDF5 error");
    } catch (std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
        throw;
    }


}

void HDFDataReader::read_frame(int frame_no, int* out) {
    DataSpace dataspace = dataset.getSpace();

/*
 * Define hyperslab in the dataset; implicitly giving stride and
 * block NULL.
 */
    hsize_t      offset[3];   // hyperslab offset in the file
    hsize_t      count[3];    // size of the hyperslab in the file
    offset[0] = frame_no;
    offset[1] = 0;
    offset[2] = 0;
    count[0]  = 1;
    count[1]  = dim1();
    count[2]  = dim2();
    dataspace.selectHyperslab( H5S_SELECT_SET, count, offset );

/*
 * Define the memory dataspace.
 */
    hsize_t     dimsm[2];              /* memory space dimensions */
    dimsm[0] = dim1();
    dimsm[1] = dim2();
    DataSpace memspace( 2, dimsm );

/*
 * Define memory hyperslab.
 */
    hsize_t      offset_out[2];   // hyperslab offset in memory
    hsize_t      count_out[2];    // size of the hyperslab in memory
    offset_out[0] = 0;
    offset_out[1] = 0;
    count_out[0]  = dim1();
    count_out[1]  = dim2();
    memspace.selectHyperslab( H5S_SELECT_SET, count_out, offset_out );

    /*
     * Read data from hyperslab in the file into the hyperslab in
     * memory and display the data.
     */
    dataset.read( out, PredType::NATIVE_INT32, memspace, dataspace );
}


