//
// Created by Arkadiy on 09/09/2016.
//

#include <iostream>
#include <set>
#include <sstream>
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

bool operator== (const ContextAroundPosition& a, const ContextAroundPosition& b) {
    return a.lines_after==b.lines_after && a.lines_before==b.lines_before && a.current_line==b.current_line && a.pos_within_current_line==b.pos_within_current_line;
}

ContextAroundPosition get_context(istream& in) {
    in.clear();


    if(in.eof())
    {
        in.clear();
        in.seekg(0,ios_base::end);
    }

    int context_position = in.tellg();
    vector<string> lines;

    in.seekg(0,ios_base::beg);

    string line;
    if(context_position==0) { //in case the line is empty
        getline(in,line);
        lines.push_back(line);
    } else
        while(int(in.tellg()) < context_position and !in.eof()) {
            getline(in,line);
            lines.push_back(line);
        }

    if(in.eof())
    {
        in.clear();
        in.seekg(0,ios_base::end);
    }

    auto current_line_no=int(lines.size())-1;

    string current_line;
    if(current_line_no>=0)
        current_line = lines[current_line_no];

    int position_within_current_line=0;
    if(in.tellg()>=0)
        position_within_current_line=current_line.length()-(int(in.tellg())-context_position);

    if (position_within_current_line<0)
        position_within_current_line=0;

    ostringstream lines_before;
    if(current_line_no==1) {
        lines_before << lines[0];
    } else if(current_line_no>1) {
        lines_before << lines[current_line_no-2] << endl << lines[current_line_no-1];
    }

    ostringstream lines_after;

    if(getline(in,line)) {
        lines_after << line;
    }
    if(getline(in,line)) {
        lines_after << endl << line;
    }

    in.seekg(context_position, ios_base::beg);
    string before=lines_before.str();
    string cur=current_line;
    string after=lines_after.str();

    ostringstream context;
    context << lines_before.str() << endl << current_line << endl;
    for(int i=0; i<position_within_current_line; ++i)
        context << " ";
    context << "^ - around here" << endl;
    context << lines_after.str();

    return ContextAroundPosition{lines_before.str(), current_line, lines_after.str(), position_within_current_line, current_line_no, context.str()};
}

bool reached_eof(const istream& in) {
    return in.rdstate() & istream::eofbit;
}
bool failed(const istream& in) {
    return in.rdstate() & (istream::badbit | istream::failbit);
}

string throw_parser_error(const string& filename, istream& in,const string& description) {
    ostringstream err_text;
    auto ctx = get_context(in);

    err_text << "Error parsing \"" << filename << "\" file" <<  " at line " << ctx.line_number << endl;

    err_text << description << ":";
    err_text << endl << endl << ctx.context << endl << endl;

    throw ParserError(err_text.str());
}

string throw_undefined_keyword(const string& filename, string keyword) {
    ostringstream err_text;
    err_text << "Error parsing \"" << filename << "\" file:" << endl;
    err_text << "keyword " << keyword << " is missing." << endl;

    throw ParserError(err_text.str());
}

string throw_error(const string& filename, string error) {
    ostringstream err_text;
    err_text << "Error parsing \"" << filename << "\" file:" << endl;
    err_text << error << endl;

    throw ParserError(err_text.str());
}


const set<string> known_xds_formats = {" XPARM.XDS    VERSION Jun 17, 2015", " XPARM.XDS    VERSION Oct 15, 2015", " XPARM.XDS    VERSION May 1, 2016  BUILT=20160617"};

void load_xparm(string filename, ExperimentalParameters & r) {
    ifstream in(filename);

    if(!in)
        throw FileNotFound(filename);

    getline(in, r.format);
    if (!isIn(r.format, known_xds_formats))
        cout <<
        "Warning: unknown version of XPARM.XDS file. This version has not been tested yet, use Meerkat at your own risk.\n";


    in >> r.starting_frame >> r.starting_angle >> r.oscillation_angle >>
    r.oscillation_axis[0] >> r.oscillation_axis[1] >> r.oscillation_axis[2] >>
    r.wavelength >> r.wavevector[0] >> r.wavevector[1] >> r.wavevector[2] >>
    r.space_group_nr >> r.cell[0] >> r.cell[1] >> r.cell[2] >> r.cell[3] >> r.cell[4] >> r.cell[5] >>
    r.cell_vectors[0][0] >> r.cell_vectors[0][1] >> r.cell_vectors[0][2] >>
    r.cell_vectors[1][0] >> r.cell_vectors[1][1] >> r.cell_vectors[1][2] >>
    r.cell_vectors[2][0] >> r.cell_vectors[2][1] >> r.cell_vectors[2][2] >>
    // We are changing x and y directions because xds uses fortran array notations, while we use C
    r.number_of_detector_segments >> r.NY >> r.NX >> r.pixel_size_y >> r.pixel_size_x >>
    r.y_center >> r.x_center >> r.distance_to_detector >>
    r.detector_y[0] >> r.detector_y[1] >> r.detector_y[2] >>
    r.detector_x[0] >> r.detector_x[1] >> r.detector_x[2] >>
    r.detector_normal[0] >> r.detector_normal[1] >> r.detector_normal[2];

    if(reached_eof(in)) {
        throw_parser_error(filename, in, "Unexpected end of file");
    }
    else if(failed(in)) {
        throw_parser_error(filename, in, "Unexpected value");
    }


    for (int i = 0; i < 5; ++i)
        in >> r.detector_segment_crossection[i];
    for (int i = 0; i < 9; ++i)
        in >> r.detector_segment_geometry[i];

}




