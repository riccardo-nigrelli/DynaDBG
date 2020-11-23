set(GTEST_SHUFFLE 1)

add_executable(
  DynaDBG_Test
  main.cpp
  ../include/KMC/kmc_api/kmc_file.cpp
  ../include/KMC/kmc_api/kmer_api.cpp
  ../include/KMC/kmc_api/mmer.cpp
  test_kmer.cpp
  test_dyna_dbg.cpp
)

target_include_directories(DynaDBG_Test PUBLIC ../include/googletest/googletest/include ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(DynaDBG_Test PUBLIC gtest)