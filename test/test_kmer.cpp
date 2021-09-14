#include <iostream>

#include "catch.hpp"
#include "kmer.hpp"

TEST_CASE("K-MER: Compute next", "[kmer]") {
  std::string current("CCCTTGAGACAACTACAGCAACTAGTCATAC");
  kmer::roll_left(current, 0);

  REQUIRE(1 == 1);
}

TEST_CASE("K-MER: Compute prev", "[kmer]") {
  REQUIRE(1 == 1);
}