add_executable(tests main.cpp test_kmer.cpp ${KMC_SRC})
target_link_libraries(tests dynadbglib)
add_test(NAME test_all COMMAND tests)