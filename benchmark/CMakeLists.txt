add_executable(
  Benchmarck_Small_DynaDBG
  small_dyna.cpp
)

target_link_libraries(Benchmarck_Small_DynaDBG benchmark::benchmark)