//
// Created by Arkadiy on 21/03/2016.
//

#include "OutputData.h"
#include "Hdf5HelperFuncitons.h"
#include <H5Cpp.h>
using namespace H5;

/// WARNING: Ruins the dataset. Should only be used before quitting the program.
void OutputData::save_data(string filename, ReconstructionParameters par) {
    for(size_t i=0; i<no_elements(); ++i)
        rebinned_data[i]/=no_pixels_rebinned[i];

    //TODO: if rewrite flag - remove previous file
    H5File file( filename, H5F_ACC_TRUNC );

    hsize_t s[] = {size[0], size[1], size[2]};
    creadeAndWriteDataset<float>(file, "data", rebinned_data, 3, s);

    // Write out the grid settings
    writeVector<reciprocal_fractional_t,3> (file, "lower_limits", par.lower_limits);
    writeConstant<int>(file, "is_direct", 0);
    writeVector<reciprocal_fractional_t,3>(file, "step_sizes", par.step_sizes);
    writeVector<float,6> (file, "unit_cell", par.exp.cell);
    writeYellFormatString(file);
}