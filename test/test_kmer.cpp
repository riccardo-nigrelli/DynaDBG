#include <bitset>

#include "kmer.hpp"
#include "gtest/gtest.h"

typedef kmer_t<uint64_t> short_kmer;

TEST(ShortKmer, ShortKmer_Equality_Test) {
  short_kmer kmer("CTAAAAGTGAAGTCAAATTTGTGAGTAACAA");
  short_kmer kmer1("CTAAAAGTGAAGTCAAATTTGTGAGTAACAA");
  ASSERT_TRUE(kmer == kmer1);

  kmer1 = short_kmer("CTAAAAGTGAAGTCAAATTTGTGAGTAACTT");
  ASSERT_FALSE(kmer == kmer1);
}

TEST(ShortKmer, ShortKmer_ShiftLeft_Test) {
  short_kmer kmer("CTAAAAGTGAAGTCAAATTTGTGAGTAACAA");
  ASSERT_TRUE(kmer.to_string() == "CTAAAAGTGAAGTCAAATTTGTGAGTAACAA");

  ASSERT_TRUE(kmer.roll_left('A').to_string() == "TAAAAGTGAAGTCAAATTTGTGAGTAACAAA");
  ASSERT_TRUE(kmer.roll_left('C').to_string() == "AAAAGTGAAGTCAAATTTGTGAGTAACAAAC");
  ASSERT_TRUE(kmer.roll_left('G').to_string() == "AAAGTGAAGTCAAATTTGTGAGTAACAAACG");
  ASSERT_TRUE(kmer.roll_left('G').to_string() == "AAGTGAAGTCAAATTTGTGAGTAACAAACGG");
}

TEST(ShortKmer, ShortKmer_ShiftRight_Test) {
  short_kmer kmer("AAGTGAAGTCAAATTTGTGAGTAACAAACGG");
  ASSERT_TRUE(kmer.to_string() == "AAGTGAAGTCAAATTTGTGAGTAACAAACGG");

  ASSERT_TRUE(kmer.roll_right('A').to_string() == "AAAGTGAAGTCAAATTTGTGAGTAACAAACG");
  ASSERT_TRUE(kmer.roll_right('T').to_string() == "TAAAGTGAAGTCAAATTTGTGAGTAACAAAC");
  ASSERT_TRUE(kmer.roll_right('C').to_string() == "CTAAAGTGAAGTCAAATTTGTGAGTAACAAA");
  ASSERT_TRUE(kmer.roll_right('A').to_string() == "ACTAAAGTGAAGTCAAATTTGTGAGTAACAA");
}
