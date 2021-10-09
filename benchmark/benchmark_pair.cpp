#include <benchmark/benchmark.h>

#include "dyna_dbg.hpp"
#include "kmc_utils.hpp"

/**
 * argv[1] => --benchmark_counters_tabular=true 
 * argv[2] => --benchmark_out=$fileName.json
 */
int main(int argc, char **argv) {
  std::vector<std::pair<uint64_t, uint32_t>> data = kmc::db_parser_pair(argv[3]);
  
  auto creation = [&data](benchmark::State &state) {
    size_t size = 0, num_elems = 0;
    for (auto _ : state) {
      DynaDBG::Pair dbg(data);
      size = dbg.size_in_bytes();
      num_elems = dbg.size();
    }
    state.counters.insert({{ "IndexSize", size }, { "NumElems", num_elems }});
  };

  auto add = [&data, argv](benchmark::State &state) {
    size_t size = 0, num_elems = 0;
    for (auto _ : state) {
      state.PauseTiming();
      DynaDBG::Pair dbg(data);
      state.ResumeTiming();

      dbg.add_kmers(argv[4]);
      size = dbg.size_in_bytes();
      num_elems = dbg.size();
    }
    state.counters.insert({{ "IndexSize", size }, { "NumElems", num_elems }});
  };

  auto remove = [&data, argv](benchmark::State &state) {
    size_t size = 0, num_elems = 0;
    for (auto _ : state) {
      state.PauseTiming();
      DynaDBG::Pair dbg(data);
      state.ResumeTiming();

      dbg.remove_kmers(argv[5]);
      state.counters.insert({ "IndexSize", dbg.size_in_bytes() });
      size = dbg.size_in_bytes();
      num_elems = dbg.size();
    }
    state.counters.insert({{ "IndexSize", size }, { "NumElems", num_elems }});
  };
  
  if (argc == 4) {
    benchmark::RegisterBenchmark("Creation", creation)->Iterations(1000)->Unit(benchmark::kMillisecond);
  }
  else if (argc == 5) {
    benchmark::RegisterBenchmark("Creation", creation)->Iterations(1000)->Unit(benchmark::kMillisecond);
    benchmark::RegisterBenchmark("Add kmers", add)->Iterations(1000)->Unit(benchmark::kMillisecond);
  }
  else if (argc ==  6) {
    benchmark::RegisterBenchmark("Creation", creation)->Iterations(1000)->Unit(benchmark::kMillisecond);
    benchmark::RegisterBenchmark("Add kmers", add)->Iterations(1000)->Unit(benchmark::kMillisecond);
    benchmark::RegisterBenchmark("Remove kmers", remove)->Iterations(1000)->Unit(benchmark::kMillisecond);
  }

  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();

  return 0;
}
