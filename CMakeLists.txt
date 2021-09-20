cmake_minimum_required(VERSION 3.18)

project(
  DynaDBG
  VERSION 1.0
)

option(BUILD_DynaDBG_BENCHMARK "Build benchmark" ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

include(CheckCXXCompilerFlag)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(include)
file(GLOB KMC_SRC "include/kmc/kmc_api/*.cpp")

add_library(dynadbglib INTERFACE)
target_include_directories(dynadbglib INTERFACE src/)

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
  message(STATUS "OpenMP found")
  target_link_libraries(dynadbglib INTERFACE OpenMP::OpenMP_CXX)
endif ()

enable_testing()
add_subdirectory(test)