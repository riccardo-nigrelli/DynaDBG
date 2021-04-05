#include "kmer.hpp"
#include "dyna_dbg.hpp"

#include <sstream>
#include <benchmark/benchmark.h>

typedef kmer_t<uint64_t> short_kmer;
DynaDBG<short_kmer> dbg;

std::stringstream stream;

int main(int argc, char** argv) {
  auto _benchmark = [](benchmark::State& state, char* path) {
    for (auto _ : state) {
      dbg = DynaDBG<short_kmer>(path, state);
    }
  };

  benchmark::RegisterBenchmark("DynaDBG_Create", _benchmark, argv[1])->Unit(benchmark::kMillisecond);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}