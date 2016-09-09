//
// Created by Arkadiy on 09/09/2016.
//

#include <iostream>
#include <set>
#include "ReconstructionParameters.h"

ReconstructionParameters load_experimental_parameters(string filename) {
    //should load the data from XPARM.XDS or GXPARM.XDS
    //also check the invisible areas on XDS, and load those
    //Also check ascii hkl and load those, figuring out the limits
    //Or maybe figure out the limits from the measured dataset limits??
}


template<class T>
bool isIn(const T& target, const std::set<T>& the_set)
{
    return the_set.find(target) != the_set.end();
}

const set<string> known_xds_formats = {" XPARM.XDS    VERSION Jun 17, 2015", " XPARM.XDS    VERSION Oct 15, 2015", " XPARM.XDS    VERSION May 1, 2016  BUILT=20160617"};

void load_xparm(string filename, ExperimentalParameters & r) {
    ifstream in(filename);

    if(!in)
        throw FileNotFound(filename);

    getline(in, r.format);
    if(!isIn(r.format,known_xds_formats))
        cout << "Warning: unknown version of XPARM.XDS file. This version has not been tested yet, use Meerkat at your own risk.\n";


    in >> r.starting_frame >> r.starting_angle >> r.oscillation_angle >>
    r.oscillation_axis[0] >> r.oscillation_axis[1] >> r.oscillation_axis[2] >>
    r.wavelength >> r.wavevector[0] >> r.wavevector[1] >> r.wavevector[2] >>
    r.space_group_nr >> r.cell[0]>> r.cell[1]>> r.cell[2]>> r.cell[3]>> r.cell[4]>> r.cell[5] >>
    r.cell_vectors[0][0] >> r.cell_vectors[0][1] >> r.cell_vectors[0][2] >>
    r.cell_vectors[1][0] >> r.cell_vectors[1][1] >> r.cell_vectors[1][2] >>
    r.cell_vectors[2][0] >> r.cell_vectors[2][1] >> r.cell_vectors[2][2] >>
    // We are changing x and y directions because xds uses fortran array notations, while we use C
    r.number_of_detector_segments >> r.NY >> r.NX  >> r.pixel_size_y >> r.pixel_size_x >>
    r.y_center >> r.x_center >> r.distance_to_detector >>
    r.detector_y[0] >> r.detector_y[1] >> r.detector_y[2] >>
    r.detector_x[0] >> r.detector_x[1] >> r.detector_x[2] >>
    r.detector_normal[0] >> r.detector_normal[1] >> r.detector_normal[2];

    for (int i=0; i<5; ++i)
        in >> r.detector_segment_crossection[i];
    for (int i=0; i<9; ++i)
        in >> r.detector_segment_geometry[i];
}

ReconstructionParameters load_refinement_parameters(string filename) {
    //ReconstructionParameters exp = load_xparm("/Users/arkadiy/ag/data/GdFe77Si13/xds/XPARM.XDS");
    ifstream in(filename);

    if(!in)
        throw FileNotFound(filename);

    ReconstructionParameters par;
    bool symmetric_limits = false;

    string keyword;
    while(!in.eof()) {
        in >> keyword;
        if (keyword[0] == '!') {
            getline(in, keyword);
            continue;
        }

        if (keyword == "DATA_FILE_TEMPLATE")
            in >> par.data_filename_template;
        else if (keyword == "FIRST_FRAME")
            in >> par.first_image;
        else if (keyword == "LAST_FRAME")
            in >> par.last_image;
        else if (keyword == "NUMBER_OF_PIXELS")
            in >> par.number_of_pixels[0] >> par.number_of_pixels[1] >> par.number_of_pixels[2];
        else if (keyword == "LOWER_LIMITS")
            in >> par.lower_limits[0] >> par.lower_limits[1] >> par.lower_limits[2];
        else if (keyword == "STEP_SIZES")
            in >> par.step_sizes[0] >> par.step_sizes[1] >> par.step_sizes[2];
        else if (keyword == "SYMMETRIC_LIMITS")
            symmetric_limits = true;
        else if (keyword == "OUTPUT_FILENAME")
            in >> par.output_filename;
        else if (keyword == "XPARM_FILE")
            in >> par.xparm_filename;
        else if (keyword == "POLARIZATION_PLANE_NORMAL")
            in >> par.exp.polarization_plane_normal[0] >> par.exp.polarization_plane_normal[1] >> par.exp.polarization_plane_normal[2]; //should probably come from xds.inp. Will break encapsulation of exp otherwise
            //In general, should input file be able to override any of the parameters from XPARM.XDS? Should they be clearly separated?
            // TODO: decide the above
        else if (keyword == "POLARIZATION_FACTOR")
            in >> par.exp.polarization_factor;
        else {
            cout << "Error: Unknown keyword " << keyword;
            terminate();
        }
    }
    if (symmetric_limits)
        for (int i = 0; i < 3; ++i)
            par.step_sizes[i] = -par.lower_limits[i] * 2 / par.number_of_pixels[i];

    par.reconstruct_in_orthonormal_basis = false;
    par.override = true;
    par.size_of_cache = 100;

    cout << "Reconstructing frames: " << par.data_filename_template << endl;
    cout << "Using frames from " << par.first_image << " till " << par.last_image << endl;
    cout << "Output array name: " << par.output_filename;
    cout << "Output array dimensions: " << par.number_of_pixels[0] << " " << par.number_of_pixels[1]
    << " " << par.number_of_pixels[2] << endl;
    cout << "In the limits ";
    for (int i=0; i<3; ++i)
        cout << par.lower_limits[i] << ' ' << par.lower_limits[i]+(par.step_sizes[i]-1)*par.step_sizes[i] << ' ';
    cout << endl << endl;

    return par;
}