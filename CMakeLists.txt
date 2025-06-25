cmake_minimum_required(VERSION 3.10)
project(Meerkat2)

include(cmake/hdf5.cmake)
include(cmake/CBFlib.cmake)

#set(LIBCBF_DIR lib/CBFlib-0.9.3.1)
#set(LIBCBF_DIR lib/CBFlib-0.9.6)
set(LIBEIGEN_DIR lib/eigen-3.4.0)

set(CMAKE_CXX_STANDARD 11)

include_directories(${LIBCBF_DIR}/include ${LIBEIGEN_DIR})
link_directories(${LIBHDF5_DIR}/lib ${LIBCBF_DIR}/lib)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") #-O0

set(SOURCE_FILES
        misc.cpp
        misc.h
        #ImageLoader.cpp
        #ImageLoader.h
        Geometry.cpp
        Geometry.h
        OutputData.cpp
        OutputData.h
        ReconstructionParameters.h
        ReconstructionParameters.cpp
        Corrections.cpp
        Corrections.h
        #CBFDataReader.cpp
        Hdf5HelperFuncitons.h
        Hdf5HelperFunctions.cpp
        HDFImageLoader.cpp
        #CBFImageLoader.cpp
        AbstractImageLoader.cpp
        ImageLoaderFactory.cpp
        HDFDataReader.cpp)

add_library(meerkat2-lib ${SOURCE_FILES})
set_target_properties(meerkat2-lib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

add_executable(Meerkat2 main.cpp)
set_target_properties(Meerkat2 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_link_libraries(Meerkat2 meerkat2-lib ${HDF5_LIBRARIES}) #libcbf.a

DownloadHDF5For(meerkat2-lib)
#DownloadCBFFor(meerkat2-lib)

#add_executable(TestYellFormat TestYellFormat.cpp)
#target_link_libraries(TestYellFormat meerkat2-lib ${HDF5_LIBRARIES})


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/lib/cxxtest/build_tools/cmake")
find_package(CxxTest)

if(CXXTEST_FOUND)
    include_directories(${CXXTEST_INCLUDES})
    cxx_test(test-meerkat test_meerkat.h)
    target_link_libraries(test-meerkat meerkat2-lib libcbf.a)
endif()
