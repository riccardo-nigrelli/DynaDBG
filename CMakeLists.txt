cmake_minimum_required(VERSION 3.18)

project(
  DynaDBG
  VERSION 1.0
)

option(BUILD_BENCHMARK "Build the benchmark target" ON)

set(CMAKE_CXX_STANDARD 17)
include(CheckCXXCompilerFlag)

include_directories(include)
file(GLOB KMC_SRC "include/kmc/kmc_api/*.cpp")

add_library(dynadbglib INTERFACE)
target_include_directories(dynadbglib INTERFACE src/)

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
  message(STATUS "OpenMP found")
  target_link_libraries(dynadbglib INTERFACE OpenMP::OpenMP_CXX)
endif ()

if (BUILD_BENCHMARK)
  set(CMAKE_BUILD_TYPE Release)
  set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
  set(BENCHMARK_ENABLE_TESTING OFF)
  add_subdirectory(benchmark/include)
  add_subdirectory(benchmark)
endif ()

enable_testing()
add_subdirectory(test)
add_subdirectory(app)