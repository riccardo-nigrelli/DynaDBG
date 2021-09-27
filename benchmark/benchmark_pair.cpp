#include <benchmark/benchmark.h>

#include "dyna_dbg.hpp"
#include "kmc_utils.hpp"

int main(int argc, char **argv) {

  std::vector<std::pair<uint64_t, uint32_t>> data = kmc::db_parser_pair(argv[1]);
  
  auto creation = [&data](benchmark::State &state) {
    for (auto _ : state) {
      DynaDBG::Pair dbg(data);
      std::cout << "# Elem: " << dbg.size() << ", size: " << dbg.size_in_bytes() << "[bytes]\n";
    }
  };

  auto add = [&data, argv](benchmark::State &state) {
    for (auto _ : state) {
      state.PauseTiming();
      DynaDBG::Pair dbg(data);
      state.ResumeTiming();

      dbg.add_kmers(argv[2]);
    }
  };

  auto remove = [&data, argv](benchmark::State &state) {
    for (auto _ : state) {
      state.PauseTiming();
      DynaDBG::Pair dbg(data);
      state.ResumeTiming();

      dbg.remove_kmers(argv[3]);
    }
  };
  
  benchmark::RegisterBenchmark("Creation", creation)->Iterations(10)->Unit(benchmark::kMillisecond);
  benchmark::RegisterBenchmark("Add kmers", add)->Iterations(100000)->Unit(benchmark::kMillisecond);
  benchmark::RegisterBenchmark("Remove kmers", remove)->Iterations(100000)->Unit(benchmark::kMillisecond);
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}
