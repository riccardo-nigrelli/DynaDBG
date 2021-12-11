#include <iostream>
#include <benchmark/benchmark.h>

#include "dyna_dbg.hpp"
#include "kmc_utils.hpp"

int main(int argc, char **argv) {
  auto find = [](benchmark::State &state, std::string path, std::string pathToSearch) {
    DynaDBG::Set dbg(path);
    for (auto _ : state) {
      dbg.find_kmer(pathToSearch);
    }
  };
  
  benchmark::Initialize(&argc, argv);
  benchmark::RegisterBenchmark(
    "Find", find,
    argv[1], argv[2]
  )->Iterations(10)->Repetitions(20)->Unit(benchmark::kMillisecond);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}