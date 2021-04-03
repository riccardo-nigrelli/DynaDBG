#include "kmer.hpp"
#include "dyna_dbg.hpp"

#include <sstream>
#include <benchmark/benchmark.h>

typedef kmer_t<uint64_t> short_kmer;
DynaDBG<short_kmer> dbg;

std::stringstream stream;

int main(int argc, char** argv) {
  auto _benchmark = [](benchmark::State& state, char* param, char* file) {
    for (auto _ : state) {
      stream << "/data/kmg-genome/split-5120/experiment-" << param << file << param << ".txt";
      dbg = DynaDBG<short_kmer>(stream.str(), state);
    }
  };

  benchmark::RegisterBenchmark("DynaDBG_Create", _benchmark, argv[1], argv[2])->Unit(benchmark::kMillisecond);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}