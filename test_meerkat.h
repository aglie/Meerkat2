//
// Created by Arkadiy on 11/03/2016.
//

#include <cxxtest/TestSuite.h>
#include "misc.h"
#include "ImageLoader.h"
#include "Geometry.h"
#include "Corrections.h"

const double inp_file_delta = 0.001;
const float eps=0.0000001;

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
        ExperimentalParameters params;
        load_xparm("tris-amide xds/XPARM.XDS",params);
        TS_ASSERT_EQUALS(1, params.starting_frame);
        TS_ASSERT_DELTA(0.,params.starting_angle,inp_file_delta);
        TS_ASSERT_DELTA(0.25,params.oscillation_angle,inp_file_delta);
        TS_ASSERT_DELTA(0.999988,params.oscillation_axis[0],inp_file_delta);
        TS_ASSERT_DELTA(-0.001214,params.oscillation_axis[1],inp_file_delta);
        TS_ASSERT_DELTA(0.004726,params.oscillation_axis[2],inp_file_delta);
        TS_ASSERT_DELTA(0.750000,params.wavelength,inp_file_delta);

        TS_ASSERT_DELTA(1005.094666,params.y_center,inp_file_delta);
        TS_ASSERT_DELTA(1005.766968,params.x_center,inp_file_delta);
        TS_ASSERT_DELTA(179.778595,params.distance_to_detector,inp_file_delta);
    }

    void test_air_absorption_coefficient() {
        TS_ASSERT_DELTA(0.00014486405283802817, material_absorption_coefficient("Air", 0.71),0.00000001);
    }

    //TODO: Rewrite this test and point it to a reasonable file
    void notest_image_loader() {
        ExperimentalParameters exp;
        ReconstructionParameters rec;
        rec.data_filename_template="/Users/arkadiy/ag/data/GdFe77Si13/images/gfs1_2_?????.cbf";
        rec.first_image=10;
        rec.last_image=10;
        ImageLoader img(rec);
        TS_ASSERT(img.load_next_frame());
        TS_ASSERT_EQUALS(679, img.current_frame(700,1030));
        TS_ASSERT_EQUALS(774, img.current_frame(701,1030));
        TS_ASSERT_EQUALS(803, img.current_frame(702,1030));
    }

    void test_filename_template() {
        TS_ASSERT_EQUALS("somewhere/whatever010.cbf", format_template("somewhere/whatever???.cbf",10));
    }

    void test_det2lab() {
        ExperimentalParameters params;
        load_xparm("tris-amide xds/GXPARM.XDS", params);
        ifstream in("tris-amide xds/XDS_ASCII.HKL");
        char first_letter;
        string line;


        float h,k,l, I, sigma, x, y, frame_no;
        float hcalс, kcalc, lcalc;
        for(getline(in, line); line != "!END_OF_DATA"; getline(in, line)) {
            if(line[0]=='!') //skip comment
                continue;

            istringstream s(line);
            s >> h >> k >> l >> I >> sigma >> y >> x >> frame_no;
            /*
             * Fun observation. The precision here is horrible. I wonder now, is it an error in calculations,
             * or the fact that orientation matrix is rerefined during integration?
             *
             * Also, are the xyframe positions of Bragg peaks in the final table calculated or determined from say
             * Bragg peak centroids???
             */
            auto hkl = det2hkl(params, x, y, frame_no);
            TS_ASSERT_DELTA(hkl[0],h,0.09);
            TS_ASSERT_DELTA(hkl[1],k,0.09);
            TS_ASSERT_DELTA(hkl[2],l,0.09);
        }

//        !ITEM_PSI=12
//        !END_OF_HEADER
//        0     0    -1  1.213E+01  3.638E+01   992.1   931.4    346.1   0.06087 100  20   50.99
//        0     0     1 -1.848E+01  4.039E+01  1012.4  1077.5    331.9   0.06083 100 -14  -51.49
    }



    void test_get_context() {
        istringstream t1("");
        {
            ContextAroundPosition ans{"", "", "", 0};
            TS_ASSERT_EQUALS(ans, get_context(t1));
        }

        istringstream t2("one two\nthree four\nfive six\nseven eight\nnine ten\neleven twelve");
        {
            ContextAroundPosition ans{"", "one two", "three four\nfive six", 0};
            TS_ASSERT_EQUALS(ans, get_context(t2));
        }

        t2.seekg(0, ios_base::beg);
        string rubbish;
        char newline_holder;
        getline(t2,rubbish);
        t2 >> rubbish;
        TS_ASSERT_EQUALS("three",rubbish);
        {
            ContextAroundPosition ans{"one two", "three four", "five six\nseven eight", 4};
            TS_ASSERT_EQUALS(ans, get_context(t2));
        }
        t2.seekg(0, ios_base::beg);
        getline(t2,rubbish);
        getline(t2,rubbish);
        t2>>newline_holder;
        {
            ContextAroundPosition ans{"one two\nthree four", "five six", "seven eight\nnine ten", 0};
            TS_ASSERT_EQUALS(ans, get_context(t2));
        }

        t2.seekg(0, ios_base::beg);
        for(int i=0; i<4; ++i)
            getline(t2,rubbish);
        t2>>newline_holder;
        {
            ContextAroundPosition ans{"five six\nseven eight","nine ten","eleven twelve",0};
            TS_ASSERT_EQUALS(ans, get_context(t2));

        }

        t2.seekg(0, ios_base::beg);
        for(int i=0; i<6; ++i)
            getline(t2,rubbish);
        {
            ContextAroundPosition ans{"seven eight\nnine ten","eleven twelve","",13};
            TS_ASSERT_EQUALS(ans, get_context(t2));
        }

    }

    void test_vector_times_scalar() {
        vec3 t = 2*vec3(0,1,2);
        TS_ASSERT_DELTA(0,t[0],0.0000001);
        TS_ASSERT_DELTA(2,t[1],0.0000001);
        TS_ASSERT_DELTA(4,t[2],0.0000001);
    }

    void test_microstep() {
        Microstep ms1(1,1);
        TS_ASSERT_DELTA(ms1.start,0,eps);
        TS_ASSERT_DELTA(ms1.end,0.5,eps);
        TS_ASSERT_DELTA(ms1.inc,1,eps);


        Microstep ms2(1,2);
        TS_ASSERT_DELTA(ms2.start,0,eps);
        TS_ASSERT_DELTA(ms2.end,1,eps);
        TS_ASSERT_DELTA(ms2.inc,2,eps);

        Microstep ms3(2,1);
        TS_ASSERT_DELTA(ms3.start,-0.25,eps);
        TS_ASSERT_DELTA(ms3.end,0.5,eps);
        TS_ASSERT_DELTA(ms3.inc,0.5,eps);

        Microstep ms4(2,2);
        TS_ASSERT_DELTA(ms4.start,-0.25*2,eps);
        TS_ASSERT_DELTA(ms4.end,0.5*2,eps);
        TS_ASSERT_DELTA(ms4.inc,0.5*2,eps);

        Microstep ms5(3,1);
        TS_ASSERT_DELTA(ms5.start,-1./3,eps);
        TS_ASSERT_DELTA(ms5.end,0.5,eps);
        TS_ASSERT_DELTA(ms5.inc,1./3,eps);
    }
};

