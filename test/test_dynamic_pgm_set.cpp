#include <iostream>

#include "catch.hpp"
#include "pgm_index_dynamic_set.hpp"

TEST_CASE("DYNAMIC_PGM_INDEX_SET") {
  std::vector<uint64_t> data;
  for (uint64_t i = 0; i < 100000; ++i) data.push_back(i);
  
  pgm::DynamicPGMIndexSet<uint64_t> index(data.begin(), data.end());
  REQUIRE(index.size() == data.size());
  REQUIRE_FALSE(index.empty());

  for (const uint64_t &elem : data) index.erase(elem);
  REQUIRE(index.size() == 0);
  REQUIRE(index.empty());
  for (const uint64_t &elem : data) REQUIRE(index.find(elem) == index.end());
  
  for (const uint64_t &elem : data) index.insert_or_assign(elem);
  REQUIRE(index.size() == data.size());
  REQUIRE_FALSE(index.empty());

  for (const uint64_t &elem : data) REQUIRE(index.find(elem) != index.end());
  
  for (const uint64_t &elem : data) index.insert_or_assign(elem);
  REQUIRE(index.size() == data.size());

  index.erase(5000);
  REQUIRE(index.size() == data.size() - 1);
  REQUIRE(index.find(5000) == index.end());
  index.insert_or_assign(5000);
  REQUIRE(index.size() == data.size());
  REQUIRE(index.find(5000) != index.end());
}