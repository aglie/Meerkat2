//
// Created by Arkadiy on 12/04/2017.
//

#ifndef MEERKAT2_HDF5HELPERFUNCITONS_H
#define MEERKAT2_HDF5HELPERFUNCITONS_H

#include <H5Cpp.h> //for reading HDF5
#include "misc.h"
#include <string>
#include <assert.h>
#include <array>

using namespace H5;

template<typename T>
DataType getH5Type() {}

template<>
DataType getH5Type<int> ();
template<>
DataType getH5Type<float> ();
template<>
DataType getH5Type<bool> ();
template<>
DataType getH5Type<double> ();
template<>
DataType getH5Type<size_t> ();

template <typename T>
void creadeAndWriteDataset(H5File& file, string datasetName, T* data, hsize_t n, hsize_t* dims) {
    DataSpace dataspace( n, dims );
    DataSet dataset = file.createDataSet( datasetName, getH5Type<T>(), dataspace );
    dataset.write( data, getH5Type<T>() );
}

template <typename T>
void creadeAndWriteDataset(H5File& file, string datasetName, vector<T> data, hsize_t n, hsize_t* dims) {
    DataSpace dataspace( n, dims );
    DataSet dataset = file.createDataSet( datasetName, getH5Type<T>(), dataspace );
    dataset.write( data.data(), getH5Type<T>() );
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

void writeVector(H5File& file, string datasetName, vec3 v);

void writeYellFormatString(H5File& file);


template<typename A>
vector<A> readVector(H5File& f, const string& datasetName) {
    DataSet dataset = f.openDataSet(datasetName);

    DataSpace dataspace = dataset.getSpace();

    hsize_t datasetSize = dataspace.getSimpleExtentNpoints();

    std::vector<A> out(datasetSize);
    dataset.read( out.data(), getH5Type<A>());

    return out;
}

vector<size_t> getDatasetDimensions(H5File& f, const string& datasetName);

#endif //MEERKAT2_HDF5HELPERFUNCITONS_H

