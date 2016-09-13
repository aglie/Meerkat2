cmake_minimum_required(VERSION 3.3)
project(Meerkat2)

set(LIBCBF_DIR lib/CBFlib-0.9.3.1)
set(LIBHDF5_DIR lib/hdf5)

set(HDF5_LIBRARIES hdf5_hl_cpp hdf5_cpp hdf5_hl hdf5 szip z )

#I am using slightly newer LIBHDF5 than the one in cbf lib
include_directories(${LIBHDF5_DIR}/include ${LIBCBF_DIR}/include)
link_directories(${LIBHDF5_DIR}/lib ${LIBCBF_DIR}/lib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3") #

set(SOURCE_FILES
        misc.cpp
        misc.h
        ImageLoader.cpp
        ImageLoader.h
        Geometry.cpp
        Geometry.h
        OutputData.cpp
        OutputData.h
        ReconstructionParameters.h
        ReconstructionParameters.cpp
        Corrections.cpp
        Corrections.h)
add_library(meerkat2-lib ${SOURCE_FILES})
add_executable(Meerkat2 main.cpp)
target_link_libraries(Meerkat2 meerkat2-lib libcbf.a ${HDF5_LIBRARIES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/lib/cxxtest/build_tools/cmake")
find_package(CxxTest)

if(CXXTEST_FOUND)
    include_directories(${CXXTEST_INCLUDES})
    cxx_test(test-meerkat test_meerkat.h)
    target_link_libraries(test-meerkat meerkat2-lib libcbf.a)
endif()
