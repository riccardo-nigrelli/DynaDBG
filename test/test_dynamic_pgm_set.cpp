#include <iostream>

#include "catch.hpp"
#include "kmc_utils.hpp"
#include "pgm_index_dynamic_set.hpp"

TEST_CASE("DYNAMIC_PGM_INDEX_SET") {
  KMC::FileWrapper file("../data/20K.res");
  pgm::DynamicPGMIndexSet<uint64_t> index(file);

  REQUIRE(index.size() == file.size());
  REQUIRE_FALSE(index.empty());

  KMC::FileWrapper _file("../data/20K.res");
  for (auto it = _file.begin(); it != _file.end(); ++it) index.erase(*it);
  REQUIRE(index.size() == 0);
  // REQUIRE(index.empty());

  KMC::FileWrapper _file_("../data/20K.res");
  for (auto it = _file_.begin(); it != _file_.end(); ++it) REQUIRE(index.find(*it) == index.end());
  
  KMC::FileWrapper __file("../data/20K.res");
  for (auto it = __file.begin(); it != __file.end(); ++it) index.insert_or_assign(*it);
  REQUIRE(index.size() == __file.size());
  REQUIRE_FALSE(index.empty());

  KMC::FileWrapper __file_("../data/20K.res");
  for (auto it = __file_.begin(); it != __file_.end(); ++it) REQUIRE(index.find(*it) != index.end());
  
  KMC::FileWrapper __file__("../data/20K.res");
  for (auto it = __file__.begin(); it != __file__.end(); ++it) index.insert_or_assign(*it);
  REQUIRE(index.size() == __file__.size());

  REQUIRE(index.find(5933537886150) != index.end());
  size_t current_size = index.size();
  index.erase(5933537886150);
  REQUIRE(index.size() == current_size - 1);
  REQUIRE(index.find(5933537886150) == index.end());
  index.insert_or_assign(5933537886150);
  REQUIRE(index.size() == current_size);
  REQUIRE(index.find(5933537886150) != index.end());
}