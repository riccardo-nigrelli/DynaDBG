cmake_minimum_required(VERSION 3.18)

project(
  DynaDBG
  VERSION 1.0
)

option(BUILD_DynaDBG_BENCHMARK "Build benchmark" ON)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS  "-Wall -Wextra -pedantic -fopenmp")

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_VERBOSE_MAKEFILE ON)

include_directories(include)
include_directories(include/KMC)

add_library(dynadbglib INTERFACE)
target_include_directories(dynadbglib INTERFACE src/)

enable_testing()
add_subdirectory(test)