#include <iostream>
#include <benchmark/benchmark.h>

#include "dyna_dbg.hpp"
#include "kmc_utils.hpp"

int main(int argc, char **argv) {
  auto insert = [](benchmark::State &state, std::string path, std::string pathToInsert) {
    std::vector<uint64_t> data = kmc::db_parser_set(path);
    DynaDBG::Set dbg(data);
    for (auto _ : state) {
      dbg.add_kmers(pathToInsert);
    }
  };
  
  auto metrics = [](benchmark::State &state, std::string path, std::string pathToInsert) {
    std::vector<uint64_t> data = kmc::db_parser_set(path);
    DynaDBG::Set dbg(data);      
    for (auto _ : state) {
      state.counters.insert({{"NumElems", dbg.size()}, {"IndexSize", dbg.size_in_bytes()}});
      dbg.add_kmers(pathToInsert);
      state.counters.insert({{"NumElemsAfterInsert", dbg.size()}, {"IndexSizeAfterInsert", dbg.size_in_bytes()}});
    }
  };

  benchmark::Initialize(&argc, argv);
  benchmark::RegisterBenchmark("Insert", insert, argv[1], argv[2])->Iterations(1000)->Unit(benchmark::kMillisecond);
  benchmark::RegisterBenchmark("Metrics", metrics, argv[1], argv[2])->Iterations(1)->Unit(benchmark::kMillisecond);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}