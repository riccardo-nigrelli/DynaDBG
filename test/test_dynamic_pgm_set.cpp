#include <iostream>

#include "catch.hpp"
#include "kmc_utils.hpp"
#include "pgm_index_dynamic_set.hpp"

TEST_CASE("DYNAMIC_PGM_INDEX_SET") {

  CKMCFile file;
  CKMCFileInfo info;
  file.OpenForListing("../data/20K.res");
  file.Info(info);

  pgm::DynamicPGMIndexSet<uint64_t> index("../data/20K.res");
  REQUIRE(index.size() == info.total_kmers);
  REQUIRE_FALSE(index.empty());

  uint32 cnt;
  CKmerAPI kmer(info.kmer_length);
  std::vector<uint64_t> kmer_ulong;

  while (file.ReadNextKmer(kmer, cnt)) {
    kmer.to_long(kmer_ulong);
    index.erase(kmer_ulong[0]);
  }
  REQUIRE(index.size() == 0);
  REQUIRE(index.empty());

  CKMCFile _file;
  _file.OpenForListing("../data/20K.res");
  while (_file.ReadNextKmer(kmer, cnt)) {
    kmer.to_long(kmer_ulong);
    REQUIRE(index.find(kmer_ulong[0]) == index.end());
  }

  CKMCFile _file_;
  _file_.OpenForListing("../data/20K.res");
  while (_file_.ReadNextKmer(kmer, cnt)) {
    kmer.to_long(kmer_ulong);
    index.insert_or_assign(kmer_ulong[0]);
  }
  REQUIRE(index.size() == info.total_kmers);
  REQUIRE_FALSE(index.empty());

  CKMCFile __file;
  __file.OpenForListing("../data/20K.res");
  while (file.ReadNextKmer(kmer, cnt)) {
    kmer.to_long(kmer_ulong);
    REQUIRE(index.find(kmer_ulong[0]) != index.end());
  }
  
  CKMCFile __file_;
  __file_.OpenForListing("../data/20K.res");
  while (__file_.ReadNextKmer(kmer, cnt)) {
    kmer.to_long(kmer_ulong);
    index.insert_or_assign(kmer_ulong[0]);
  }
  REQUIRE(index.size() == info.total_kmers);

  REQUIRE(index.find(5933537886150) != index.end());
  size_t current_size = index.size();
  index.erase(5933537886150);
  REQUIRE(index.size() == current_size - 1);
  REQUIRE(index.find(5933537886150) == index.end());
  index.insert_or_assign(5933537886150);
  REQUIRE(index.size() == current_size);
  REQUIRE(index.find(5933537886150) != index.end());
}