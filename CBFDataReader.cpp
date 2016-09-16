//
// Created by Arkadiy on 16/09/2016.
//

#include "misc.h"
#include "CBFDataReader.h"

CBFDataReader::CBFDataReader(string inp_filename) : m_filename(inp_filename) {

    size_t numread, nelem, elsize;

    unsigned int compression;

    int id, elsigned, elunsigned, maxel, minel;


    /* Read the input test file */
    if (!(in = fopen(filename().c_str(), "rb")))
        throw FileNotFound(filename());


    const char *byteorder;

    size_t padding;


    throws_cbf_errors(cbf_make_handle(&incbf));
    throws_cbf_errors(cbf_read_file(incbf, in, MSG_DIGEST));
    throws_cbf_errors(cbf_rewind_datablock(incbf));
    throws_cbf_errors(cbf_rewind_category(incbf));
    throws_cbf_errors(cbf_find_column(incbf, "data"));
    throws_cbf_errors(cbf_rewind_row(incbf));

    throws_cbf_errors (cbf_get_integerarrayparameters_wdims(incbf, &compression, &id, &elsize, &elsigned,
                                                      &elunsigned, &nelem, &maxel, &minel, &byteorder, &m_dim1, &m_dim2,
                                                      &m_dim3, &padding))
}

void CBFDataReader::read_data(int* out) {
    size_t numread;
    throws_cbf_errors (cbf_get_integerarray(incbf, NULL,
                                            out, sizeof(int), 0,
                                            dim1()*dim2(), &numread))

    if (numread != dim1()*dim2()) throw CBFError(10000, filename());
}

CBFDataReader::~CBFDataReader() {
    throws_cbf_errors (cbf_free_handle (incbf));
//    fclose(in);
}