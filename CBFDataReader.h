//
// Created by Arkadiy on 16/09/2016.
//

#ifndef MEERKAT2_CBFFILE_H
#define MEERKAT2_CBFFILE_H

#include "misc.h"
#include "cbf.h"

#define throws_cbf_errors(x) {int err; err = (x); if (err) throw CBFError(err,filename());}

class CBFError : exception {
public:
    CBFError(int code, string filename): code(code), filename(filename) {}
    ~CBFError() throw() {}
    int code;
    string filename;
};

class CBFDataReader {
public:
    CBFDataReader(string filename);
    size_t dim1() {return m_dim1;}
    size_t dim2() {return m_dim2;}
    size_t dim3() {return m_dim3;}
    void read_data(int* out);
    ~CBFDataReader();

    string filename() {return m_filename;};

private:
    string m_filename;
    size_t m_dim1, m_dim2, m_dim3;

    cbf_handle incbf = NULL;
    FILE *in;
};

#endif //MEERKAT2_CBFFILE_H
