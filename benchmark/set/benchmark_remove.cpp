#include <iostream>
#include <benchmark/benchmark.h>

#include "dyna_dbg.hpp"
#include "kmc_utils.hpp"

int main(int argc, char **argv) {
  auto remove = [](benchmark::State &state, std::string path, std::string pathToRemove) {
    DynaDBG::Set dbg(path);
    for (auto _ : state) {
      dbg.remove_kmers(pathToRemove);
    }
  };
  
  auto metrics = [](benchmark::State &state, std::string path, std::string pathToRemove) {
    DynaDBG::Set dbg(path);
    for (auto _ : state) {
      state.counters.insert({{"NumElems", dbg.size()}, {"IndexSize", dbg.size_in_bytes()}});
      dbg.remove_kmers(pathToRemove);
      state.counters.insert({{"NumElemsAfterRemove", dbg.size()}, {"IndexSizeAfterRemove", dbg.size_in_bytes()}});
    }
  };

  benchmark::Initialize(&argc, argv);
  benchmark::RegisterBenchmark("Remove", remove, argv[1], argv[2])->Iterations(10)->Repetitions(20)->Unit(benchmark::kMillisecond);
  benchmark::RegisterBenchmark("Metrics", metrics, argv[1], argv[2])->Iterations(1)->Unit(benchmark::kMillisecond);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}