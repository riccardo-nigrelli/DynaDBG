set(GTEST_SHUFFLE 1)

add_executable(
  DynaDBG_Test
  main.cpp
  test_kmer.cpp
)

target_include_directories(DynaDBG_Test PUBLIC ../include/googletest/googletest/include ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(DynaDBG_Test PUBLIC gtest)