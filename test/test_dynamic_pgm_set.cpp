#include <iostream>

#include "catch.hpp"
#include "pgm_index_dynamic_set.hpp"

TEST_CASE("TEST") {
  std::vector<uint32_t> data;
  for (int i = 10; i < 1000010; ++i) data.push_back(i);
  pgm::DynamicPGMIndexSet<uint32_t> pgm_dynamic_set(data.begin(), data.end());
  
  REQUIRE(data.size() == pgm_dynamic_set.size());

  pgm_dynamic_set.insert_or_assign(2);
  pgm_dynamic_set.insert_or_assign(4);
  pgm_dynamic_set.insert_or_assign(8);

  REQUIRE(pgm_dynamic_set.find(2) != pgm_dynamic_set.end());
  REQUIRE(data.size() + 3 == pgm_dynamic_set.size());

  pgm_dynamic_set.erase(4);

  REQUIRE(pgm_dynamic_set.find(4) == pgm_dynamic_set.end());
  REQUIRE(data.size() + 2 == pgm_dynamic_set.size());
}