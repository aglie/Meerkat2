
 ***** CORRECT ***** (VERSION Jun 17, 2015)  24-Feb-2016

 INPUT PARAMETER VALUES
 ----------------------
 SPACE_GROUP_NUMBER=    1 as used in the INTEGRATE step
 UNIT_CELL_CONSTANTS=     6.932    14.116    14.117  59.988  90.002  90.003 as used by INTEGRATE
 FRIEDEL'S_LAW=TRUE 
 PROFILE_FITTING= TRUE 
 OVERLOAD=    130000     MINPK=  75.00000    WFAC1=   1.0
 INCLUDE_RESOLUTION_RANGE=    20.000     0.000
 NAME_TEMPLATE_OF_DATA_FRAMES=../mar2000/diffuse_???.mar2000 MAR345
 DATA_RANGE=       1     513
 ROTATION_AXIS=  0.999988 -0.001214  0.004726
 OSCILLATION_RANGE=  0.250000
 STARTING_ANGLE=     0.000     STARTING_FRAME=       1
 X-RAY_WAVELENGTH=  0.750000
 INCIDENT_BEAM_DIRECTION= -0.003162 -0.001518  1.333329
 FRACTION_OF_POLARIZATION=   0.500
 POLARIZATION_PLANE_NORMAL=  0.000000  1.000000  0.000000
 AIR=   0.00013
 DETECTOR=MAR345
 SILICON=  1.662190 SENSOR_THICKNESS=  0.000000
 NUMBER OF DETECTOR SEGMENTS   1
 NX=  2000  NY=  2000    QX=  0.150000  QY=  0.150000
 ORGX=   1005.09  ORGY=   1005.77
 DETECTOR_DISTANCE=   179.779
 DIRECTION_OF_DETECTOR_X-AXIS=   1.00000   0.00000   0.00000
 DIRECTION_OF_DETECTOR_Y-AXIS=   0.00000   1.00000   0.00000
 BEAM_DIVERGENCE_E.S.D.=   0.067
 REFLECTING_RANGE_E.S.D.=   0.123
 MINIMUM_ZETA=     0.050
 MAXIMUM_ERROR_OF_SPOT_POSITION=   3.0
 MAXIMUM_ERROR_OF_SPINDLE_POSITION=   2.0
 MINIMUM_I/SIGMA=   3.0
 REFLECTIONS/CORRECTION_FACTOR=      50
 STRICT_ABSORPTION_CORRECTION=FALSE 
 CORRECTIONS= DECAY MODULATION ABSORPTION                      
 REFERENCE_DATA_SET=                                                  


    2509 REFLECTIONS ON FILE "INTEGRATE.HKL"
       0 CORRUPTED REFLECTION RECORDS (IGNORED)
       0 MATCHING REFLECTIONS SPECIFIED IN FILE "FILTER.HKL"
       0 REFLECTIONS INCOMPLETE OR OUTSIDE IMAGE RANGE       1 ...     513
      83 OVERLOADED REFLECTIONS (IGNORED)
       1 REFLECTIONS OUTSIDE ACCEPTED RESOLUTION RANGES
                OR TOO CLOSE TO ROTATION AXIS (IGNORED)
    2425 REFLECTIONS ACCEPTED



 ******************************************************************************
                      AUTOMATIC SPACE GROUP ASSIGNMENT
 ******************************************************************************

 XDS adopts the following approach.
 (1) it looks for possible symmetries of the crystal lattice
 (2) it computes a redundancy independent R-factor for all enantiomorphous
     point groups compatible with the observed lattice symmetry.
 (3) it selects the group which explains the intensity data at an acceptable,
     redundancy-independent R-factor (Rmeas, Rrim) using a minimum number of
     unique reflections.

 This approach does not test for the presence of screw axes. Consequently,
 orthorhombic cell axes will be specified in increasing length (following
 conventions), despite the possibility that different assignments for the
 cell axes could become necessary for space groups P222(1) and P2(1)2(1)2
 containing one or two screw axes, respectively.

 The user can always override the automatic decisions by specifying the
 correct space group number and unit cell constants in XDS.INP and repeating
 the CORRECT step of XDS. This provides a simple way to rename orthorhombic
 cell constants if screw axes are present.

 In addition, the user has the option to specify in XDS.INP
 (a) a reference data set or
 (b) a reindexing transformation or
 (c) the three basis vectors (if known from processing a previous data set
 taken at the same crystal orientation in a multi-wavelength experiment).
 These features of XDS are useful for resolving the issue of alternative
 settings of polar or rhombohedral cells (like P4, P6, R3).

 =====> Specifications provided by the user in XDS.INP:
 SPACE_GROUP_NUMBER=    0 (0: unknown symmetry and unit cell)
 UNIT_CELL_CONSTANTS=     0.00     0.00     0.00   0.000   0.000   0.000
 UNIT_CELL_A-AXIS=     0.000     0.000     0.000 (0 0 0 : unknown)
 UNIT_CELL_B-AXIS=     0.000     0.000     0.000 (0 0 0 : unknown)
 UNIT_CELL_C-AXIS=     0.000     0.000     0.000 (0 0 0 : unknown)
 REIDX=  0  0  0  0  0  0  0  0  0  0  0  0 (all 0 : not specified)
 TEST_RESOLUTION_RANGE=    8.00    4.50 (Angstrom) for space group determination
 NUMBER OF ACCEPTED REFLECTIONS FOR CALCULATING Rmeas               10
 NUMBER OF ACCEPTED UNIQUE REFLECTIONS FROM REFERENCE DATA SET       0


 *********** DETERMINATION OF LATTICE CHARACTER AND BRAVAIS LATTICE ***********

 The CHARACTER OF A LATTICE is defined by the metrical parameters of its
 reduced cell as described in the INTERNATIONAL TABLES FOR CRYSTALLOGRAPHY
 Volume A, p. 746 (KLUWER ACADEMIC PUBLISHERS, DORDRECHT/BOSTON/LONDON, 1989).
 Note that more than one lattice character may have the same BRAVAIS LATTICE.

 A lattice character is marked "*" to indicate a lattice consistent with the
 observed locations of the diffraction spots. These marked lattices must have
 low values for the QUALITY OF FIT and their implicated UNIT CELL CONSTANTS
 should not violate the ideal values by more than
 MAX_CELL_AXIS_ERROR=  0.03
 MAX_CELL_ANGLE_ERROR=           2.0 (Degrees)

 The REINDEXING TRANSFORMATION REIDX() consists of 12 integers that relate
 the original indices H,K,L from file INTEGRATE.HKL to the indices H',K',L'
 with respect to the new cell.
    H'=(REIDX(1)*H+REIDX( 2)*K+REIDX( 3)*L)/IDXV+REIDX( 4)
    K'=(REIDX(5)*H+REIDX( 6)*K+REIDX( 7)*L)/IDXV+REIDX( 8)
    L'=(REIDX(9)*H+REIDX(10)*K+REIDX(11)*L)/IDXV+REIDX(12)
 The value of the integer IDXV depends on the lattice type used for
 specifying reflections on file INTEGRATE.HKL; IDXV is
 1 for a primitive,
 2 for a face or body centred,
 3 for a rhombohedral,
 4 for a lattice centred on all faces.
 IDXV is set by XDS and cannot be input by the user.

  LATTICE-  BRAVAIS-   QUALITY  UNIT CELL CONSTANTS (ANGSTROEM & DEGREES)    REINDEXING TRANSFORMATION
 CHARACTER  LATTICE     OF FIT      a      b      c   alpha  beta gamma

 *  31        aP          0.0       6.9   14.1   14.1  60.0  90.0  90.0    1  0  0  0  0 -1  1  0  0 -1  0  0
 *  44        aP          0.1       6.9   14.1   14.1 120.0  90.0  90.0   -1  0  0  0  0  1 -1  0  0 -1  0  0
 *  35        mP          0.3      14.1    6.9   14.1  90.0 120.0  90.0    0 -1  1  0  1  0  0  0  0  1  0  0
 *  30        mC          0.4      14.1   24.5    6.9  90.0  90.0  90.0    0 -1  1  0  0  1  1  0 -1  0  0  0
 *  41        mC          0.5      24.5   14.1    6.9  90.0  90.0  90.0    0  1  1  0  0 -1  1  0  1  0  0  0
 *  40        oC          0.6      14.1   24.5    6.9  90.0  90.0  90.0    0 -1  1  0  0 -1 -1  0  1  0  0  0
 *  20        mC          1.4      24.4   14.1    6.9  90.0  90.0  90.0    0 -2  1  0  0  0  1  0 -1  0  0  0
 *  23        oC          1.7      14.1   24.4    6.9  90.0  90.0  90.0    0  0 -1  0  0 -2  1  0 -1  0  0  0
 *  25        mC          1.7      14.1   24.4    6.9  90.0  90.0  90.0    0  0 -1  0  0 -2  1  0 -1  0  0  0
 *  22        hP          2.0      14.1   14.1    6.9  90.0  90.0 120.0    0  1 -1  0  0 -1  0  0 -1  0  0  0
    37        mC        250.1      29.1    6.9   14.1  90.0 119.0  76.2   -1 -2  0  0 -1  0  0  0  0  1 -1  0
    39        mC        250.2      29.1    6.9   14.1  90.0 119.0  76.2    1  2 -2  0  1  0  0  0  0 -1  0  0
    42        oI        250.4       6.9   14.1   25.4  90.0 105.8  90.0    1  0  0  0  0 -1  1  0 -1 -1 -1  0
    27        mC        499.8      29.1    6.9   14.1  90.0 119.0  76.2   -1 -2  2  0 -1  0  0  0  0  0 -1  0
    19        oI        501.2       6.9   14.1   25.4  90.0  74.2  90.0   -1  0  0  0  0  0 -1  0 -1 -2  1  0
    24        hR        667.3      25.4   24.5    6.9  90.0  74.2 118.8   -1 -2  1  0  0  1  1  0 -1  0  0  0
     1        cF        999.0      15.7   15.7   25.4  96.9  96.9 127.7    1  0 -1  0  1  0  1  0 -1 -2  1  0
     2        hR        999.0      15.7   15.7   25.4 128.9  51.1 126.6    1  1 -1  0 -1 -1  0  0 -1  2 -1  0
     3        cP        999.0       6.9   14.1   14.1 120.0  90.0  90.0   -1  0  0  0  0  1 -1  0  0 -1  0  0
     5        cI        999.0      15.7   15.7   14.1  63.3  63.3 102.0   -1 -1  0  0 -1  1 -1  0  0  0 -1  0
     4        hR        999.0      15.7   15.7   15.7 102.1  78.0  78.0   -1 -1  1  0  1 -1  0  0  1  0  1  0
     6        tI        999.0      14.1   15.7   15.7 102.0  63.3  63.3    0  0 -1  0 -1 -1  0  0 -1  1 -1  0
     7        tI        999.0      15.7   15.7   14.1  63.3  63.3 102.0   -1 -1  0  0 -1  1 -1  0  0  0 -1  0
     8        oI        999.0      15.7   15.7   14.1  63.3  63.3 102.0    1 -1  1  0  1  1  0  0  0  0  1  0
     9        hR        999.0       6.9   15.7   38.0  75.7 100.5 116.2    1  0  0  0 -1 -1  1  0 -1 -2 -1  0
    10        mC        999.0      15.7   15.7   14.1  63.4 116.6 127.7    1 -1  1  0  1  1 -1  0  0  1  0  0
    11        tP        999.0       6.9   14.1   14.1 120.0  90.0  90.0   -1  0  0  0  0  1 -1  0  0 -1  0  0
    12        hP        999.0       6.9   14.1   14.1 120.0  90.0  90.0   -1  0  0  0  0 -1  1  0  0  1  0  0
    13        oC        999.0      15.7   15.7   14.1 116.6 116.6  52.3   -1  1 -1  0  1  1 -1  0  0 -1  0  0
    15        tI        999.0       6.9   14.1   25.4  90.0  74.2  90.0   -1  0  0  0  0  1 -1  0 -1 -1 -1  0
    16        oF        999.0      15.7   15.7   25.4  83.1  96.9  52.3    1 -1  1  0 -1 -1  1  0 -1 -1 -1  0
    14        mC        999.0      15.7   15.7   14.1 116.6 116.6  52.3   -1  1 -1  0  1  1 -1  0  0 -1  0  0
    17        mC        999.0      15.7   15.7   15.7 102.0 126.7  52.3    1 -1  1  0 -1 -1  1  0 -1  0 -1  0
    18        tI        999.0      14.1   25.4    6.9  74.2  90.0  90.0    0  0 -1  0  1  2 -1  0  1  0  0  0
    21        tP        999.0      14.1   14.1    6.9  90.0  90.0 120.0    0  1 -1  0  0 -1  0  0 -1  0  0  0
    26        oF        999.0       6.9   29.1   29.1  58.1 103.8 103.8    1  0  0  0 -1 -2  2  0 -1 -2  0  0
    28        mC        999.0       6.9   29.1   14.1  61.0  90.0  76.2   -1  0  0  0 -1 -2  0  0  0 -1  1  0
    29        mC        999.0       6.9   29.1   14.1  61.0  90.0  76.2    1  0  0  0  1  2 -2  0  0  1  0  0
    32        oP        999.0       6.9   14.1   14.1 120.0  90.0  90.0   -1  0  0  0  0  1 -1  0  0 -1  0  0
    36        oC        999.0       6.9   29.1   14.1  61.0  90.0 103.8   -1  0  0  0  1  2  0  0  0  1 -1  0
    33        mP        999.0       6.9   14.1   14.1 120.0  90.0  90.0   -1  0  0  0  0  1 -1  0  0 -1  0  0
    38        oC        999.0       6.9   29.1   14.1  61.0  90.0 103.8    1  0  0  0 -1 -2  2  0  0 -1  0  0
    34        mP        999.0       6.9   14.1   14.1 120.0  90.0  90.0    1  0  0  0  0  1  0  0  0 -1  1  0
    43        mI        999.0      15.7   25.4   14.1  90.0 153.8  83.1    1  1 -1  0  1  1  1  0  0 -1  1  0

 ****** LATTICE SYMMETRY IMPLICATED BY SPACE GROUP SYMMETRY ******

