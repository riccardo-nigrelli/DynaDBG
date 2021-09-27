add_executable(dbg_pair benchmark_pair.cpp ${KMC_SRC})
target_link_libraries(dbg_pair dynadbglib benchmark::benchmark)

add_executable(dbg_set benchmark_pair.cpp ${KMC_SRC})
target_link_libraries(dbg_set dynadbglib benchmark::benchmark)