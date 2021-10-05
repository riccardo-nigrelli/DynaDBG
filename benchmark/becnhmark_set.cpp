#include <benchmark/benchmark.h>

#include "dyna_dbg.hpp"
#include "kmc_utils.hpp"

int main(int argc, char **argv) {

  std::vector<uint64_t> data = kmc::db_parser_set(argv[1]);
  
  auto creation = [&data](benchmark::State &state) {
    for (auto _ : state) {
      DynaDBG::Set dbg(data);
    }
  };

  auto add = [&data, argv](benchmark::State &state) {
    for (auto _ : state) {
      state.PauseTiming();
      DynaDBG::Set dbg(data);
      state.ResumeTiming();

      dbg.add_kmers(argv[2]);
    }
  };

  auto remove = [&data, argv](benchmark::State &state) {
    for (auto _ : state) {
      state.PauseTiming();
      DynaDBG::Set dbg(data);
      state.ResumeTiming();

      dbg.remove_kmers(argv[3]);
    }
  };
  
  if (argc == 2) {
    benchmark::RegisterBenchmark("Creation", creation)->Iterations(1000)->Unit(benchmark::kMillisecond);
  }
  else if (argc == 3) {
    benchmark::RegisterBenchmark("Creation", creation)->Iterations(1000)->Unit(benchmark::kMillisecond);
    benchmark::RegisterBenchmark("Add kmers", add)->Iterations(1000)->Unit(benchmark::kMillisecond);
  }
  else if (argc ==  4) {
    benchmark::RegisterBenchmark("Creation", creation)->Iterations(1000)->Unit(benchmark::kMillisecond);
    benchmark::RegisterBenchmark("Add kmers", add)->Iterations(1000)->Unit(benchmark::kMillisecond);
    benchmark::RegisterBenchmark("Remove kmers", remove)->Iterations(1000)->Unit(benchmark::kMillisecond);
  }

  benchmark::RunSpecifiedBenchmarks();

  return 0;
}
