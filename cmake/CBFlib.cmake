cmake_minimum_required(VERSION 3.10)
function(DownloadCBFFor targetName)
    message(STATUS "CBF library will be downloaded and compiled statically")
    set(CBF_PREFIX ${CMAKE_BINARY_DIR}/cbflib)
    set(CBF_INSTALL_BIN_DIR ${CBF_PREFIX}/install)
    set(CBF_INSTALL_LIB_DIR ${CBF_PREFIX}/install)
    set(CBF_INSTALL_INCLUDE_DIR ${CBF_PREFIX}/install/include)
    set(CBF_INSTALL_DATA_DIR ${CBF_PREFIX}/install)
    include(ExternalProject)
    ExternalProject_Add(
            download_cbf
            URL https://git.3lp.cx/packages/CBFlib-0.9.6.tar.gz
            URL_MD5 67cae8a75d57185afa3e954816e75e19
            PREFIX ${CBF_PREFIX}
            INSTALL_DIR ${CBF_INSTALL_BIN_DIR}
            CMAKE_ARGS "${CMAKE_ARGS}"
            CMAKE_ARGS
                "-DCMAKE_INSTALL_PREFIX=${CBF_PREFIX}"
                "-DCMAKE_POLICY_VERSION_MINIMUM=3.10"
    )
    add_library(cbf_local STATIC IMPORTED)
    add_dependencies(cbf_local download_cbf)
    if (UNIX)
        set(CMAKE_DL_LIBS dl)
    endif ()
    target_link_libraries(cbf_local INTERFACE ${CMAKE_DL_LIBS})
    if (WIN32)
        set(STUPID_PREFIX "lib")
    endif ()
    set(lib_cbf_name ${CMAKE_STATIC_LIBRARY_PREFIX}${STUPID_PREFIX}cbf${CMAKE_STATIC_LIBRARY_SUFFIX})
    set_target_properties(cbf_local PROPERTIES IMPORTED_LOCATION ${CBF_PREFIX}/src/download_cbf-build/lib/${lib_cbf_name})
    add_dependencies(${targetName} download_cbf)
    target_include_directories(${targetName} PUBLIC ${CBF_PREFIX}/src/download_cbf/include)
#    target_link_libraries(${targetName} cbf_local)
    file(MAKE_DIRECTORY ${CBF_INSTALL_INCLUDE_DIR})
endfunction()
