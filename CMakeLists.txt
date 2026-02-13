cmake_minimum_required(VERSION 3.24)
project(Meerkat2)

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
    set(TARGET_ARCH "arm64" CACHE STRING "Target architecture for macOS (e.g., arm64, x86_64).")
    set(CMAKE_OSX_ARCHITECTURES "${TARGET_ARCH}" CACHE STRING "OSX Architectures" FORCE)

    # Argument that will be passed to hdf5 and bitshuffle
    set(ARCH_CMAKE_ARG "-DCMAKE_OSX_ARCHITECTURES=${TARGET_ARCH}")
else()
    set(ARCH_CMAKE_ARG "")
endif()


include(cmake/hdf5.cmake)
include(cmake/CBFlib.cmake)

include(ExternalProject)
set(LIBEIGEN_DIR ${CMAKE_BINARY_DIR}/eigen-install)

ExternalProject_Add(
        eigen
        URL  https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz
        #SOURCE_DIR ${EIGEN_PATH}
        #BINARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/eigen"
        #INSTALL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libs/eigen-install"
        CMAKE_ARGS
        #-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
        -DCMAKE_INSTALL_PREFIX=${LIBEIGEN_DIR}
)

set(CMAKE_CXX_STANDARD 11)

include_directories(${LIBCBF_DIR}/include ${LIBEIGEN_DIR}/include/eigen3 ${CMAKE_SOURCE_DIR}/libs)
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
        Hdf5HelperFuncitons.h
        Hdf5HelperFunctions.cpp
        HDFImageLoader.cpp
        CBFImageLoader.cpp
        AbstractImageLoader.cpp
        ImageLoaderFactory.cpp
        HDFDataReader.cpp
        libs/nanocbf/cbfframe.cpp)

add_library(meerkat2-lib ${SOURCE_FILES})
DownloadHDF5For(meerkat2-lib)


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
add_dependencies(meerkat2-lib eigen)
target_link_libraries(Meerkat2 meerkat2-lib) #libcbf.a ${HDF5_LIBRARIES}

#add_executable(TestYellFormat TestYellFormat.cpp)
#target_link_libraries(TestYellFormat meerkat2-lib ${HDF5_LIBRARIES})

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/lib/cxxtest/build_tools/cmake")
#find_package(CxxTest)
#
#if(CXXTEST_FOUND)
#    include_directories(${CXXTEST_INCLUDES})
#    cxx_test(test-meerkat test_meerkat.h)
#    target_link_libraries(test-meerkat meerkat2-lib libcbf.a)
#endif()
