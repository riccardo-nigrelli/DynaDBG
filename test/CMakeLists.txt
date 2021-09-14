add_executable(tests main.cpp test_kmer.cpp ../include/KMC/kmc_api/kmc_file.cpp ../include/KMC/kmc_api/kmer_api.cpp ../include/KMC/kmc_api/mmer.cpp)
target_link_libraries(tests dynadbglib)
add_test(NAME test_all COMMAND tests)