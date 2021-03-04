add_executable(
  Benchmark_Small_DynaDBG
  ../include/KMC/kmc_api/kmc_file.cpp
  ../include/KMC/kmc_api/kmer_api.cpp
  ../include/KMC/kmc_api/mmer.cpp
  small_dyna.cpp
)

add_executable(
  Benchmark_Genome
  ../include/KMC/kmc_api/kmc_file.cpp
  ../include/KMC/kmc_api/kmer_api.cpp
  ../include/KMC/kmc_api/mmer.cpp
  genome_dyna.cpp
)

target_include_directories(Benchmark_Small_DynaDBG PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Benchmark_Small_DynaDBG benchmark::benchmark)

target_include_directories(Benchmark_Genome PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Benchmark_Genome benchmark::benchmark)