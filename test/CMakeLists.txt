add_executable(tests main.cpp test_kmer.cpp test_dynamic_pgm_set.cpp ${KMC_SRC})
target_link_libraries(tests dynadbglib)
add_test(NAME test_all COMMAND tests WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})