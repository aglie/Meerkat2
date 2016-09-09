//
// Created by Arkadiy on 11/03/2016.
//

#include <iostream>
#include "misc.h"
#include "Geometry.h"

ExperimentalParameters load_experimental_parameters(string filename) {
    //should load the data from XPARM.XDS or GXPARM.XDS
    //also check the invisible areas on XDS, and load those
    //Also check ascii hkl and load those, figuring out the limits
    //Or maybe figure out the limits from the measured dataset limits??
}


ExperimentalParameters load_xparm(string filename) {
    ifstream in(filename);

    if(!in)
        throw FileNotFound(filename);

    ExperimentalParameters r;

    getline(in, r.format);
    if(r.format!=" XPARM.XDS    VERSION Jun 17, 2015" and r.format!=" XPARM.XDS    VERSION Oct 15, 2015")
        throw UnknownFormat();


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

    return r;
}


struct EnergyAttenuationLine {
    float energy, attenuation;
};

struct MaterialAttenuationParameters {
    float density;
    vector<EnergyAttenuationLine> mass_attenuation_coefficients;
};

const MaterialAttenuationParameters air_attenuation_params = {
    1.205e-03,
    {{1.00000e-03, 3.606e+03},
     {1.50000e-03, 1.191e+03},
     {2.00000e-03, 5.279e+02},
     {3.00000e-03,1.625e+02},
     {3.20290e-03,1.340e+02},
     {3.20290e-03, 1.485e+02},
     {4.00000e-03, 7.788e+01},
     {5.00000e-03, 4.027e+01},
     {6.00000e-03, 2.341e+01},
     {8.00000e-03, 9.921e+00},
     {1.00000e-02, 5.120e+00},
     {1.50000e-02, 1.614e+00},
     {2.00000e-02, 7.779e-01},
     {3.00000e-02, 3.538e-01},
     {4.00000e-02, 2.485e-01},
     {5.00000e-02, 2.080e-01},
     {6.00000e-02, 1.875e-01},
     {8.00000e-02, 1.662e-01},
     {1.00000e-01, 1.541e-01},
     {1.50000e-01, 1.356e-01},
     {2.00000e-01, 1.233e-01},
     {3.00000e-01, 1.067e-01},
     {4.00000e-01, 9.549e-02},
     {5.00000e-01, 8.712e-02},
     {6.00000e-01, 8.055e-02},
     {8.00000e-01, 7.074e-02},
     {1.00000e+00, 6.358e-02},
     {1.25000e+00, 5.687e-02},
     {1.50000e+00, 5.175e-02},
     {2.00000e+00, 4.447e-02},
     {3.00000e+00, 3.581e-02},
     {4.00000e+00, 3.079e-02},
     {5.00000e+00, 2.751e-02},
     {6.00000e+00, 2.522e-02},
     {8.00000e+00, 2.225e-02},
     {1.00000e+01, 2.045e-02},
     {1.50000e+01, 1.810e-02},
     {2.00000e+01, 1.705e-02}}
};
const MaterialAttenuationParameters silicon_attenuation_params = {
    2.33,
   {{1.00000E-03, 3.606E+03},
    {1.50000E-03, 1.191E+03},
    {2.00000E-03, 5.279E+02},
    {3.00000E-03, 1.625E+02},
    {3.20290E-03, 1.340E+02},
    {3.20290E-03, 1.485E+02},
    {4.00000E-03, 7.788E+01},
    {5.00000E-03, 4.027E+01},
    {6.00000E-03, 2.341E+01},
    {8.00000E-03, 9.921E+00},
    {1.00000E-02, 5.120E+00},
    {1.50000E-02, 1.614E+00},
    {2.00000E-02, 7.779E-01},
    {3.00000E-02, 3.538E-01},
    {4.00000E-02, 2.485E-01},
    {5.00000E-02, 2.080E-01},
    {6.00000E-02, 1.875E-01},
    {8.00000E-02, 1.662E-01},
    {1.00000E-01, 1.541E-01},
    {1.50000E-01, 1.356E-01},
    {2.00000E-01, 1.233E-01},
    {3.00000E-01, 1.067E-01},
    {4.00000E-01, 9.549E-02},
    {5.00000E-01, 8.712E-02},
    {6.00000E-01, 8.055E-02},
    {8.00000E-01, 7.074E-02},
    {1.00000E+00, 6.358E-02},
    {1.25000E+00, 5.687E-02},
    {1.50000E+00, 5.175E-02},
    {2.00000E+00, 4.447E-02},
    {3.00000E+00, 3.581E-02},
    {4.00000E+00, 3.079E-02},
    {5.00000E+00, 2.751E-02},
    {6.00000E+00, 2.522E-02},
    {8.00000E+00, 2.225E-02},
    {1.00000E+01, 2.045E-02},
    {1.50000E+01, 1.810E-02},
    {2.00000E+01, 1.705E-02}}};