ReconstructionParameters load_refinement_parameters(string filename) {
    //ReconstructionParameters exp = load_xparm("/Users/arkadiy/ag/data/GdFe77Si13/xds/XPARM.XDS");
    ifstream in(filename);
    //in.exceptions(ifstream::failbit | ifstream::badbit); //Also unexpected end of file should be checked
    // http://www.cplusplus.com/reference/ios/ios/exceptions/

    if(!in)
        throw FileNotFound(filename);

    ReconstructionParameters par;
    bool symmetric_limits = false;
    reciprocal_fractional_t upper_limits[3];
    bool upper_limits_defined = false;

    string keyword;

    while (!in.eof()) {
        in >> keyword;
        if(reached_eof(in))
            break;

        if (keyword[0] == '!' or keyword[0] == '#') {
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
        else if (keyword == "UPPER_LIMITS") {
            in >> upper_limits[0] >> upper_limits[1] >> upper_limits[2];
            upper_limits_defined=true;
        }
        else if (keyword == "STEP_SIZES")
            in >> par.step_sizes[0] >> par.step_sizes[1] >> par.step_sizes[2];
        else if (keyword == "SYMMETRIC_LIMITS")
            symmetric_limits = true;
        else if (keyword == "OUTPUT_FILENAME")
            in >> par.output_filename;
        else if (keyword == "XPARM_FILE")
            in >> par.xparm_filename;
        else if (keyword == "POLARIZATION_PLANE_NORMAL")
            in >> par.exp.polarization_plane_normal[0] >> par.exp.polarization_plane_normal[1] >>
            par.exp.polarization_plane_normal[2];
            //should probably come from xds.inp. Will break encapsulation of exp otherwise
            //In general, should input file be able to override any of the parameters from XPARM.XDS? Should they be clearly separated?
            // TODO: decide the above
        else if (keyword == "POLARIZATION_FACTOR")
            in >> par.exp.polarization_factor;
        else if (keyword == "DETECTOR")
            in >> par.exp.detector;
        else if (keyword == "DETECTOR_THICKNESS")
            in >> par.exp.detector_thickness;
        else if (keyword == "MICROSTEP_FRAMES")
            in >> par.microsteps[2];
        else if (keyword == "RECONSTRUCT_EVERY_NTH_FRAME")
            in >> par.frame_increment;
        else {
            throw_parser_error(filename, in, "Unknown keyword \"" + keyword + "\"");
        }
        if(reached_eof(in)) {
            throw_parser_error(filename, in, "Unexpected end of file");
        }
        else if(failed(in)) {
            throw_parser_error(filename, in, "Incorrect arguments to keyword \"" + keyword + "\"");
        }
    }

    if(par.lower_limits[0]==NAN and par.lower_limits[1]==NAN and par.lower_limits[2]==NAN)
        throw_undefined_keyword(filename,"LOWER_LIMITS");

    //Most of the people will use the lower and upper limits plus the number of steps. Stepsize is something esoteric.
    // TODO: allow to define the range with lower and upper limits and Nsteps
    if (symmetric_limits)
        for (int i = 0; i < 3; ++i)
            par.step_sizes[i] = -par.lower_limits[i] * 2 / (par.number_of_pixels[i]-1);

    if(upper_limits_defined)
        for (int i = 0; i < 3; ++i)
            par.step_sizes[i] = (upper_limits[i]-par.lower_limits[i]) / (par.number_of_pixels[i]-1);

    if(par.step_sizes[0]==NAN and par.step_sizes[1]==NAN and par.step_sizes[2]==NAN)
        throw_undefined_keyword(filename,"STEP_SIZES or UPPER_LIMITS or SYMMETRIC_LIMITS");

    if(par.data_filename_template=="")
        throw_undefined_keyword(filename, "DATA_FILE_TEMPLATE");

    if(par.xparm_filename=="")
        throw_undefined_keyword(filename, "XPARM_FILE");

    for(int i=0; i<3; ++i)
        if(par.microsteps <= 0)
            throw_error(filename, "MICROSTEPS should be positive");

    for(int i=0; i<2; ++i)
        if(par.microsteps[i] > 1)
            throw_error(filename, "MICROSTEPS along x and y are currently not supported");

    if(par.frame_increment <= 0)
        throw_error(filename, "RECONSTRUCT_EVERY_NTH_FRAME should be positive");

    if(par.last_image==numeric_limits<size_t>::max()) {
        int i;
        for(i=par.first_image; i<10000; i+=par.frame_increment) {
            if(not file_exists(format_template(par.data_filename_template, i))) {
                i-=par.frame_increment;
                break;
            }
        }
        par.last_image=i;
    }

    return par;
}
// TODO: add a non-trivial check that polarization plane is normal to wavevector otherwise the P correction will fail miserably