//
// Created by Arkadiy on 11/03/2016.
//

#ifndef MEERKAT2_MISC_H
#define MEERKAT2_MISC_H

#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <Eigen/Dense>

using namespace std;

typedef float corrected_frame_dt;
typedef float out_float_number;
typedef float reciprocal_fractional_t;
typedef Eigen::Matrix3<reciprocal_fractional_t> matrix_3x3;

const float  PI_F=3.14159265358979f;

typedef float vec6[6];

typedef Eigen::Vector3<reciprocal_fractional_t > vec3;

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
    size_t number;

    Microstep(size_t no_microsteps, size_t increment_step=1) :
            inc(1.*increment_step/no_microsteps),
            start((-double(increment_step)+inc)*0.5),
            end(0.5*increment_step),
            number(no_microsteps)
    {}
};




#endif //MEERKAT2_MISC_H
