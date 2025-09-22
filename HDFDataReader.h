//
// Created by Arkadiy Simonov on 02.10.2024.
//

#ifndef MEERKAT2_HDFDATAREADER_H
#define MEERKAT2_HDFDATAREADER_H

#include <string>
#include "H5Cpp.h"

using std::string;

class HDFDataReader {
public:
    HDFDataReader(string filename, string dataset_name);
    size_t dim1() {return m_dim1;}
    size_t dim2() {return m_dim2;}
    size_t no_frames() {return m_no_frames;}
    void read_frame(int frame_no, int* out);
    ~HDFDataReader() {

    }

    string filename() {return m_filename;};
    string dataset_name() {return m_dataset_name;}

private:
    string m_filename;
    string m_dataset_name;
    size_t m_dim1, m_dim2, m_no_frames;

    H5::H5File in;
    H5::DataSet dataset;
};


#endif //MEERKAT2_HDFDATAREADER_H
