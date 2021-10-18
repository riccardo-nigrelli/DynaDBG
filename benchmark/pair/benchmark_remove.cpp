#include <iostream>
#include <benchmark/benchmark.h>

#include "dyna_dbg.hpp"
#include "kmc_utils.hpp"

int main(int argc, char **argv) {
  auto remove = [](benchmark::State &state, std::string path, std::string pathToRemove) {
    std::vector<std::pair<uint64_t, uint32_t>> data = kmc::db_parser_pair(path);
    DynaDBG::Pair dbg(data);
    for (auto _ : state) {
      dbg.remove_kmers(pathToRemove);
    }
  };
  
  auto metrics = [](benchmark::State &state, std::string path, std::string pathToRemove) {
    std::vector<std::pair<uint64_t, uint32_t>> data = kmc::db_parser_pair(path);
    DynaDBG::Pair dbg(data);      
    for (auto _ : state) {
      state.counters.insert({{"NumElems", dbg.size()}, {"IndexSize", dbg.size_in_bytes()}});

      dbg.remove_kmers(pathToRemove);
      state.counters.insert({{"NumElemsAfterInsert", dbg.size()}, {"IndexSizeAfterInsert", dbg.size_in_bytes()}});
    }
  };

  benchmark::Initialize(&argc, argv);
  benchmark::RegisterBenchmark("Remove", remove, argv[1], argv[2])->Iterations(1000)->Unit(benchmark::kMillisecond);
  benchmark::RegisterBenchmark("Metrics", metrics, argv[1], argv[2])->Iterations(1)->Unit(benchmark::kMillisecond);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}