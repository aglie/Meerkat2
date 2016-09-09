//
// Created by Arkadiy on 11/03/2016.
//

#ifndef MEERKAT2_MISC_H
#define MEERKAT2_MISC_H

#include <string>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

typedef float microstep_type;

typedef int corrected_frame_dt;
typedef float out_float_number;
typedef float reciprocal_fractional_t;
typedef reciprocal_fractional_t matrix_3x3[3][3];

const float  PI_F=3.14159265358979f;

typedef float vec6[6];

class vec3 {
public:
    vec3() {}
    vec3(float a,float b, float c) : data{a, b, c} {}
    float& operator[] (size_t n) {
        return data[n];
    }
    vec3 operator+ (const vec3& other) {
        return {data[0]+other.data[0],data[1]+other.data[1], data[2]+other.data[2]};
    }

//    vec3 operator+ (vec3&& other) const {
//        for(int i=0; i<3; ++i)
//            other.data[i]+=data[i];
//        return other;
//    }

    float norm() const {
        return sqrt(data[0]*data[0]+data[1]*data[1]+data[2]*data[2]);
    }

    vec3 normalized() const {
        return *this/norm();
    }

    float dot(const vec3& other) const {
        return data[0] * other.data[0] + data[1] * other.data[1] + data[2] * other.data[2];
    }

    vec3 operator/ (float d) const {
        return {data[0]/d, data[1]/d, data[2]/d};
    }

    vec3 operator- (const vec3& other) const {
        return {data[0]-other.data[0],data[1]-other.data[1], data[2]-other.data[2]};
    }

    vec3 cross(const vec3& other)
    {
        return {data[1]*other.data[2] - data[2]*other.data[1],
                data[2]*other.data[0] - data[0]*other.data[2],
                data[0]*other.data[1] - data[1]*other.data[0]};
    }

    //vec3 operator- (vec3&& other) {
    //    return {data[0]-other.data[0],data[1]-other.data[1], data[2]-other.data[2]};
    //}

    float data[3];
private:

};

template<typename T>
inline vec3 operator* (const T& a,vec3& v) {
    return {a*v[0], a*v[1], a*v[2]};
}

template<typename T>
inline vec3 operator* (const T& a, vec3&& v) {
    v[0]*=a;
    v[1]*=a;
    v[2]*=a;
    return v;
}

inline vec3 operator* (matrix_3x3 M, vec3& v) {
    return {M[0][0]*v[0]+M[0][1]*v[1]+M[0][2]*v[2],
            M[1][0]*v[0]+M[1][1]*v[1]+M[1][2]*v[2],
            M[2][0]*v[0]+M[2][1]*v[1]+M[2][2]*v[2]};
}
inline vec3 operator* (matrix_3x3 M, vec3&& v) {
    return {M[0][0]*v[0]+M[0][1]*v[1]+M[0][2]*v[2],
            M[1][0]*v[0]+M[1][1]*v[1]+M[1][2]*v[2],
            M[2][0]*v[0]+M[2][1]*v[1]+M[2][2]*v[2]};
}

template<typename T>
inline T square(T a){
    return a*a;
}

struct ReconstructionParameters {
    string data_filename_template;
    string xparm_filename;
    size_t first_image;
    size_t last_image;
    size_t number_of_pixels[3];
    reciprocal_fractional_t lower_limits[3];
    reciprocal_fractional_t step_sizes[3];
    bool reconstruct_in_orthonormal_basis;
    //measured_pixels in some format - missing in the baseline
    //size_t microsteps[3]; //missing in the baseline
    //size_t skip_frames; //missing in the baseline
    //unit_cell_transform_matrix=np.eye(3) //missing in baseline

    string output_filename;
    bool override;
    size_t size_of_cache;

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
};



class FileNotFound : std::exception {
public:
    FileNotFound() {}
    FileNotFound(string filename): filename(filename) {}
    ~FileNotFound() throw() {}
    string filename;
};

class UnknownFormat : std::exception {
public:
    UnknownFormat() {}
    ~UnknownFormat() throw() {}
};

ExperimentalParameters load_experimental_parameters(string filename);

ExperimentalParameters load_xparm(string filename);

ReconstructionParameters load_refinement_parameters(string filename);



class ValueOutsideRange : std::exception {
public:
    ValueOutsideRange() {}
    ~ValueOutsideRange() throw() {}
};

float air_absorption_coefficient(float wavelength);

float calculate_correction_coefficient(ExperimentalParameters& exp, int x, int y);

#endif //MEERKAT2_MISC_H
