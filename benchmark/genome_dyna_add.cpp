#include "kmer.hpp"
#include "dyna_dbg.hpp"

#include <sstream>
#include <benchmark/benchmark.h>

typedef kmer_t<uint64_t> short_kmer;
DynaDBG<short_kmer> dbg;

std::string base_path = "/data/kmg-genome/split-5120/experiment-";
std::stringstream stream;

int main(int argc, char** argv) {
  auto _benchmark = [](benchmark::State& state, char* _union, char* add) {
    for (auto _ : state) {
      dbg = DynaDBG<short_kmer>(_union, state);
      dbg.bulk_add_from_file(add, state);
    }
  };

  benchmark::RegisterBenchmark("DynaDBG_Add", _benchmark, argv[1], argv[2])->Unit(benchmark::kMillisecond);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}