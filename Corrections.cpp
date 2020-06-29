//
// Created by Arkadiy on 09/09/2016.
//

#include "Corrections.h"

#include "Geometry.h"

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
        {{1.00000E-03, 1.570E+03},
         {1.50000E-03, 5.355E+02},
         {1.83890E-03, 3.092E+02},
         {1.83890E-03, 3.192E+03},
         {2.00000E-03, 2.777E+03},
         {3.00000E-03, 9.784E+02},
         {4.00000E-03, 4.529E+02},
         {5.00000E-03, 2.450E+02},
         {6.00000E-03, 1.470E+02},
         {8.00000E-03, 6.468E+01},
         {1.00000E-02, 3.389E+01},
         {1.50000E-02, 1.034E+01},
         {2.00000E-02, 4.464E+00},
         {3.00000E-02, 1.436E+00},
         {4.00000E-02, 7.012E-01},
         {5.00000E-02, 4.385E-01},
         {6.00000E-02, 3.207E-01},
         {8.00000E-02, 2.228E-01},
         {1.00000E-01, 1.835E-01},
         {1.50000E-01, 1.448E-01},
         {2.00000E-01, 1.275E-01},
         {3.00000E-01, 1.082E-01},
         {4.00000E-01, 9.614E-02},
         {5.00000E-01, 8.748E-02},
         {6.00000E-01, 8.077E-02},
         {8.00000E-01, 7.082E-02},
         {1.00000E+00, 6.361E-02},
         {1.25000E+00, 5.688E-02},
         {1.50000E+00, 5.183E-02},
         {2.00000E+00, 4.480E-02},
         {3.00000E+00, 3.678E-02},
         {4.00000E+00, 3.240E-02},
         {5.00000E+00, 2.967E-02},
         {6.00000E+00, 2.788E-02},
         {8.00000E+00, 2.574E-02},
         {1.00000E+01, 2.462E-02},
         {1.50000E+01, 2.352E-02},
         {2.00000E+01, 2.338E-02}}};

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

float transmission(string material, float wavelength, float path_length) {
    //TODO: add new mediums as needed. In the last years we have never measured in helium

    MaterialAttenuationParameters mat;
    if(material == "Air") {
        mat=air_attenuation_params;
    } else if(material == "Silicon") {
        mat=silicon_attenuation_params;
    }else if(material == "Helium") {
        mat=helium_attenuation_params;
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

    auto mu = 0.1 * density * interpolated_value;

    return exp(-mu*path_length);
}

float calculate_correction_coefficient(ExperimentalParameters & experiment, int x, int y) {
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


// TODO: CHECK THIS: it works differently than in MEERKAT1. it seems correct there not here! Is it possible the polarization plane components get scrumbled somewhere?
    auto air_transmission = transmission("Air", experiment.wavelength, scattering_vector_mm.norm());
    auto polarization_plane_normal=experiment.polarization_plane_normal.normalized();
    // A vector perpendicular to polarization plane and the wavevector

    auto polarization_plane_other_comp = polarization_plane_normal.cross(experiment.wavevector).normalized();
    auto polarization_correction =
            (1 - experiment.polarization_factor) * (1 - square(polarization_plane_normal.dot(unit_scattering_vector))) +
            experiment.polarization_factor * (1 - square(polarization_plane_other_comp.dot(unit_scattering_vector)));

    auto cos_detected_ray_angle = abs(experiment.detector_normal.normalized().dot(unit_scattering_vector));
    auto solid_angle_correction = pow(cos_detected_ray_angle,3);

    auto res = solid_angle_correction * polarization_correction * air_transmission;

    if (experiment.detector=="Pilatus") {
        auto ray_len_in_detector = experiment.detector_thickness/cos_detected_ray_angle;

        auto pilatus_photon_efficiency = 1 - transmission("Silicon", experiment.wavelength, ray_len_in_detector);
        res*=pilatus_photon_efficiency;
    }

    return res;

    //TODO: Get a Bragg datasets for testing the corrections
    //TODO: Get a lot of air scattering from synchrotron to test the corrections
}
