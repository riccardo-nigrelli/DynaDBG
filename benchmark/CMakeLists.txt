# add_executable(
#   Benchmark_Small_DynaDBG
#   ../include/KMC/kmc_api/kmc_file.cpp
#   ../include/KMC/kmc_api/kmer_api.cpp
#   ../include/KMC/kmc_api/mmer.cpp
#   small_dyna.cpp
# )

add_executable(
  Benchmark_Genome_Create
  ../include/KMC/kmc_api/kmc_file.cpp
  ../include/KMC/kmc_api/kmer_api.cpp
  ../include/KMC/kmc_api/mmer.cpp
  genome_dyna_create.cpp
)

add_executable(
  Benchmark_Genome_Add
  ../include/KMC/kmc_api/kmc_file.cpp
  ../include/KMC/kmc_api/kmer_api.cpp
  ../include/KMC/kmc_api/mmer.cpp
  genome_dyna_add.cpp
)

# target_include_directories(Benchmark_Small_DynaDBG PUBLIC ${CMAKE_SOURCE_DIR}/src)
# target_link_libraries(Benchmark_Small_DynaDBG benchmark::benchmark)

target_include_directories(Benchmark_Genome_Create PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Benchmark_Genome_Create benchmark::benchmark)

target_include_directories(Benchmark_Genome_Add PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(Benchmark_Genome_Add benchmark::benchmark)

target_compile_definitions(Benchmark_Genome_Create PRIVATE TIMER=0 CREATION=1)
target_compile_definitions(Benchmark_Genome_Add PRIVATE TIMER=0 CREATION=0)