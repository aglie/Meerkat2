//
// Created by Arkadiy on 21/03/2016.
//

#ifndef MEERKAT2_OUTPUTDATA_H
#define MEERKAT2_OUTPUTDATA_H


#include "misc.h"

class OutputData {
public:
    OutputData(ReconstructionParameters par) :
            size{par.number_of_pixels[0],par.number_of_pixels[1],par.number_of_pixels[2]}
    {
        size_t N = no_elements();
        rebinned_data = (out_float_number*) malloc(sizeof(out_float_number)*N);
        no_pixels_rebinned = (size_t*) malloc(sizeof(size_t)*N);
    }
    out_float_number& rebinned_data_at(int hi, int ki, int li) {return rebinned_data[hkli2i(hi,ki,li)];}
    size_t& no_pixels_rebinned_at(int hi, int ki, int li) {return no_pixels_rebinned[hkli2i(hi,ki,li)];}
    void save_data(string filename, ReconstructionParameters par,  ExperimentalParameters exp);
    ~OutputData() {
        free(rebinned_data);
        free(no_pixels_rebinned);
    }
    size_t no_elements() {return size[0]*size[1]*size[2];}
private:
    out_float_number* rebinned_data;
    size_t* no_pixels_rebinned;
    size_t size[3];
    int hkli2i(int hi, int ki, int li) {return (hi*size[1]+ki)*size[2]+li;}

    // This is in simplest implementation is simply a NxMxL dataset
    // Should allow to hold running sum of rebinned data and the number of pixels rebinned
    // Parameterise over double or float, and different versions of INTS once we willl run in a situation
    // when ints are not enough for reconstruction (possible?)

    // Should know how to export results in an hdf5 file
    // writing the reconstruction parameters

    // In a fancier version should dynamically allocate data to save a bit of operating memory
    // on the regions which are not reconstructed
    // (are modulo operations here visibly slow??
};



#endif //MEERKAT2_OUTPUTDATA_H
