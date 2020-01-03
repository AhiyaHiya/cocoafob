cmake_minimum_required(VERSION 3.16.2)
include(ExternalProject)

# Install path variable has to be set prior to creating project.
SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install CACHE PATH "Default path override")

# Name used for sln/xcproj/etc.
project(cocoafob VERSION 1.0)

# C++17 would be nice to use
SET(CMAKE_CXX_STANDARD 17)

# Search for C++ files in the project
file(GLOB SOURCES_UT "ctest/*.cpp")
file(GLOB SOURCES_CF "source/*.cpp")

# For Catch2 and OpenSSL 
SET(THIRD_PARTY_PATH "${CMAKE_BINARY_DIR}/external/third_party")

# We need Catch2 for unit testing
SET(CATCH2_PATH "${THIRD_PARTY_PATH}/catch2")
if( NOT EXISTS "${CATCH2_PATH}" )
    message("Catch2 header file not found; attempting to download header from GitHub")

    file(MAKE_DIRECTORY "${CATCH2_PATH}/include")
    # execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${directory})

    file(DOWNLOAD https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp 
    "${CATCH2_PATH}/include/catch2/catch.hpp")
endif()

# We need OpenSSL for basic functionality
SET(OPENSSL_CMAKE_PATH "${THIRD_PARTY_PATH}/openssl-cmake")
SET(BUILD_OPENSSL ON CACHE BOOL "We need to build OpenSSL")
SET(OPENSSL_BRANCH OpenSSL_1_0_2-stable CACHE STRING "Version needed")

if( NOT EXISTS "${OPENSSL_CMAKE_DIR}" )
    message("openssl-cmake project not found; attempting to clone repo from GitHub")

    execute_process(COMMAND git clone git@github.com:viaduck/openssl-cmake.git
                    WORKING_DIRECTORY ${THIRD_PARTY_PATH})
endif()

add_subdirectory(${OPENSSL_CMAKE_PATH})

# include_directories(${EXTERNAL_INSTALL_LOCATION}/include)
# link_directories(${EXTERNAL_INSTALL_LOCATION}/lib)
# 

# Set up the unit test target
add_executable(cocoafob_unittests ${SOURCES_UT} ${SOURCES_CF})

# Set up the static library target
add_library(cocoafob_staticlib STATIC ${SOURCES_CF})


# Set up dependencies
add_dependencies(cocoafob_staticlib openssl-cmake)

# Set the header search path for the unit test target
target_include_directories(cocoafob_unittests PRIVATE "${THIRD_PARTY_PATH}/catch2/include")



