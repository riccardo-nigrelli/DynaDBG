set(benchmarks creation insert remove)
foreach(benchmark IN LISTS benchmarks)
  add_executable(dbg_pair_${benchmark} pair/benchmark_${benchmark}.cpp ${KMC_SRC})
  target_link_libraries(dbg_pair_${benchmark} dynadbglib benchmark::benchmark)
  set_property(
    TARGET dbg_pair_${benchmark}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY 
    "${CMAKE_CURRENT_BINARY_DIR}/pair"
  )
endforeach()

foreach(benchmark IN LISTS benchmarks)
  add_executable(dbg_set_${benchmark} set/benchmark_${benchmark}.cpp ${KMC_SRC})
  target_link_libraries(dbg_set_${benchmark} dynadbglib benchmark::benchmark)
  set_property(
    TARGET dbg_set_${benchmark}
    PROPERTY RUNTIME_OUTPUT_DIRECTORY 
    "${CMAKE_CURRENT_BINARY_DIR}/set"
  )
endforeach()