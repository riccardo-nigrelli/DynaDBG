#include <iostream>

#include "catch.hpp"
#include "kmer.hpp"

TEST_CASE("K-MER: Compute next") {
  std::string current("CTAAAAGTGAAGTCAAATTTGTGAGTAACAA");
  uint64_t next = kmer::roll_left(current, 0);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "TAAAAGTGAAGTCAAATTTGTGAGTAACAAA");

  current = "TAAAAGTGAAGTCAAATTTGTGAGTAACAAA";
  next = kmer::roll_left(current, 1);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "AAAAGTGAAGTCAAATTTGTGAGTAACAAAC");
  
  current = "AAAAGTGAAGTCAAATTTGTGAGTAACAAAC";
  next = kmer::roll_left(current, 2);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "AAAGTGAAGTCAAATTTGTGAGTAACAAACG");
  
  current = "AAAGTGAAGTCAAATTTGTGAGTAACAAACG";
  next = kmer::roll_left(current, 2);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "AAGTGAAGTCAAATTTGTGAGTAACAAACGG");
  
  current = "AAGTGAAGTCAAATTTGTGAGTAACAAACGG";
  next = kmer::roll_left(current, 3);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "AGTGAAGTCAAATTTGTGAGTAACAAACGGT");
}

TEST_CASE("K-MER: Compute prev") {
  std::string current("CTAAAAGTGAAGTCAAATTTGTGAGTAACAA");
  uint64_t next = kmer::roll_right(current, 0);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "ACTAAAAGTGAAGTCAAATTTGTGAGTAACA");

  current = "ACTAAAAGTGAAGTCAAATTTGTGAGTAACA";
  next = kmer::roll_right(current, 1);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "CACTAAAAGTGAAGTCAAATTTGTGAGTAAC");
  
  current = "CACTAAAAGTGAAGTCAAATTTGTGAGTAAC";
  next = kmer::roll_right(current, 3);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "TCACTAAAAGTGAAGTCAAATTTGTGAGTAA");
  
  current = "TCACTAAAAGTGAAGTCAAATTTGTGAGTAA";
  next = kmer::roll_right(current, 2);
  REQUIRE(kmer::ulong_to_string(next, current.size()) == "GTCACTAAAAGTGAAGTCAAATTTGTGAGTA");
}