BRAVAIS-            POSSIBLE SPACE-GROUPS FOR PROTEIN CRYSTALS
  TYPE                     [SPACE GROUP NUMBER,SYMBOL]
  aP      [1,P1]
  mP      [3,P2] [4,P2(1)]
 mC,mI    [5,C2]
  oP      [16,P222] [17,P222(1)] [18,P2(1)2(1)2] [19,P2(1)2(1)2(1)]
  oC      [21,C222] [20,C222(1)]
  oF      [22,F222]
  oI      [23,I222] [24,I2(1)2(1)2(1)]
  tP      [75,P4] [76,P4(1)] [77,P4(2)] [78,P4(3)] [89,P422] [90,P42(1)2]
          [91,P4(1)22] [92,P4(1)2(1)2] [93,P4(2)22] [94,P4(2)2(1)2]
          [95,P4(3)22] [96,P4(3)2(1)2]
  tI      [79,I4] [80,I4(1)] [97,I422] [98,I4(1)22]
  hP      [143,P3] [144,P3(1)] [145,P3(2)] [149,P312] [150,P321] [151,P3(1)12]
          [152,P3(1)21] [153,P3(2)12] [154,P3(2)21] [168,P6] [169,P6(1)]
          [170,P6(5)] [171,P6(2)] [172,P6(4)] [173,P6(3)] [177,P622]
          [178,P6(1)22] [179,P6(5)22] [180,P6(2)22] [181,P6(4)22] [182,P6(3)22]
  hR      [146,R3] [155,R32]
  cP      [195,P23] [198,P2(1)3] [207,P432] [208,P4(2)32] [212,P4(3)32]
          [213,P4(1)32]
  cF      [196,F23] [209,F432] [210,F4(1)32]
  cI      [197,I23] [199,I2(1)3] [211,I432] [214,I4(1)32]


 ********************* SYMMETRY OF REFLECTION INTENSITIES *********************

 Analysis of symmetry related reflections is based on strong data within a
 TEST_RESOLUTION_RANGE=    8.00    4.50 Angstrom (defined in XDS.INP).

 The symmetry test is carried out for the enantiomorphous space groups above
 (omitting those with screw axes) that conform with the observed lattice
 symmetry. The test is quantified by the redundancy independent R-factor,
 Rmeas, defined by Diederichs & Karplus, Nature Struct. Biol. 4, 269-275 (1997).

 For computation of Rmeas a minimum number of symmetry-related reflections is
 required and set by the user (in XDS.INP) as the parameter
                      MIN_RFL_Rmeas=   50

 Low values for Rmeas should be obtained if the crystal possesses the symmetry
 elements of the tested space group. The decision whether the crystal's data
 satisfy the requirements of the tested space group is based on a constant set
 by the user (in XDS.INP) as the parameter
                      MAX_FAC_Rmeas=      2.
 which provides an upper limit for acceptable Rmeas as a multiple of the
 lowest Rmeas found for all tested space groups. If Rmeas is larger than this
 upper limit, the corresponding space group symmetry is considered violated
 by the observed data.

 XDS will select (*) that space group that requires a minimum number of unique
 reflections to account for the observed intensities at an acceptable Rmeas.

 UNIQUE   = number of unique reflections
 Rmeas    = redundancy independent R-factor (intensities)
 COMPARED = number of reflections used for calculating Rmeas

 SPACE-GROUP         UNIT CELL CONSTANTS            UNIQUE   Rmeas  COMPARED  LATTICE-
   NUMBER      a      b      c   alpha beta gamma                            CHARACTER

       5      24.4   14.1    6.9  90.0  90.0  90.0       4     4.4        6    20 mC
     143      14.1   14.1    6.9  90.0  90.0 120.0       3    11.4        7    22 hP
     149      14.1   14.1    6.9  90.0  90.0 120.0       3    11.4        7    22 hP
     150      14.1   14.1    6.9  90.0  90.0 120.0       3    11.4        7    22 hP
     168      14.1   14.1    6.9  90.0  90.0 120.0       3    11.4        7    22 hP
     177      14.1   14.1    6.9  90.0  90.0 120.0       3    11.4        7    22 hP
      21      14.1   24.4    6.9  90.0  90.0  90.0       4     4.4        6    23 oC
       5      14.1   24.4    6.9  90.0  90.0  90.0       4     4.4        6    25 mC
       5      14.1   24.5    6.9  90.0  90.0  90.0       5     4.5        5    30 mC
       1       6.9   14.1   14.1  60.0  90.0  90.0       5     4.5        5    31 aP
      21      14.1   24.5    6.9  90.0  90.0  90.0       5     4.5        5    40 oC
       3      14.1    6.9   14.1  90.0 120.0  90.0       5     4.5        5    35 mP
       5      24.5   14.1    6.9  90.0  90.0  90.0       5     4.5        5    41 mC
       1       6.9   14.1   14.1 120.0  90.0  90.0       5     4.5        5    44 aP
 

 !!! WARNING !!! NONE OF THE SPACE GROUPS ABOVE IS ACCEPTABLE.
 XDS WILL CONTINUE WITH THE SPACE GROUP USED IN THE INTEGRATE STEP.


 ************ SELECTED SPACE GROUP AND UNIT CELL FOR THIS DATA SET ************

 SPACE_GROUP_NUMBER=    1
 UNIT_CELL_CONSTANTS=     6.93    14.12    14.12  59.973  90.002  90.007
 UNIT_CELL_A-AXIS=    -6.692     1.615    -0.812
 UNIT_CELL_B-AXIS=     3.092    13.668     1.707
 UNIT_CELL_C-AXIS=     3.278     7.954   -11.196
 REFLECTIONS H,K,L FROM "INTEGRATE.HKL" WILL BE REINDEXED BY
 H' = (  1*H +  0*K +  0*L)/ 1 +  0
 K' = (  0*H +  1*K +  0*L)/ 1 +  0
 L' = (  0*H +  0*K +  1*L)/ 1 +  0

 *****  1 EQUIVALENT POSITIONS IN SPACE GROUP #  1 *****

    If x',y',z' is an equivalent position to x,y,z, then
        x'=x*ML(1)+y*ML( 2)+z*ML( 3)+ML( 4)/12.0
        y'=x*ML(5)+y*ML( 6)+z*ML( 7)+ML( 8)/12.0
        z'=x*ML(9)+y*ML(10)+z*ML(11)+ML(12)/12.0

    #    1  2  3  4    5  6  7  8    9 10 11 12 
    1    1  0  0  0    0  1  0  0    0  0  1  0

 ******************************************************************************
      MEAN DISCREPANCIES BETWEEN OBSERVED AND CALCULATED SPOT LOCATIONS
 ******************************************************************************

 The discrepancies in X- and Y-coordinates of the spots are depicted in the
 two images DX-CORRECTIONS.cbf and DY-CORRECTIONS.cbf for inspection with
 the XDS-Viewer.



 ******************************************************************************
  REFINEMENT OF DIFFRACTION PARAMETERS USING ALL IMAGES
 ******************************************************************************


 REFINED VALUES OF DIFFRACTION PARAMETERS DERIVED FROM      2085 INDEXED SPOTS
 REFINED PARAMETERS:   POSITION BEAM AXIS ORIENTATION CELL
 STANDARD DEVIATION OF SPOT    POSITION (PIXELS)     0.19
 STANDARD DEVIATION OF SPINDLE POSITION (DEGREES)    0.03
 SPACE GROUP NUMBER      1
 UNIT CELL PARAMETERS      6.934    14.120    14.121  59.989  89.997  89.999
 E.S.D. OF CELL PARAMETERS  6.4E-04 8.1E-04 1.0E-03 1.5E-03 5.1E-03 5.0E-03
 REC. CELL PARAMETERS   0.144216  0.081789  0.081780 120.011  90.002  90.000
 COORDINATES OF UNIT CELL A-AXIS    -6.694     1.617    -0.811
 COORDINATES OF UNIT CELL B-AXIS     3.095    13.670     1.707
 COORDINATES OF UNIT CELL C-AXIS     3.277     7.952   -11.200
 CRYSTAL MOSAICITY (DEGREES)     0.123
 LAB COORDINATES OF ROTATION AXIS  0.999988 -0.001450  0.004755
 DIRECT BEAM COORDINATES (REC. ANGSTROEM)  -0.003123 -0.001533  1.333329
 DETECTOR COORDINATES (PIXELS) OF DIRECT BEAM    1002.25   1004.41
 DETECTOR ORIGIN (PIXELS) AT                     1005.06   1005.79
 CRYSTAL TO DETECTOR DISTANCE (mm)       179.87
 LAB COORDINATES OF DETECTOR X-AXIS  1.000000  0.000000  0.000000
 LAB COORDINATES OF DETECTOR Y-AXIS  0.000000  1.000000  0.000000


 THE DATA COLLECTION STATISTICS REPORTED BELOW ASSUMES:
 SPACE_GROUP_NUMBER=    1
 UNIT_CELL_CONSTANTS=     6.93    14.12    14.12  59.989  89.997  89.999


 ******************************************************************************
        MEAN INTENSITY AS FUNCTION OF SPINDLE POSITION WITHIN DATA IMAGE
 ******************************************************************************

 This statistics could serve as a diagnostic tool for detecting
 shutter problems (suggested by Kay Diederichs).
 Data are corrected for this effect if PATCH_SHUTTER_PROBLEM=TRUE in XDS.INP.
 ===> Selected : PATCH_SHUTTER_PROBLEM=FALSE

 INTERVAL = Angular interval in units of the oscillation range
            covered by a data image.
 NUMBER   = Number of reflections in each interval
 INTENSITY= Mean intensity of the reflections in each interval
 FACTOR   = Correction factor applied to intensities;
            INTENSITY(overall)/INTENSITY(interval)

   INTERVAL     NUMBER      INTENSITY      FACTOR
 -0.05  0.05       267      23506.503       0.785
  0.05  0.15       249      16759.920       1.101
  0.15  0.25       218      17680.502       1.043
  0.25  0.35       261      20326.764       0.907
  0.35  0.45       224      16124.710       1.144
  0.45  0.55       241      15584.324       1.184
  0.55  0.65       254      16898.902       1.091
  0.65  0.75       251      22705.343       0.812
  0.75  0.85       230      18785.439       0.982
  0.85  0.95       230      14957.128       1.233
 
 -0.05  0.95      2425      18444.949       1.000
 

 ******************************************************************************
           CORRECTION FACTORS AS FUNCTION OF IMAGE NUMBER & RESOLUTION
 ******************************************************************************

 RECIPROCAL CORRECTION FACTORS FOR INPUT DATA SETS MERGED TO
 OUTPUT FILE: XDS_ASCII.HKL                                     

 THE CALCULATIONS ASSUME         FRIEDEL'S_LAW= TRUE
 TOTAL NUMBER OF CORRECTION FACTORS DEFINED       20
 DEGREES OF FREEDOM OF CHI^2 FIT               727.0
 CHI^2-VALUE OF FIT OF CORRECTION FACTORS      1.005
 NUMBER OF CYCLES CARRIED OUT                      3

 CORRECTION FACTORS for visual inspection by XDS-Viewer DECAY.cbf           
 XMIN=     0.9 XMAX=   512.6 NXBIN=    1
 YMIN= 0.00669 YMAX= 0.81231 NYBIN=   20
 NUMBER OF REFLECTIONS USED FOR DETERMINING CORRECTION FACTORS       1496


 ******************************************************************************
  CORRECTION FACTORS AS FUNCTION OF X (fast) & Y(slow) IN THE DETECTOR PLANE
 ******************************************************************************

 RECIPROCAL CORRECTION FACTORS FOR INPUT DATA SETS MERGED TO
 OUTPUT FILE: XDS_ASCII.HKL                                     

 THE CALCULATIONS ASSUME         FRIEDEL'S_LAW= TRUE
 TOTAL NUMBER OF CORRECTION FACTORS DEFINED       30
 DEGREES OF FREEDOM OF CHI^2 FIT               727.0
 CHI^2-VALUE OF FIT OF CORRECTION FACTORS      0.997
 NUMBER OF CYCLES CARRIED OUT                      3

 CORRECTION FACTORS for visual inspection by XDS-Viewer MODPIX.cbf          
 XMIN=    30.1 XMAX=  1960.1 NXBIN=    5
 YMIN=    19.0 YMAX=  1983.5 NYBIN=    6
 NUMBER OF REFLECTIONS USED FOR DETERMINING CORRECTION FACTORS       1496


 ******************************************************************************
   CORRECTION FACTORS AS FUNCTION OF IMAGE NUMBER & DETECTOR SURFACE POSITION
 ******************************************************************************

 RECIPROCAL CORRECTION FACTORS FOR INPUT DATA SETS MERGED TO
 OUTPUT FILE: XDS_ASCII.HKL                                     

 THE CALCULATIONS ASSUME         FRIEDEL'S_LAW= TRUE
 TOTAL NUMBER OF CORRECTION FACTORS DEFINED       13
 DEGREES OF FREEDOM OF CHI^2 FIT               727.0
 CHI^2-VALUE OF FIT OF CORRECTION FACTORS      0.993
 NUMBER OF CYCLES CARRIED OUT                      3

 CORRECTION FACTORS for visual inspection by XDS-Viewer ABSORP.cbf          
 XMIN=     0.9 XMAX=   512.6 NXBIN=    1
 DETECTOR_SURFACE_POSITION=     995    1001
 DETECTOR_SURFACE_POSITION=    1323    1335
 DETECTOR_SURFACE_POSITION=     667    1335
 DETECTOR_SURFACE_POSITION=     667     668
 DETECTOR_SURFACE_POSITION=    1323     668
 DETECTOR_SURFACE_POSITION=    1737    1314
 DETECTOR_SURFACE_POSITION=    1302    1756
 DETECTOR_SURFACE_POSITION=     688    1756
 DETECTOR_SURFACE_POSITION=     253    1314
 DETECTOR_SURFACE_POSITION=     253     688
 DETECTOR_SURFACE_POSITION=     688     246
 DETECTOR_SURFACE_POSITION=    1302     246
 DETECTOR_SURFACE_POSITION=    1737     688
 NUMBER OF REFLECTIONS USED FOR DETERMINING CORRECTION FACTORS       1496


 ******************************************************************************
    CORRECTION PARAMETERS FOR THE STANDARD ERROR OF REFLECTION INTENSITIES
 ******************************************************************************

 The variance v0(I) of the intensity I obtained from counting statistics is
 replaced by v(I)=a*(v0(I)+b*I^2). The model parameters a, b are chosen to
 minimize the discrepancies between v(I) and the variance estimated from
 sample statistics of symmetry related reflections. This model implicates
 an asymptotic limit ISa=1/SQRT(a*b) for the highest I/Sigma(I) that the
 experimental setup can produce (Diederichs (2010) Acta Cryst D66, 733-740).

     a        b          ISa
 6.158E+00  5.146E-04   17.76


 ******************************************************************************
      STANDARD ERROR OF REFLECTION INTENSITIES AS FUNCTION OF RESOLUTION
      FOR DATA SET  XDS_ASCII.HKL                                     
 ******************************************************************************

  I/Sigma  = mean intensity/Sigma of a reflection in shell
  Chi^2    = goodness of fit between sample variances of
             symmetry-related intensities and their errors
             (Chi^2 = 1 for perfect agreement)
  R-FACTOR
  observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
  expected = expected R-FACTOR derived from Sigma(I)

   NUMBER  = number of reflections in resolution shell
             used for calculation of R-FACTOR
  ACCEPTED = number of accepted reflections
  REJECTED = number of rejected reflections (MISFITS),
             recognized by comparison with symmetry-related
             reflections.

 RESOLUTION RANGE  I/Sigma  Chi^2  R-FACTOR  R-FACTOR  NUMBER ACCEPTED REJECTED
                                   observed  expected

   12.229   3.537     9.97   1.07      4.18      3.71      34      36       0
    3.537   2.555    14.37   0.92      3.10      3.32     106     135       2
    2.555   2.102    16.23   1.10      2.99      3.21     100     132       2
    2.102   1.827    14.04   1.21      3.47      3.31     140     184      10
    1.827   1.638    13.31   1.04      3.92      3.35     162     220       0
    1.638   1.497    12.58   0.91      3.31      3.61     168     238       4
    1.497   1.388    12.15   0.99      3.72      3.59     178     252       2
    1.388   1.299    11.69   0.96      3.40      3.60     178     266       8
    1.299   1.226    10.52   1.04      3.45      3.74     198     300       8
    1.226   1.163    10.43   0.92      3.40      3.79     182     278       2
    1.163   1.110     9.73   0.81      3.12      3.86     204     344       2
   --------------------------------------------------------------------------
   12.229   1.110    11.96   0.98      3.38      3.48    1650    2385      40
 


 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR VARIOUS SUBSETS OF INCLUDED DATA IMAGES
 ******************************************************************************

 Data set statistics is reported below several times, each with a different
 upper limit on the number of images included. This provides the user with
 the information for deciding which data images should be excluded from the
 final data set because of radiation damage or other defects. If the user
 decides for a subset of "good" images that differs from the specification
 as given by the input parameter (see DATA_RANGE= in XDS.INP) the CORRECT-
 step of XDS must be repeated with the new parameter values for DATA_RANGE=.


 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR IMAGE   DATA_RANGE=       1      58
 ******************************************************************************


          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22           7       6        72        8.3%       4.0%      6.1%        2   12.88      5.7%     0.0      0    0.000       0
     2.32          16      16       121       13.2%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.91          31      31       192       16.1%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.66          25      25       167       15.0%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.48          35      35       233       15.0%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.36          38      38       247       15.4%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.26          44      44       257       17.1%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.18          38      38       262       14.5%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.11          46      46       314       14.6%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
    total         280     279      1865       15.0%       4.0%      6.1%        2   11.67      5.7%     0.0      0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES       283
 NUMBER OF REJECTED MISFITS                                 3
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                          280
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                    279



 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR IMAGE   DATA_RANGE=       1     115
 ******************************************************************************


          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22          15      11        72       15.3%       1.6%      3.3%        8   11.93      2.3%   100.0*     0    0.000       0
     2.32          27      22       121       18.2%       2.8%      3.4%       10   15.13      4.0%   100.0*     0    0.000       0
     1.91          51      48       192       25.0%       2.0%      3.2%        6   15.67      2.8%   100.0*     0    0.000       0
     1.66          51      48       167       28.7%       1.4%      3.6%        6   14.51      2.0%   100.0*     0    0.000       0
     1.48          74      74       233       31.8%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.36          68      68       247       27.5%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.26          79      79       257       30.7%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.18          79      79       262       30.2%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
     1.11          83      83       314       26.4%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
    total         527     512      1865       27.5%       2.1%      3.3%       30   11.41      3.0%    99.9*     0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES       537
 NUMBER OF REJECTED MISFITS                                10
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                          527
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                    512



 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR IMAGE   DATA_RANGE=       1     172
 ******************************************************************************


          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22          24      15        72       20.8%       2.3%      3.4%       18   14.90      3.3%   100.0*     0    0.000       0
     2.32          42      31       121       25.6%       3.3%      3.4%       22   15.48      4.6%    99.9*     0    0.000       0
     1.91          82      67       192       34.9%       3.4%      3.3%       30   16.57      4.7%    99.7*     0    0.000       0
     1.66          76      64       167       38.3%       1.7%      3.7%       24   14.96      2.4%   100.0*     0    0.000       0
     1.48         106      95       233       40.8%       2.8%      4.0%       22   12.59      4.0%    99.9*     0    0.000       0
     1.36         104      97       247       39.3%       3.2%      3.5%       14   12.93      4.5%    99.9*     0    0.000       0
     1.26         120     112       257       43.6%       1.7%      3.5%       16    9.58      2.4%   100.0*     0    0.000       0
     1.18         118     114       262       43.5%       3.1%      3.3%        8    9.73      4.4%   100.0*     0    0.000       0
     1.11         124     124       314       39.5%     -99.9%    -99.9%        0  -99.00    -99.9%     0.0      0    0.000       0
    total         796     719      1865       38.6%       2.9%      3.4%      154   11.89      4.1%    99.8*     0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES       809
 NUMBER OF REJECTED MISFITS                                13
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                          796
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                    719



 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR IMAGE   DATA_RANGE=       1     229
 ******************************************************************************


          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22          30      18        72       25.0%       2.1%      3.4%       24   16.05      2.9%    99.9*     0    0.000       0
     2.32          60      43       121       35.5%       3.1%      3.4%       34   16.47      4.4%    99.9*     0    0.000       0
     1.91         106      83       192       43.2%       3.8%      3.2%       46   17.04      5.4%    99.3*     0    0.000       0
     1.66         101      79       167       47.3%       4.4%      3.4%       44   15.22      6.3%    99.5*     0    0.000       0
     1.48         141     114       233       48.9%       5.9%      4.0%       54   12.97      8.3%    98.8*     0    0.000       0
     1.36         139     118       247       47.8%       3.7%      3.5%       42   13.83      5.2%    99.6*     0    0.000       0
     1.26         155     133       257       51.8%       2.6%      3.7%       44   10.03      3.7%   100.0*     0    0.000       0
     1.18         157     139       262       53.1%       3.9%      3.6%       36   10.61      5.5%   100.0*     0    0.000       0
     1.11         166     153       314       48.7%       3.9%      3.5%       26    9.93      5.6%    99.4*     0    0.000       0
    total        1055     880      1865       47.2%       3.8%      3.4%      350   12.56      5.3%    99.6*     0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES      1072
 NUMBER OF REJECTED MISFITS                                17
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                         1055
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                    880



 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR IMAGE   DATA_RANGE=       1     285
 ******************************************************************************


          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22          35      20        72       27.8%       1.9%      3.3%       30   16.85      2.7%    99.9*     0    0.000       0
     2.32          75      51       121       42.1%       2.6%      3.4%       48   16.81      3.7%    99.9*     0    0.000       0
     1.91         136     100       192       52.1%       3.4%      3.2%       72   17.46      4.8%    99.7*     0    0.000       0
     1.66         127      91       167       54.5%       3.4%      3.4%       72   16.06      4.9%    99.4*     0    0.000       0
     1.48         176     132       233       56.7%       3.7%      3.7%       88   13.65      5.2%    99.5*     0    0.000       0
     1.36         177     140       247       56.7%       3.8%      3.5%       74   14.26      5.3%    99.5*     0    0.000       0
     1.26         190     155       257       60.3%       2.9%      3.8%       70   10.52      4.1%   100.0*     0    0.000       0
     1.18         193     159       262       60.7%       4.4%      4.0%       68   11.12      6.3%   100.0*     0    0.000       0
     1.11         212     180       314       57.3%       4.1%      4.0%       64   10.26      5.8%    99.9*     0    0.000       0
    total        1321    1028      1865       55.1%       3.4%      3.5%      586   13.08      4.8%    99.7*     0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES      1345
 NUMBER OF REJECTED MISFITS                                24
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                         1321
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                   1028



 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR IMAGE   DATA_RANGE=       1     342
 ******************************************************************************


          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22          44      25        72       34.7%       2.4%      3.3%       38   16.47      3.4%    99.8*     0    0.000       0
     2.32          91      57       121       47.1%       2.8%      3.3%       68   17.55      4.0%    99.7*     0    0.000       0
     1.91         161     110       192       57.3%       3.2%      3.2%      102   18.05      4.6%    99.7*     0    0.000       0
     1.66         153     106       167       63.5%       3.7%      3.3%       94   16.36      5.2%    99.5*     0    0.000       0
     1.48         213     151       233       64.8%       3.6%      3.7%      124   14.09      5.1%    99.6*     0    0.000       0
     1.36         216     163       247       66.0%       3.7%      3.6%      106   14.51      5.3%    99.5*     0    0.000       0
     1.26         228     173       257       67.3%       3.0%      3.8%      110   11.09      4.3%    99.9*     0    0.000       0
     1.18         233     179       262       68.3%       4.2%      4.0%      108   11.52      5.9%    99.8*     0    0.000       0
     1.11         261     211       314       67.2%       3.8%      4.1%      100   10.52      5.3%    99.8*     0    0.000       0
    total        1600    1175      1865       63.0%       3.4%      3.5%      850   13.47      4.8%    99.6*     0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES      1625
 NUMBER OF REJECTED MISFITS                                25
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                         1600
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                   1175



 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR IMAGE   DATA_RANGE=       1     399
 ******************************************************************************


          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22          49      27        72       37.5%       2.4%      3.3%       44   16.67      3.4%    99.9*     0    0.000       0
     2.32         106      65       121       53.7%       2.7%      3.3%       82   18.10      3.8%    99.8*     0    0.000       0
     1.91         186     124       192       64.6%       3.0%      3.2%      124   18.34      4.2%    99.6*     0    0.000       0
     1.66         179     118       167       70.7%       3.4%      3.3%      122   16.74      4.8%    99.4*     0    0.000       0
     1.48         249     170       233       73.0%       3.4%      3.6%      158   14.40      4.8%    99.6*     0    0.000       0
     1.36         250     182       247       73.7%       3.3%      3.5%      136   14.89      4.7%    99.6*     0    0.000       0
     1.26         265     189       257       73.5%       2.6%      3.7%      152   11.59      3.6%    99.9*     0    0.000       0
     1.18         269     196       262       74.8%       3.4%      3.9%      146   11.84      4.9%    99.8*     0    0.000       0
     1.11         303     233       314       74.2%       2.9%      3.9%      140   10.85      4.1%    99.9*     0    0.000       0
    total        1856    1304      1865       69.9%       3.1%      3.5%     1104   13.86      4.3%    99.7*     0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES      1883
 NUMBER OF REJECTED MISFITS                                27
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                         1856
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                   1304



 ******************************************************************************
  SUMMARY OF DATA SET STATISTICS FOR IMAGE   DATA_RANGE=       1     456
 ******************************************************************************


          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22          55      30        72       41.7%       2.6%      3.3%       50   17.22      3.7%    99.8*     0    0.000       0
     2.32         122      75       121       62.0%       2.6%      3.3%       94   18.07      3.7%    99.8*     0    0.000       0
     1.91         213     136       192       70.8%       3.1%      3.2%      154   18.82      4.3%    99.6*     0    0.000       0
     1.66         203     131       167       78.4%       3.4%      3.3%      144   16.71      4.8%    99.6*     0    0.000       0
     1.48         281     187       233       80.3%       3.5%      3.7%      188   14.66      5.0%    99.6*     0    0.000       0
     1.36         290     201       247       81.4%       3.3%      3.5%      178   15.42      4.6%    99.6*     0    0.000       0
     1.26         302     207       257       80.5%       2.8%      3.8%      190   11.96      3.9%   100.0*     0    0.000       0
     1.18         307     218       262       83.2%       3.5%      3.7%      178   12.18      5.0%    99.8*     0    0.000       0
     1.11         346     256       314       81.5%       2.9%      3.8%      180   11.13      4.1%    99.9*     0    0.000       0
    total        2119    1441      1865       77.3%       3.1%      3.5%     1356   14.19      4.4%    99.7*     0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES      2154
 NUMBER OF REJECTED MISFITS                                35
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                         2119
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                   1441



 ******************************************************************************
  STATISTICS OF SAVED DATA SET "XDS_ASCII.HKL" (DATA_RANGE=       1     513)
 FILE TYPE:         XDS_ASCII      MERGE=FALSE          FRIEDEL'S_LAW=TRUE 
 ******************************************************************************

   REFLECTIONS OF TYPE H,0,0  0,K,0  0,0,L OR EXPECTED TO BE ABSENT (*)
   --------------------------------------------------------------------

   H    K    L  RESOLUTION  INTENSITY     SIGMA    INTENSITY/SIGMA  #OBSERVED

    0    0    1    12.228  -0.1579E+01  0.2703E+02        -0.06           2 
    0    0    2     6.114   0.1676E+03  0.6020E+02         2.78           2 
    0    0    3     4.076   0.1975E+04  0.1203E+03        16.41           2 
    0    0    5     2.446   0.4791E+04  0.2400E+03        19.96           2 
    0    0    6     2.038   0.1856E+06  0.7412E+04        25.04           2 
    0    0    7     1.747   0.3082E+05  0.1255E+04        24.56           2 
    0    0    8     1.528   0.2013E+04  0.1671E+03        12.05           2 
    0    0    9     1.359   0.4865E+05  0.1971E+04        24.69           2 
    0    0   10     1.223   0.1964E+06  0.7856E+04        25.01           2 
    0    0   11     1.112   0.2637E+05  0.1575E+04        16.75           1 
    0    9    0     1.359   0.5930E+05  0.3384E+04        17.52           1 
    0   10    0     1.223   0.2316E+06  0.1308E+05        17.70           1 
    1    0    0     6.934   0.4260E+02  0.2820E+02         1.51           2 
    3    0    0     2.311   0.1333E+02  0.7306E+02         0.18           1 
    4    0    0     1.734   0.4131E+03  0.5409E+02         7.64           1 

          COMPLETENESS AND QUALITY OF DATA SET
          ------------------------------------

 R-FACTOR
 observed = (SUM(ABS(I(h,i)-I(h))))/(SUM(I(h,i)))
 expected = expected R-FACTOR derived from Sigma(I)

 COMPARED = number of reflections used for calculating R-FACTOR
 I/SIGMA  = mean of intensity/Sigma(I) of unique reflections
            (after merging symmetry-related observations)
 Sigma(I) = standard deviation of reflection intensity I
            estimated from sample statistics

 R-meas   = redundancy independent R-factor (intensities)
            Diederichs & Karplus (1997), Nature Struct. Biol. 4, 269-275.

 CC(1/2)  = percentage of correlation between intensities from
            random half-datasets. Correlation significant at
            the 0.1% level is marked by an asterisk.
            Karplus & Diederichs (2012), Science 336, 1030-33
 Anomal   = percentage of correlation between random half-sets
  Corr      of anomalous intensity differences. Correlation
            significant at the 0.1% level is marked.
 SigAno   = mean anomalous difference in units of its estimated
            standard deviation (|F(+)-F(-)|/Sigma). F(+), F(-)
            are structure factor estimates obtained from the
            merged intensity observations in each parity class.
  Nano    = Number of unique reflections used to calculate
            Anomal_Corr & SigAno. At least two observations
            for each (+ and -) parity are required.


 SUBSET OF INTENSITY DATA WITH SIGNAL/NOISE >= -3.0 AS FUNCTION OF RESOLUTION
 RESOLUTION     NUMBER OF REFLECTIONS    COMPLETENESS R-FACTOR  R-FACTOR COMPARED I/SIGMA   R-meas  CC(1/2)  Anomal  SigAno   Nano
   LIMIT     OBSERVED  UNIQUE  POSSIBLE     OF DATA   observed  expected                                      Corr

     3.22          63      35        72       48.6%       2.8%      3.3%       56   17.63      3.9%    99.8*     0    0.000       0
     2.32         138      83       121       68.6%       3.4%      3.3%      110   18.19      4.8%    99.5*     0    0.000       0
     1.91         237     150       192       78.1%       3.2%      3.2%      174   18.92      4.5%    99.6*     0    0.000       0
     1.66         227     142       167       85.0%       3.7%      3.3%      170   17.08      5.2%    99.5*     0    0.000       0
     1.48         314     202       233       86.7%       3.8%      3.6%      224   14.86      5.4%    99.5*     0    0.000       0
     1.36         331     219       247       88.7%       3.3%      3.5%      224   15.82      4.7%    99.6*     0    0.000       0
     1.26         339     223       257       86.8%       3.2%      3.7%      232   12.35      4.5%    99.9*     0    0.000       0
     1.18         344     232       262       88.5%       3.7%      3.8%      224   12.67      5.3%    99.8*     0    0.000       0
     1.11         392     274       314       87.3%       3.3%      3.9%      236   11.54      4.6%    99.9*     0    0.000       0
    total        2385    1560      1865       83.6%       3.4%      3.5%     1650   14.56      4.8%    99.6*     0    0.000       0


 NUMBER OF REFLECTIONS IN SELECTED SUBSET OF IMAGES      2425
 NUMBER OF REJECTED MISFITS                                40
 NUMBER OF SYSTEMATIC ABSENT REFLECTIONS                    0
 NUMBER OF ACCEPTED OBSERVATIONS                         2385
 NUMBER OF UNIQUE ACCEPTED REFLECTIONS                   1560



 ******************************************************************************
    WILSON STATISTICS OF DATA SET  "XDS_ASCII.HKL"
 ******************************************************************************

 Data is divided into resolution shells and a straight line 
 A - 2*B*SS is fitted to log<I>, where
   RES    = mean resolution (Angstrom) in shell
   SS     = mean of (sin(THETA)/LAMBDA)**2 in shell
   <I>    = mean reflection intensity in shell
   BO     = (A - log<I>)/(2*SS)
    #     = number of reflections in resolution shell

   WILSON LINE (using all data) : A=  10.519 B=   3.379 CORRELATION=  0.65
      #      RES      SS        <I>       log(<I>)       BO
       6     7.039   0.005  1.1143E+04       9.319     119.0
      28     3.604   0.019  3.0271E+04      10.318       5.2
      46     2.932   0.029  2.5600E+04      10.150       6.3
      37     2.548   0.038  5.2942E+04      10.877      -4.6
      59     2.224   0.051  5.9985E+04      11.002      -4.8
      43     2.046   0.060  4.5793E+04      10.732      -1.8
      77     1.904   0.069  1.8481E+04       9.825       5.0
      79     1.749   0.082  2.7379E+04      10.218       1.8
      84     1.657   0.091  2.6585E+04      10.188       1.8
      93     1.558   0.103  1.6270E+04       9.697       4.0
      92     1.492   0.112  1.1117E+04       9.316       5.4
     108     1.416   0.125  1.3583E+04       9.517       4.0
      90     1.370   0.133  1.4571E+04       9.587       3.5
     115     1.312   0.145  9.7793E+03       9.188       4.6
     112     1.269   0.155  1.4930E+04       9.611       2.9
      97     1.230   0.165  1.9338E+04       9.870       2.0
     129     1.192   0.176  7.0063E+03       8.855       4.7
     136     1.154   0.188  1.3841E+04       9.535       2.6
     127     1.123   0.198  7.4793E+03       8.920       4.0


 HIGHER ORDER MOMENTS OF WILSON DISTRIBUTION OF  CENTRIC DATA
    AS COMPARED WITH THEORETICAL VALUES. (EXPECTED: 1.00)    
      #      RES        <I**2>/      <I**3>/      <I**4>/  
                         3<I>**2     15<I>**3    105<I>**4 

       0   overall        0.000        0.000        0.000


 HIGHER ORDER MOMENTS OF WILSON DISTRIBUTION OF ACENTRIC DATA
    AS COMPARED WITH THEORETICAL VALUES. (EXPECTED: 1.00)    
      #      RES        <I**2>/      <I**3>/      <I**4>/  
                         2<I>**2      6<I>**3     24<I>**4 

       6     7.039        1.499        1.520        1.165
      28     3.604        1.744        2.644        3.272
      46     2.932        2.030        5.735       15.310
      37     2.548        1.708        2.639        3.602
      59     2.224        0.958        0.794        0.592
      43     2.046        2.270        4.422        6.766
      77     1.904        0.972        0.799        0.561
      79     1.749        1.354        1.750        1.922
      84     1.657        1.547        2.382        3.314
      93     1.558        1.561        2.311        2.993
      92     1.492        1.314        1.823        2.234
     108     1.416        1.525        2.123        2.493
      90     1.370        1.326        1.655        1.800
     115     1.312        1.031        0.866        0.605
     112     1.269        3.420       13.941       49.128
      97     1.230        2.168        6.335       16.532
     129     1.192        1.710        2.989        4.523
     136     1.154        2.940       11.321       38.536
     127     1.123        2.283        6.410       16.599
    1558   overall        1.831        4.401       11.398

   ======= CUMULATIVE INTENSITY DISTRIBUTION =======
 DEFINITIONS:
   <I>    = mean reflection intensity
 Na(Z)exp = expected number of acentric reflections with I <= Z*<I>
 Na(Z)obs = observed number of acentric reflections with I <= Z*<I>
 Nc(Z)exp = expected number of  centric reflections with I <= Z*<I>
 Nc(Z)obs = observed number of  centric reflections with I <= Z*<I>



 Nc(Z)obs/Nc(Z)exp versus resolution and Z (0.1-1.0)
      #      RES     0.1   0.2   0.3   0.4   0.5   0.6   0.7   0.8   0.9   1.0

       0   overall  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00  0.00


 Na(Z)obs/Na(Z)exp versus resolution and Z (0.1-1.0)
      #      RES     0.1   0.2   0.3   0.4   0.5   0.6   0.7   0.8   0.9   1.0

       6     7.039  7.01  3.68  2.57  2.02  1.69  1.48  1.32  1.21  1.12  1.05
      28     3.604  3.00  2.36  2.07  1.73  1.82  1.66  1.49  1.36  1.26  1.19
      46     2.932  2.74  2.16  1.76  1.65  1.44  1.25  1.12  1.03  1.03  0.96
      37     2.548  3.98  3.28  2.61  2.05  1.72  1.50  1.34  1.23  1.14  1.07
      59     2.224  1.42  1.12  1.63  1.29  1.16  1.05  0.98  1.02  0.97  0.94
      43     2.046  3.18  1.92  1.97  2.33  1.95  1.70  1.52  1.39  1.45  1.36
      77     1.904  2.87  1.50  1.10  1.14  1.12  1.04  1.01  0.94  0.88  0.92
      79     1.749  2.79  1.82  1.27  1.19  1.22  1.12  1.01  1.01  1.13  1.16
      84     1.657  4.63  2.50  1.93  1.55  1.30  1.16  1.06  1.02  1.04  1.07
      93     1.558  1.13  1.72  2.12  1.73  1.72  1.53  1.45  1.33  1.23  1.16
      92     1.492  1.83  0.96  1.05  1.25  1.05  1.11  1.17  1.09  1.08  1.10
     108     1.416  1.95  1.43  1.82  1.60  1.48  1.50  1.40  1.31  1.23  1.19
      90     1.370  2.22  1.47  1.29  1.28  1.30  1.38  1.26  1.23  1.14  1.09
     115     1.312  1.74  1.82  1.58  1.42  1.30  1.18  1.11  1.06  1.01  0.95
     112     1.269  3.38  2.71  2.41  2.14  1.82  1.64  1.49  1.36  1.29  1.23
      97     1.230  2.06  1.76  1.87  1.47  1.23  1.07  0.96  0.95  0.96  0.99
     129     1.192  2.61  2.10  1.59  1.50  1.40  1.31  1.20  1.18  1.16  1.14
     136     1.154  3.55  2.27  1.79  1.49  1.49  1.39  1.26  1.18  1.13  1.11
     127     1.123  2.73  2.00  1.85  1.62  1.52  1.50  1.45  1.36  1.26  1.21
    1558   overall  2.62  1.91  1.73  1.55  1.42  1.33  1.24  1.17  1.13  1.10


 List of     12 reflections *NOT* obeying Wilson distribution (Z> 10.0)

   h    k    l     RES      Z     Intensity    Sigma

    0    9   -1    1.28   16.04  0.2395E+06  0.1353E+05 "alien"
    0   10   -1    1.16   15.80  0.2186E+06  0.1236E+05 "alien"
    0    1   10    1.28   13.75  0.2053E+06  0.8203E+04 "alien"
    0    1   11    1.16   13.67  0.1892E+06  0.7567E+04 "alien"
    0   10    9    1.28   13.01  0.1943E+06  0.7767E+04 "alien"
    0   11   10    1.16   12.62  0.1747E+06  0.9884E+04 "alien"
    0   10    0    1.22   11.97  0.2316E+06  0.1308E+05 "alien"
    0    9   -3    1.13   11.80  0.8826E+05  0.5021E+04 "alien"
    0    4    4    3.06   11.36  0.2907E+06  0.1639E+05 "alien"
    0    3   12    1.13   11.10  0.8304E+05  0.3343E+04 "alien"
    0   12    9    1.13   10.90  0.8151E+05  0.4646E+04 "alien"
    0    0   10    1.22   10.17  0.1966E+06  0.7864E+04 "alien"


 List of     12 reflections *NOT* obeying Wilson distribution (sorted by resolution)
 Ice rings could occur at (Angstrom):
 3.897,3.669,3.441, 2.671,2.249,2.072, 1.948,1.918,1.883,1.721

   h    k    l     RES      Z     Intensity    Sigma

    0    9   -3    1.13   11.80  0.8826E+05  0.5021E+04
    0    3   12    1.13   11.10  0.8304E+05  0.3343E+04
    0   12    9    1.13   10.90  0.8151E+05  0.4646E+04
    0   10   -1    1.16   15.80  0.2186E+06  0.1236E+05
    0    1   11    1.16   13.67  0.1892E+06  0.7567E+04
    0   11   10    1.16   12.62  0.1747E+06  0.9884E+04
    0   10    0    1.22   11.97  0.2316E+06  0.1308E+05
    0    0   10    1.22   10.17  0.1966E+06  0.7864E+04
    0    9   -1    1.28   16.04  0.2395E+06  0.1353E+05
    0    1   10    1.28   13.75  0.2053E+06  0.8203E+04
    0   10    9    1.28   13.01  0.1943E+06  0.7767E+04
    0    4    4    3.06   11.36  0.2907E+06  0.1639E+05

 NUMBER OF UNIQUE ALIEN REFLECTIONS WITH A Z-SCORE ABOVE LIMIT         0
 (ALIENS ABOVE LIMIT (REJECT_ALIEN=      20.0) ARE MARKED INVALID)

 NUMBER OF REFLECTION RECORDS ON OUTPUT FILE "XDS_ASCII.HKL"        2425
 NUMBER OF ACCEPTED OBSERVATIONS (INCLUDING SYSTEMATIC ABSENCES)    2385
 NUMBER OF REJECTED MISFITS & ALIENS (marked by -1*SIGMA(IOBS))       40


 cpu time used                  0.2 sec
 elapsed wall-clock time        0.3 sec
