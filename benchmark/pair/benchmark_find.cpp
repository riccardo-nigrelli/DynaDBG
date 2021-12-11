#include <iostream>
#include <benchmark/benchmark.h>

#include "dyna_dbg.hpp"
#include "kmc_utils.hpp"

int main(int argc, char **argv) {
  auto find = [](benchmark::State &state, std::string path, std::string pathToSearch, uint32_t kmer_size) {
    std::vector<std::pair<uint64_t, uint32_t>> data = KMC::db_parser_pair(path);
    DynaDBG::Pair dbg(data);
    for (auto _ : state) {
      dbg.find_kmer(pathToSearch, kmer_size);
    }
  };
  
  benchmark::Initialize(&argc, argv);
  benchmark::RegisterBenchmark(
    "Find", find,
    argv[1], argv[2], std::atoi(argv[3])
  )->Iterations(10)->Repetitions(20)->Unit(benchmark::kMillisecond);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}