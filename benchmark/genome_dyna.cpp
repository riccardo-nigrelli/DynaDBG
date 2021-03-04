#include "kmer.hpp"
#include "dyna_dbg.hpp"

#include <benchmark/benchmark.h>

typedef kmer_t<uint64_t> short_kmer;

static void DynaDBG_Create(benchmark::State& state) {
  for (auto _ : state) {
    DynaDBG<short_kmer> dbg = DynaDBG<short_kmer>("/data/kmc-genome/genome.res", state);
  }
}
BENCHMARK(DynaDBG_Create)->Unit(benchmark::kMillisecond);

// static void DynaDBG_add_new(benchmark::State& state) {
//   DynaDBG<short_kmer> dbg = DynaDBG<short_kmer>("../data/partition/union.txt", false);
//   for (auto _ : state) {
//     dbg.bulk_add("../data/partition/missing.txt", false);
//   }
// }
// BENCHMARK(DynaDBG_add_new);

// static void DynaDBG_add_existing(benchmark::State& state) {
//   DynaDBG<short_kmer> dbg = DynaDBG<short_kmer>("../data/partition/union.txt", false);
//   for (auto _ : state) {
//     dbg.bulk_add("../data/partition/already_present.txt", false);
//   }
// }
// BENCHMARK(DynaDBG_add_existing);

BENCHMARK_MAIN();