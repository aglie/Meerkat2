//
// Created by Arkadiy on 20/03/2016.
//

#ifndef MEERKAT2_GEOMETRY_H
#define MEERKAT2_GEOMETRY_H

#include "misc.h"


///Convert rotation from axis and angle to matrix representation. Assumes u is normalized.
inline void rotvec2mat(vec3& u, float phi, matrix_3x3& res) {
    // http://en.wikipedia.org/wiki/Rotation_matrix
    auto s = sin(phi);
    auto c = cos(phi);
    auto t = 1 - c;

    auto ux = u[0];
    auto uy = u[1];
    auto uz = u[2];

    res[0][0] = t * ux * ux + c;
    res[0][1] = t * ux * uy - s * uz;
    res[0][2] = t * ux * uz + s * uy;
    res[1][0] = t * ux * uy + s * uz;
    res[1][1] = t * uy * uy + c;
    res[1][2] = t * uy * uz - s * ux;
    res[2][0] = t * ux * uz - s * uy;
    res[2][1] = t * uy * uz + s * ux;
    res[2][2] = t * uz * uz + c;
}

template<typename T1, typename T2>
inline vec3 project_to_evald_sphere(ExperimentalParameters& p,
                    const T1& x,
                    const T1& y,
                    const T2& frame_no)
{
    auto xmm = (x - p.x_center) * p.pixel_size_x;
    auto ymm = (y - p.y_center) * p.pixel_size_y;

    vec3 scattering_vector_mm = xmm * p.detector_x + \
                             ymm * p.detector_y + \
                             p.distance_to_detector * p.detector_normal;


    auto unit_scattering_vector = scattering_vector_mm.normalized();
    auto s = unit_scattering_vector / p.wavelength - p.wavevector;
    return s;
}

template<typename T1, typename T2>
inline vec3 det2lab(ExperimentalParameters& p,
                    const T1& x,
                    const T1& y,
                    const T2& frame_no)
{
    auto phi = (frame_no - p.starting_frame) * p.oscillation_angle + p.starting_angle;
    matrix_3x3 rotation_matrix;
    rotvec2mat(p.oscillation_axis, -2 * PI_F * phi / 360, rotation_matrix);
    auto hkl = rotation_matrix * project_to_evald_sphere(p,x,y,frame_no);
    return hkl;
}

template<typename T1, typename T2>
inline vec3 det2hkl(ExperimentalParameters& p,
                    const T1& x,
                    const T1& y,
                    const T2& frame_no)
{
    return p.cell_vectors * det2lab(p,x,y,frame_no);
}

inline void get_index(
        ExperimentalParameters& exp,
        ReconstructionParameters& par,
        size_t x, size_t y,
        int frame_no, int* indices) {

    auto hkl = det2hkl<int>(exp, x, y, frame_no);

    indices[0] = (hkl[0]-par.lower_limits[0])/par.step_sizes[0];
    indices[1] = (hkl[1]-par.lower_limits[1])/par.step_sizes[1];
    indices[2] = (hkl[2]-par.lower_limits[2])/par.step_sizes[2];
}

inline bool indices_within_bounds(ReconstructionParameters& p, int* i) {
    return i[0]>=0 and i[1]>=0 and i[2]>=0 and \
           i[0]<p.number_of_pixels[0] and \
           i[1]<p.number_of_pixels[1] and \
           i[2]<p.number_of_pixels[2];
}

#endif //MEERKAT2_GEOMETRY_H
