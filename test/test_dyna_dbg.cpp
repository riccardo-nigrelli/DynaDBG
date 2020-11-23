#include <gtest/gtest.h>
#include "dyna_dbg.hpp"
#include "kmer.hpp"

typedef kmer_t<uint64_t> short_kmer;

TEST(DynaDBG, Init) {
  dbg::DynaDBG<short_kmer> dbg("asdf");
}