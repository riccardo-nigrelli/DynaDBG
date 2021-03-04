#include "kmer.hpp"
#include "dyna_dbg.hpp"

#include <chrono>
#include <benchmark/benchmark.h>

typedef kmer_t<uint64_t> short_kmer;

static void DynaDBG_create(benchmark::State& state) {
  for (auto _ : state)
    DynaDBG<short_kmer> dbg = DynaDBG<short_kmer>();
}
BENCHMARK(DynaDBG_create)->Unit(benchmark::kMillisecond);

static void DynaDBG_fill(benchmark::State& state) {
  for (auto _ : state) {
    DynaDBG<short_kmer> dbg = DynaDBG<short_kmer>("../data/partition/union.txt", state);
  }
}
BENCHMARK(DynaDBG_fill)->Unit(benchmark::kMillisecond);

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