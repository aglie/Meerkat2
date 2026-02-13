//
// Created by Arkadiy on 09/09/2016.
//

#ifndef MEERKAT2_EXPERIMENTALPARAMETERS_H
#define MEERKAT2_EXPERIMENTALPARAMETERS_H

#include "misc.h"

struct ExperimentalParameters {
    string format;
    size_t starting_frame;
    float starting_angle, oscillation_angle;
    vec3 oscillation_axis;
    float wavelength;
    vec3 wavevector;
    size_t space_group_nr;
    vec6 cell;
    matrix_3x3 cell_vectors;
    size_t number_of_detector_segments;
    size_t NX,NY;
    float pixel_size_x,pixel_size_y,x_center, y_center, distance_to_detector;
    vec3 detector_x, detector_y, detector_normal;

    float detector_segment_crossection[5];
    float detector_segment_geometry[9];

    vec3 polarization_plane_normal;
    float polarization_factor;
    string detector;
    float detector_thickness;

    ExperimentalParameters() :
            polarization_plane_normal(0, 1, 0),
            polarization_factor(0.5)
    {}
};

struct ReconstructionParameters {
    string mask_filename;
    string data_filename_template;
    string hdf5_dataset_name;
    string xparm_filename;
    size_t first_image;
    size_t last_image;
    size_t number_of_pixels[3];
    reciprocal_fractional_t lower_limits[3];
    reciprocal_fractional_t step_sizes[3];
    reciprocal_fractional_t inv_step_sizes[3];
    bool reconstruct_in_orthonormal_basis;
    //measured_pixels in some format - missing in the baseline
    size_t microsteps[3];
    size_t frame_increment;
    //unit_cell_transform_matrix=np.eye(3) //missing in baseline

    string output_filename;
    size_t size_of_cache;

    ReconstructionParameters() :
            data_filename_template(""),
            xparm_filename(""),
            hdf5_dataset_name(""),
            output_filename(""),
            mask_filename(""),
            first_image(1),
            last_image(numeric_limits<size_t>::max()),
            number_of_pixels{701,701,701},
            lower_limits{NAN,NAN,NAN},
            step_sizes{NAN,NAN,NAN},
            reconstruct_in_orthonormal_basis{false},
            size_of_cache{100},
            microsteps{1,1,1},
            frame_increment{1}
    {}

    ExperimentalParameters exp;

//    microsteps = microsteps[2]
//    if microsteps < 1:
//    image_increment = 1 / microsteps
//    assert (np.mod(image_increment, 1) == 0)
//    microsteps = 1
//    else:
//    image_increment = 1

//    output_filename='reconstruction.h5',
//    size_of_cache=100,
//    all_in_memory=False,
//    override=False,
//    scale=None):

};


struct ContextAroundPosition {
    string lines_before;
    string current_line;
    string lines_after;
    int pos_within_current_line;
    int line_number;
    string context;
};


bool operator== (const ContextAroundPosition& a, const ContextAroundPosition& b);

ContextAroundPosition get_context(istream& in);

void load_xparm(string filename, ExperimentalParameters & r);

ReconstructionParameters load_refinement_parameters(string filename);

#endif //MEERKAT2_EXPERIMENTALPARAMETERS_H