const MaterialAttenuationParameters helium_attenuation_params = {
    1.785e-04,
    {{1.00000E-03, 6.084E+01},
    {1.50000E-03, 1.676E+01},
    {2.00000E-03, 6.863E+00},
    {3.00000E-03, 2.007E+00},
    {4.00000E-03, 9.329E-01},
    {5.00000E-03, 5.766E-01},
    {6.00000E-03, 4.195E-01},
    {8.00000E-03, 2.933E-01},
    {1.00000E-02, 2.476E-01},
    {1.50000E-02, 2.092E-01},
    {2.00000E-02, 1.960E-01},
    {3.00000E-02, 1.838E-01},
    {4.00000E-02, 1.763E-01},
    {5.00000E-02, 1.703E-01},
    {6.00000E-02, 1.651E-01},
    {8.00000E-02, 1.562E-01},
    {1.00000E-01, 1.486E-01},
    {1.50000E-01, 1.336E-01},
    {2.00000E-01, 1.224E-01},
    {3.00000E-01, 1.064E-01},
    {4.00000E-01, 9.535E-02},
    {5.00000E-01, 8.707E-02},
    {6.00000E-01, 8.054E-02},
    {8.00000E-01, 7.076E-02},
    {1.00000E+00, 6.362E-02},
    {1.25000E+00, 5.688E-02},
    {1.50000E+00, 5.173E-02},
    {2.00000E+00, 4.422E-02},
    {3.00000E+00, 3.503E-02},
    {4.00000E+00, 2.949E-02},
    {5.00000E+00, 2.577E-02},
    {6.00000E+00, 2.307E-02},
    {8.00000E+00, 1.940E-02},
    {1.00000E+01, 1.703E-02},
    {1.50000E+01, 1.363E-02},
    {2.00000E+01, 1.183E-02}}};

float material_absorption_coefficient(string material, float wavelength) {
    //TODO: add new mediums as needed. In the last years we have never measured in helium

    MaterialAttenuationParameters mat;
    if(material == "Air") {
        mat=air_attenuation_params;
    } else if(material == "Silicon") {
        mat=silicon_attenuation_params;
    }else if(material == "Helium") {
        mat=silicon_attenuation_params;
    }else {
        throw runtime_error("Material is unknown: " + material);
    }

    const float density = mat.density;
    vector<EnergyAttenuationLine> mass_attenuation_coefficients = mat.mass_attenuation_coefficients;

    float etw = 1.23985e-2; //[Mev*Angstroem]
    float photon_energy = etw / wavelength;

    if(photon_energy < begin(mass_attenuation_coefficients)->energy)
        throw ValueOutsideRange();
    auto last = end(mass_attenuation_coefficients) - 1;
    if(photon_energy > last->energy)
        throw ValueOutsideRange();

    //make linear interpolation between nearest points
    auto right = begin(mass_attenuation_coefficients);
    while(right->energy<photon_energy)
        ++right;

    auto left = right - 1;
    auto dE_val = photon_energy - left->energy;
    auto dE_step = right->energy - left->energy;

    auto interpolated_value = (right->attenuation * dE_val + left->attenuation * (dE_step-dE_val))/dE_step;

    return 0.1 * density * interpolated_value;
}

float calculate_correction_coefficient(ExperimentalParameters& experiment, int x, int y) {
/*
 * def correction_coefficients(h, instrument_parameters, medium, polarization_factor, polarization_plane_normal,
                            wavelength, wavevector):

    [_, scattering_vector_mm, unit_scattering_vector] = det2lab_xds(h, 0, **instrument_parameters)
    mu = air_absorption_coefficient(medium, wavelength)
    air_absorption = np.exp(
        -mu * np.sqrt(np.sum(scattering_vector_mm ** 2, axis=0)))  #check along which dimension. should be of size




    polarization_plane_normal = np.array(polarization_plane_normal)
    polarization_plane_normal = polarization_plane_normal / np.linalg.norm(polarization_plane_normal)  # just in case
    polarization_plane_other_comp = np.cross(polarization_plane_normal, wavevector.T)
    polarization_plane_other_comp = polarization_plane_other_comp / np.linalg.norm(polarization_plane_other_comp)
    polarization_correction = (1 - polarization_factor) * (
        1 - np.dot(polarization_plane_normal, unit_scattering_vector) ** 2) + \
                              polarization_factor * (
                                  1 - np.dot(polarization_plane_other_comp, unit_scattering_vector) ** 2)

    #% solid angle correction
    direct_beam_direction = wavevector.T / np.linalg.norm(wavevector)
    solid_angle_correction = np.dot(direct_beam_direction, unit_scattering_vector) ** 3

    corrections = solid_angle_correction * polarization_correction * air_absorption


    return corrections

 */

    auto scattering_vector_mm = real_space_scattering_vector(experiment,x,y);
    auto unit_scattering_vector = scattering_vector_mm.normalized();

    auto mu = material_absorption_coefficient("Air", experiment.wavelength);
    auto air_absorption = exp(-mu * scattering_vector_mm.norm());
    auto polarization_plane_normal=experiment.polarization_plane_normal;
    // A vector perpendicular to polarization plane and the wavevector

    auto polarization_plane_other_comp = polarization_plane_normal.cross(experiment.wavevector).normalized();
    auto polarization_correction =
            (1 - experiment.polarization_factor) * (1 - square(polarization_plane_normal.dot(unit_scattering_vector))) +
            experiment.polarization_factor * (1 - square(polarization_plane_other_comp.dot(unit_scattering_vector)));

    auto cos_detected_ray_angle = abs(experiment.detector_normal.normalized().dot(unit_scattering_vector));
    auto solid_angle_correction = pow(cos_detected_ray_angle,3);

    auto res = solid_angle_correction * polarization_correction * air_absorption;

    if (experiment.detector=="Pilatus") {
        auto ray_len_in_detector = experiment.detector_thickness/cos_detected_ray_angle;
        auto mu_si = material_absorption_coefficient("Silicon", experiment.wavelength);
        auto pilatus_photon_efficiency = 1 - exp(-mu_si * ray_len_in_detector);
        res*=pilatus_photon_efficiency;
    }

    return res;

    //TODO: Get a Bragg datasets for testing the corrections
    //TODO: Get a lot of air scattering from synchrotron to test the corrections
}


ReconstructionParameters load_refinement_parameters(string filename) {
    //ExperimentalParameters exp = load_xparm("/Users/arkadiy/ag/data/GdFe77Si13/xds/XPARM.XDS");
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
