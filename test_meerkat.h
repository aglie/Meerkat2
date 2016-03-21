//
// Created by Arkadiy on 11/03/2016.
//

#include <cxxtest/TestSuite.h>
#include "misc.h"
#include "ImageLoader.h"
#include "Geometry.h"

const double inp_file_delta = 0.001;

class MeerkatTestSuit : public CxxTest::TestSuite
{
public:
    void test_load_xparm() {
        //currently tests a couple of numbers, just to make sure it loads the data

        //TODO: Test all the values since the file type

        /*
         * XPARM.XDS    VERSION Jun 17, 2015
    1        0.0000    0.2500  0.999988 -0.001214  0.004726
    0.750000      -0.003162      -0.001518       1.333329
    1      6.9322     14.1162     14.1170  59.988  90.002  90.003
    -6.692194       1.615698      -0.812077
    3.093155      13.666920       1.707512
    3.278411       7.949903     -11.195524
    1      2000      2000    0.150000    0.150000
    1005.094666    1005.766968     179.778595
    1.000000       0.000000       0.000000
    0.000000       1.000000       0.000000
    0.000000       0.000000       1.000000
    1         1      2000         1      2000
    0.00    0.00    0.00  1.00000  0.00000  0.00000  0.00000  1.00000  0.00000


                      wavelength=r_get_numbers(f, 1),
                      wavevector=r_get_numbers(f, 3),

                      space_group_nr=r_get_numbers(f, 1),
                      cell=r_get_numbers(f, 6),
                      unit_cell_vectors=np.reshape(r_get_numbers(f, 9), (3, 3)),

                      number_of_detector_segments=r_get_numbers(f, 1),
                      NX=r_get_numbers(f, 1),
                      NY=r_get_numbers(f, 1),
                      pixelsize_x=r_get_numbers(f, 1),
                      pixelsize_y=r_get_numbers(f, 1),

                      x_center=r_get_numbers(f, 1),
                      y_center=r_get_numbers(f, 1),
                      distance_to_detector=r_get_numbers(f, 1),

                      detector_x=r_get_numbers(f, 3),
                      detector_y=r_get_numbers(f, 3),
                      detector_normal=r_get_numbers(f, 3),
                      detector_segment_crossection=r_get_numbers(f, 5),
                      detector_segment_geometry=r_get_numbers(f, 9)
         */
        auto params = load_xparm("tris-amide xds/XPARM.XDS");
        TS_ASSERT_EQUALS(1, params.starting_frame);
        TS_ASSERT_DELTA(0.,params.starting_angle,inp_file_delta);
        TS_ASSERT_DELTA(0.25,params.oscillation_angle,inp_file_delta);
        TS_ASSERT_DELTA(0.999988,params.oscillation_axis[0],inp_file_delta);
        TS_ASSERT_DELTA(-0.001214,params.oscillation_axis[1],inp_file_delta);
        TS_ASSERT_DELTA(0.004726,params.oscillation_axis[2],inp_file_delta);
        TS_ASSERT_DELTA(0.750000,params.wavelength,inp_file_delta);

        TS_ASSERT_DELTA(1005.094666,params.x_center,inp_file_delta);
        TS_ASSERT_DELTA(1005.766968,params.y_center,inp_file_delta);
        TS_ASSERT_DELTA(179.778595,params.distance_to_detector,inp_file_delta);

    }

    void test_air_absorption_coefficient() {
        TS_ASSERT_DELTA(0.00014486405283802817,air_absorption_coefficient(0.71),0.00000001);
    }

    void test_image_loader() {
        ExperimentalParameters exp;
        ReconstructionParameters rec;
        rec.filename_template="/Users/arkadiy/ag/data/GdFe77Si13/images/gfs1_2_?????.cbf";
        rec.first_image=10;
        rec.last_image=10;
        ImageLoader img(exp,rec);
        TS_ASSERT(img.load_next_frame());
        TS_ASSERT_EQUALS(679, img.current_frame(700,1030));
        TS_ASSERT_EQUALS(774, img.current_frame(701,1030));
        TS_ASSERT_EQUALS(803, img.current_frame(702,1030));
    }

    void test_filename_template() {
        TS_ASSERT_EQUALS("somewhere/whatever010.cbf",ImageLoader::format_template("somewhere/whatever???.cbf",10));
    }

    void test_det2lab() {
        auto params = load_xparm("tris-amide xds/GXPARM.XDS");
        ifstream in("tris-amide xds/XDS_ASCII.HKL");
        char first_letter;
        string line;


        float h,k,l, I, sigma, x, y, frame_no;
        float hcalс, kcalc, lcalc;
        for(getline(in, line); line != "!END_OF_DATA"; getline(in, line)) {
            if(line[0]=='!') //skip comment
                continue;

            istringstream s(line);
            s >> h >> k >> l >> I >> sigma >> x >> y >> frame_no;
            /*
             * Fun observation. The precision here is horrible. I wonder now, is it an error in calculations,
             * or the fact that orientation matrix is rerefined during integration?
             *
             * Also, are the xyframe positions of Bragg peaks in the final table calculated or determined from say
             * Bragg peak centroids???
             */
            det2lab(params, x, y, frame_no, hcalс, kcalc, lcalc);
            TS_ASSERT_DELTA(h,hcalс,0.09);
            TS_ASSERT_DELTA(k,kcalc,0.09);
            TS_ASSERT_DELTA(l,lcalc,0.09);
        }

//        !ITEM_PSI=12
//        !END_OF_HEADER
//        0     0    -1  1.213E+01  3.638E+01   992.1   931.4    346.1   0.06087 100  20   50.99
//        0     0     1 -1.848E+01  4.039E+01  1012.4  1077.5    331.9   0.06083 100 -14  -51.49
    }

    void test_vector_times_scalar() {
        vec3 t = 2*vec3(0,1,2);
        TS_ASSERT_DELTA(0,t[0],0.0000001);
        TS_ASSERT_DELTA(2,t[1],0.0000001);
        TS_ASSERT_DELTA(4,t[2],0.0000001);
    }
};

