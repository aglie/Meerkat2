//
// Created by Arkadiy on 21/03/2016.
//

#include "OutputData.h"
#include <H5Cpp.h> //for reading HDF5
using namespace H5;

template<typename T>
DataType getH5Type() {}

template<>
DataType getH5Type<int> () {
    return PredType::NATIVE_INT;
}
template<>
DataType getH5Type<float> () {
    return PredType::NATIVE_FLOAT;
}
template<>
DataType getH5Type<bool> () {
    return PredType::NATIVE_HBOOL;
}
template<>
DataType getH5Type<double> () {
    return PredType::NATIVE_DOUBLE;
}
template<>
DataType getH5Type<size_t> () {
    return PredType::NATIVE_UINT;
}

template <typename T>
void creadeAndWriteDataset(H5File& file, string datasetName, T* data, hsize_t n, hsize_t* dims) {
    DataSpace dataspace( n, dims );
    DataSet dataset = file.createDataSet( datasetName, getH5Type<T>(), dataspace );
    dataset.write( data, getH5Type<T>() );
}

template <typename T>
void writeConstant(H5File& file, string datasetName, T data) {
    H5::DataSet ds = file.createDataSet(datasetName, getH5Type<T>(), H5::DataSpace(H5S_SCALAR));
    ds.write(&data, getH5Type<T>());
}

template<typename T, std::size_t N>
void writeVector(H5File& file, string datasetName, T* v) {
    hsize_t sz[]={N};
    creadeAndWriteDataset<T>(file, datasetName, v, 1, sz);
}

void writeVector(H5File& file, string datasetName, vec3 v) {
    writeVector<float,3>(file, datasetName, v.data);
}

void writeFormatString(H5File& file) {
    string format = "Yell 1.0";

    H5::StrType h5stringType(H5::PredType::C_S1, H5T_VARIABLE); // + 1 for trailing zero
    H5::DataSet ds = file.createDataSet("format", h5stringType, H5::DataSpace(H5S_SCALAR));
    ds.write(format, h5stringType);
}

// Ruins the dataset. Should only be used before quitting the program.
void OutputData::save_data(string filename, ReconstructionParameters par, ExperimentalParameters exp) {
    for(size_t i=0; i<no_elements(); ++i)
        rebinned_data[i]/=no_pixels_rebinned[i];

    //TODO: if rewrite flag - remove previous file
    H5File file( filename, H5F_ACC_TRUNC );

    hsize_t s[] = {size[0],size[1],size[2]};
    creadeAndWriteDataset<float>(file, "data", rebinned_data, 3, s);

    // Write out the grid settings
    writeVector<reciprocal_fractional_t,3> (file, "lower_limits", par.lower_limits);
    writeConstant(file, "is_direct", false);
    writeVector<reciprocal_fractional_t,3>(file, "step_sizes", par.step_sizes);
    writeVector<float,6> (file, "unit_cell", exp.cell);
    writeFormatString(file);
}