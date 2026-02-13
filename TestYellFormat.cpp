//
// Created by Arkadiy Simonov on 07.07.21.
//

#include "OutputData.h"
#include "ReconstructionParameters.h"
#include <algorithm>
#include "hdf5_write.c"

int main(int argc, char* argv[]) {

//    ReconstructionParameters params;
//
//    for(int i=0; i<3; ++i) {
//        params.number_of_pixels[i] = 50;
//        params.lower_limits[i] = -1;
//        params.step_sizes[i] = 2./50;
//        params.exp.cell[i] = 1;
//        params.exp.cell[i+3] = 90;
//    }
//
//    OutputData temp(params);
//    for(int i = 0; i<params.number_of_pixels[0]; ++i)
//        for(int j = 0; j<params.number_of_pixels[1]; ++j)
//            for(int k = 0; k<params.number_of_pixels[2]; ++k) {
//                temp.rebinned_data_at(i,j,k) = 10;
//                temp.no_pixels_rebinned_at(i,j,k) = 10;
//            }
//
//    temp.save_data("temp.h5", params);


    char* outfile = "test.h5";
    hsize_t hdims[3] = {50,50,50};
    double values[50][50][50];
    short is_direct = false;
    double llims[3] = {-1,-1,-1};
    double steps[3] = {2./50,2./50,2./50};
    double unit_cell[6] = {1,1,1,90,90,90};


    for(int i = 0; i<hdims[0]; ++i)
        for(int j = 0; j<hdims[1]; ++j)
            for(int k = 0; k<hdims[2]; ++k) {
                values[i][j][k] = i;
            }

    hdf5_write_discus(outfile, 0, 3, hdims,
                           values,
                           &is_direct, llims, steps,
                           unit_cell);
}