#pragma once
  
#include <fstream>
#include <iostream>

#include "kmer.hpp"
#include "kmc_utils.hpp"
#include "pgm/pgm_index_dynamic.hpp"
#include "pgm_index_dynamic_set.hpp"

namespace DynaDBG {

  class Pair {
    pgm::DynamicPGMIndex<uint64_t, uint32_t> dynamic_index;
    
    public:
      Pair(): dynamic_index() {}
      Pair(std::vector<std::pair<uint64_t, uint32_t>> &data): dynamic_index(data.begin(), data.end()) {}
      ~Pair() {}

      void add_kmer(const std::string &kmer, const uint32_t data) {
        dynamic_index.insert_or_assign(kmer::string_to_ulong(kmer), data);
      }

      void add_kmers(const std::string &path) {
        const std::vector<std::pair<uint64_t, uint32_t>> data = kmc::db_parser_pair(path);
        for (const std::pair<uint64_t, uint32_t> &pair: data) {
          dynamic_index.insert_or_assign(pair.first, pair.second);
        }
      }

      void remove_kmer(const std::string &kmer) {
        dynamic_index.erase(kmer::string_to_ulong(kmer));
      }

      void remove_kmers(const std::string &path) {
        const std::vector<uint64_t> data = kmc::db_parser_set(path);
        for (const uint64_t &elem: data) {
          dynamic_index.erase(elem);
        }
      }

      void find_kmer(const std::string &path, const uint32_t kmer_len) {
        std::ofstream file("membership.tsv");
        if (!file.is_open()) {
          std::cerr << "ERROR: unable to create the file." << std::endl;
        }

        std::vector<uint64_t> data = kmc::db_parser_set(path);
        for (const uint64_t &elem : data) {
          file << kmer::ulong_to_string(elem, kmer_len) << "\t" << ((dynamic_index.find(elem) != dynamic_index.end()) ? 1 : 0) << std::endl;
        }

        file.close();
      }

      size_t size_in_bytes() const { return dynamic_index.size_in_bytes(); }
      
      size_t size() const { return dynamic_index.size(); }
  };

  class Set {
    pgm::DynamicPGMIndexSet<uint64_t> dynamic_index;

    public:
      Set(): dynamic_index() {}
      Set(std::vector<uint64_t> &data): dynamic_index(data.begin(), data.end()) {}
      ~Set() {}
      
      void add_kmer(const std::string &kmer, const uint32_t data) {
        dynamic_index.insert_or_assign(kmer::string_to_ulong(kmer));
      }

      void add_kmers(const std::string &path) {
        const std::vector<uint64_t> data = kmc::db_parser_set(path);
        for (const uint64_t &elem: data) {
          dynamic_index.insert_or_assign(elem);
        }
        dynamic_index.index_cleaner();
      }

      void remove_kmer(const std::string &kmer) {
        dynamic_index.erase(kmer::string_to_ulong(kmer));
      }

      void remove_kmers(const std::string &path) {
        const std::vector<uint64_t> data = kmc::db_parser_set(path);
        for (const uint64_t &elem: data) {
          dynamic_index.erase(elem);
        }
        dynamic_index.index_cleaner();
      }

      void find_kmer(const std::string &path, const uint32_t kmer_len) {
        std::ofstream file("membership.tsv");
        if (!file.is_open()) {
          std::cerr << "ERROR: unable to create the file." << std::endl;
        }

        std::vector<uint64_t> data = kmc::db_parser_set(path);
        for (const uint64_t &elem : data) {
          file << kmer::ulong_to_string(elem, kmer_len) << "\t" << ((dynamic_index.find(elem) != dynamic_index.end()) ? 1 : 0) << std::endl;
        }

        file.close();
      }

      size_t size_in_bytes() const { return dynamic_index.size_in_bytes(); }
      
      size_t size() const { return dynamic_index.size(); }
  };
}