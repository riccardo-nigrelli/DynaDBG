add_executable(
  Benchmarck_Small_DynaDBG
  ../include/KMC/kmc_api/kmc_file.cpp
  ../include/KMC/kmc_api/kmer_api.cpp
  ../include/KMC/kmc_api/mmer.cpp
  small_dyna.cpp
)

target_include_directories(Benchmarck_Small_DynaDBG PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Benchmarck_Small_DynaDBG benchmark::benchmark)