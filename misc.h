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

typedef float corrected_frame_dt;
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

class FileNotFound : std::exception {
public:
    FileNotFound(string filename): filename(filename) {}
    ~FileNotFound() throw() {}
    string filename;
};

class ParserError : std::exception {
public:
    ParserError(string description): description(description) {}
    ~ParserError() throw() {}
    string description;
};

class MaskError : std::exception {
public:
    MaskError(string description): description(description) {}
    ~MaskError() throw() {}
    string description;
};

class ValueOutsideRange : std::exception {
public:
    ValueOutsideRange() {}
    ~ValueOutsideRange() throw() {}
};

bool file_exists(const string& filename);
string format_template(string, size_t);

class Microstep {
public:
    double inc;
    double start;
    double end;

    Microstep(size_t no_microsteps, size_t increment_step=1) :
            inc(1.*increment_step/no_microsteps),
            start((-double(increment_step)+inc)*0.5),
            end(0.5*increment_step)
    {}
};




#endif //MEERKAT2_MISC_H
