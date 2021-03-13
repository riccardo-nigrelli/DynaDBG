#include "kmer.hpp"
#include "dyna_dbg.hpp"

#include <benchmark/benchmark.h>

typedef kmer_t<uint64_t> short_kmer;
DynaDBG<short_kmer> dbg;

static void DynaDBG_Create(benchmark::State& state) {
  for (auto _ : state) dbg = DynaDBG<short_kmer>("/data/kmc-genome/union.txt", state);
}
BENCHMARK(DynaDBG_Create)->Unit(benchmark::kMillisecond);

static void DynaDBG_add_existing(benchmark::State& state) {
  for (auto _ : state) dbg.bulk_add_from_file("/data/kmc-genome/already_present.txt", state);
}
BENCHMARK(DynaDBG_add_existing);

static void DynaDBG_new_existing(benchmark::State& state) {
  for (auto _ : state) dbg.bulk_add_from_file("/data/kmc-genome/missing.txt", state);
}
BENCHMARK(DynaDBG_new_existing);

static void DynaDBG_mix_kmer(benchmark::State& state) {
  for (auto _ : state) dbg.bulk_add_from_file("/data/kmc-genome/mix_kmer.txt", state);
}
BENCHMARK(DynaDBG_mix_kmer);

BENCHMARK_MAIN();