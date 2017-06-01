//
// Created by Arkadiy on 12/04/2017.
//

#include "Hdf5HelperFuncitons.h"

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

void writeVector(H5File& file, string datasetName, vec3 v) {
    writeVector<float,3>(file, datasetName, v.data);
}

void writeYellFormatString(H5File& file) {
    string format = "Yell 1.0";

    H5::StrType h5stringType(H5::PredType::C_S1, H5T_VARIABLE); // + 1 for trailing zero
    H5::DataSet ds = file.createDataSet("format", h5stringType, H5::DataSpace(H5S_SCALAR));
    ds.write(format, h5stringType);
}

vector<size_t> getDatasetDimensions(H5File& f, const string& datasetName) {
    DataSet dataset = f.openDataSet(datasetName);

    DataSpace dataspace = dataset.getSpace();
    int rank = dataspace.getSimpleExtentNdims();

    hsize_t rawDimensions[rank];

    dataspace.getSimpleExtentDims(rawDimensions);

    vector<size_t> res(rank, 0);

    for(int i=0; i<rank; ++i)
        res[i]=rawDimensions[i];

    return res;
}