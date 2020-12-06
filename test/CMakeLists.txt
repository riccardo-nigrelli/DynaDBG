set(GTEST_SHUFFLE 1)

add_executable(
  DynaDBG_Test_Kmer
  main.cpp
  test_kmer.cpp
)

add_executable(
  DynaDBG_Test_DBG
  main.cpp
  ../include/KMC/kmc_api/kmc_file.cpp
  ../include/KMC/kmc_api/kmer_api.cpp
  ../include/KMC/kmc_api/mmer.cpp
  test_dyna_dbg.cpp
)

target_include_directories(DynaDBG_Test_Kmer PUBLIC ../include/googletest/googletest/include ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(DynaDBG_Test_Kmer PUBLIC gtest)

target_include_directories(DynaDBG_Test_DBG PUBLIC ../include/googletest/googletest/include ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(DynaDBG_Test_DBG PUBLIC gtest)