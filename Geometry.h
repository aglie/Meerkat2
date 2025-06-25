//
// Created by Arkadiy on 20/03/2016.
//

#ifndef MEERKAT2_GEOMETRY_H
#define MEERKAT2_GEOMETRY_H

#include "misc.h"
#include "ReconstructionParameters.h"

///Convert rotation from axis and angle to matrix representation. Assumes u is normalized.
inline void rotvec2mat(vec3& u, float phi, matrix_3x3& res) {
    // http://en.wikipedia.org/wiki/Rotation_matrix
    auto s = sin(phi);
    auto c = cos(phi);
    auto t = 1 - c;

    auto ux = u[0];
    auto uy = u[1];
    auto uz = u[2];

    res(0, 0) = t * ux * ux + c;
    res(0, 1) = t * ux * uy - s * uz;
    res(0, 2) = t * ux * uz + s * uy;
    res(1, 0) = t * ux * uy + s * uz;
    res(1, 1) = t * uy * uy + c;
    res(1, 2) = t * uy * uz - s * ux;
    res(2, 0) = t * ux * uz - s * uy;
    res(2, 1) = t * uy * uz + s * ux;
    res(2, 2) = t * uz * uz + c;

}


//TODO: Hide all this functions in a class ExperimentalGeometry or something like this
// All this funcitons depend on ExperimentalParameters. It is likely, that they will be implemented the second time
// if/when I will use the Crysalis orientation matrix definitions. At this moment it would be wise to have two Experimental
// classes
// All this functions, though being quite lightweight are outside the main loop so speed is not important here really
template<typename T>
inline vec3 real_space_scattering_vector(ExperimentalParameters & p,
                                         const T& x,
                                         const T& y)
{
    auto xmm = (x - p.x_center) * p.pixel_size_x;
    auto ymm = (y - p.y_center) * p.pixel_size_y;

    vec3 scattering_vector_mm = xmm * p.detector_x + \
                             ymm * p.detector_y + \
                             p.distance_to_detector * p.detector_normal;

    return scattering_vector_mm;
}

template<typename T>
inline vec3 project_to_evald_sphere(ExperimentalParameters & p,
                                    const T& x,
                                    const T& y)
{
    vec3 scattering_vector_mm = real_space_scattering_vector(p,x,y);


    auto unit_scattering_vector = scattering_vector_mm.normalized();
    auto s = unit_scattering_vector / p.wavelength - p.wavevector;
    return s;
}

template<typename T>
inline vec3 rotate_to_frame(
        ExperimentalParameters & p,
        vec3 s,
        const T& frame_no) {
    auto phi = (frame_no - p.starting_frame) * p.oscillation_angle + p.starting_angle;
    matrix_3x3 rotation_matrix;
    rotvec2mat(p.oscillation_axis, -2 * PI_F * phi / 360, rotation_matrix);
    auto hkl = rotation_matrix * s;
    return hkl;
}

template<typename T>
inline matrix_3x3 pixel_to_hkl_matrix(
        ExperimentalParameters & p,
        const T& frame_no)
{
    auto phi = (frame_no - p.starting_frame) * p.oscillation_angle + p.starting_angle;
    matrix_3x3 rotation_matrix;
    rotvec2mat(p.oscillation_axis, -2 * PI_F * phi / 360, rotation_matrix);
    return p.cell_vectors* rotation_matrix;
}

template<typename T1, typename T2>
inline vec3 det2lab(ExperimentalParameters & p,
                    const T1& x,
                    const T1& y,
                    const T2& frame_no)
{
    return rotate_to_frame(p, project_to_evald_sphere(p,x,y), frame_no);
}

template<typename T1, typename T2>
inline vec3 det2hkl(ExperimentalParameters & p,
                    const T1& x,
                    const T1& y,
                    const T2& frame_no)
{
    return p.cell_vectors * det2lab(p,x,y,frame_no);
}


inline void to_index(const ReconstructionParameters& par,
        const vec3 hkl, int* res ) {

    // round operation is implicit in conversion which applies floor, together with floor it makes it correctly
    // TODO: SOMTHING CHAGED, test it thoroughly
    // Check part with microstepping thoroughly!
    res[0] = int((hkl[0] - par.lower_limits[0]) * par.inv_step_sizes[0] + 0.5);
    res[1] = int((hkl[1] - par.lower_limits[1]) * par.inv_step_sizes[1] + 0.5);
    res[2] = int((hkl[2] - par.lower_limits[2]) * par.inv_step_sizes[2] + 0.5);
}

inline void get_index(
        ExperimentalParameters & exp,
        ReconstructionParameters& par,
        size_t x, size_t y,
        int frame_no, int* indices) {

    auto hkl = det2hkl<int>(exp, x, y, frame_no);

    to_index(par, hkl, indices);
}

inline bool indices_within_bounds(ReconstructionParameters& p, int* i) {
    return i[0]>=0 and i[1]>=0 and i[2]>=0 and \
           i[0]<p.number_of_pixels[0] and \
           i[1]<p.number_of_pixels[1] and \
           i[2]<p.number_of_pixels[2];
}

#endif //MEERKAT2_GEOMETRY_H
