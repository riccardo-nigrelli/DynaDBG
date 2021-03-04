#include "kmer.hpp"
#include "dyna_dbg.hpp"
#include "gtest/gtest.h"

typedef kmer_t<uint64_t> short_kmer;
DynaDBG<short_kmer> dbg("../data/sars-cov-2/sorted-sars-cov-2.res", NULL);

TEST(DynaDBG, DynaDBG_Find_Test) {
  ASSERT_TRUE(dbg.member(short_kmer("CTACAGCAACTGGTAATACAGCAAAGCATAA")));
  ASSERT_TRUE(dbg.member(short_kmer("CTATGGTTAGAATGTACATTTTCTTTGCATC")));
  ASSERT_FALSE(dbg.member(short_kmer("TGTACATTTTCTTTGCATCCTATGGTTAGAA")));
  ASSERT_FALSE(dbg.member(short_kmer("AAACCTTTACCGGGGTTAGAAAACTAGCAAT")));
}

TEST(DynaDBG, DynaDBG_Add_Test) {
  size_t actual_size = dbg.size();
  short_kmer kmer("TGTACATTTTCTTTGCATCCTATGGTTAGAA");
  
  dbg.add(kmer);
  ASSERT_TRUE(dbg.member(kmer));
  ASSERT_TRUE(dbg.size() > actual_size);
  ASSERT_TRUE(dbg.size() == actual_size + 1);
}

TEST(DynaDBG, DynaDBG_Predecessors_Test) {
  std::vector<short_kmer> nodes = dbg.predecessors(short_kmer("CTACAGCAACTGGTAATACAGCAAAGCATAA"));
  ASSERT_TRUE(nodes.size() == 1);
  ASSERT_TRUE(nodes[0].to_string() == "ACTACAGCAACTGGTAATACAGCAAAGCATA");

  nodes = dbg.predecessors(short_kmer("AAACCTTTACCGGGGTTAGAAAACTAGCAAT"));
  ASSERT_TRUE(nodes.empty());
}

TEST(DynaDBG, DynaDBG_Successors_Test) {
  std::vector<short_kmer> nodes = dbg.successors(short_kmer("AAAAGATTGCTGAGATTCCTAAAGAGGAAGT"));
  ASSERT_TRUE(nodes.size() == 1);
  ASSERT_TRUE(nodes[0].to_string() == "AAAGATTGCTGAGATTCCTAAAGAGGAAGTT");

  nodes = dbg.successors(short_kmer("AAACCTTTACCGGGGTTAGAAAACTAGCAAG"));
  ASSERT_TRUE(nodes.empty());
}

TEST(DynaDBG, DynaDBG_Remove_Test) {
  size_t actual_size = dbg.size();
  short_kmer kmer("TGTACATTTTCTTTGCATCCTATGGTTAGAA");
  
  dbg.remove(kmer);
  ASSERT_FALSE(dbg.member(kmer));
  ASSERT_TRUE(dbg.size() < actual_size);
  ASSERT_TRUE(dbg.size() == actual_size - 1);
}