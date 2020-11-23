cmake_minimum_required(VERSION 3.18)

project(DynaDBG)
enable_language(CXX)
set(PROJECT_VERSION_MAJOR 1)
set(PROJECT_VERSION_MINOR 0)

SET(CMAKE_CXX_FLAGS  "-pedantic -Wall -Wextra -fopenmp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_VERBOSE_MAKEFILE ON)
include(CMakeToolsHelpers OPTIONAL)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)
include_directories(include/KMC)

add_subdirectory(app)
add_subdirectory(test)
add_subdirectory(include/googletest/googletest)