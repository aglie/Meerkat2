//
// Created by Arkadiy on 11/03/2016.
//

#include <iostream>
#include <regex>
#include <sstream>
#include <iomanip>
#include "misc.h"
#include "Geometry.h"

bool file_exists(const string& filename) {
    ifstream in(filename);
    return in.good();
}




/// Replaces ??? in the format file with the image number. Example whatever???.cbf, 2 -> whatever002.cbf
string format_template(string format, size_t N) {
    smatch m;
    regex r("\\?+");

    bool found = regex_search(format, m, r);
    if(!found) {
        return format; //do not change anything
    }

    ostringstream formatted_n;

    formatted_n << setfill('0') << setw(m.length()) << N;

    return regex_replace(format, r, formatted_n.str());
}