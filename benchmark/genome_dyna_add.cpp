#include "kmer.hpp"
#include "dyna_dbg.hpp"

#include <sstream>
#include <benchmark/benchmark.h>

typedef kmer_t<uint64_t> short_kmer;
DynaDBG<short_kmer> dbg;

std::string base_path = "/data/kmg-genome/split-5120/experiment-";
std::stringstream stream;

int main(int argc, char** argv) {
  auto _benchmark = [](benchmark::State& state, char* param) {
    for (auto _ : state) {
      stream << base_path << param << "/sort-union-" << param << ".txt";
      dbg = DynaDBG<short_kmer>(stream.str(), state);
      stream << base_path << param << "/sort-existing-kmer-" << param << ".txt";
      dbg.bulk_add_from_file(stream.str(), state);
    }
  };

  benchmark::RegisterBenchmark("DynaDBG_Create", _benchmark, argv[1])->Unit(benchmark::kMillisecond);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();

  return 0;
}