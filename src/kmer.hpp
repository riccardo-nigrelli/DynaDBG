#pragma once

#include "kmc/kmc_api/kmer_api.h"

namespace kmer {
  
  std::string ulong_to_string(const uint64_t v, uint32_t k) {
    std::string res;
    uint32_t n_words = (k + 31) / 32;
    for (uint32_t i = 0; i < k; ++i) {
      uint32_t pos = i % 32;
      uint32_t real_pos = pos * 2;
      char symbol = "ACGT"[(v >> real_pos) & 3];
      res.push_back(symbol);
    }
    return std::string(res.rbegin(), res.rend());
  }

  /**
   * Get numeric representation of string kmer
   * @param k kmer to convert 
   * @return the numeric representation of the kmer
   */ 
  uint64_t string_to_ulong(const std::string &k) {
    std::vector<uint64_t> v;
    CKmerAPI kmer(k.size());
    kmer.from_string(k);

    kmer.to_long(v);
    return v[0];
  }

  /**
   * Get predecessor of a given kmer
   * @param k starting kmer
   * @param c bit that rapresent the char { 0 -> 'A', 1 -> 'C', 2 -> 'G', 3 -> 'T' }
   * @return numeric representation of the predecessor
   */ 
  uint64_t roll_left(const std::string k, uchar c) {
    CKmerAPI kmer(k.size());
    kmer.from_string(k);
    kmer.SHL_insert2bits(c);
    
    std::vector<uint64_t> v;
    kmer.to_long(v);
    return v[0];
  }
  
  /**
   * Get successor of a given kmer
   * @param k starting kmer
   * @param c bit that rapresent the char { 0 -> 'A', 1 -> 'C', 2 -> 'G', 3 -> 'T' }
   * @return numeric representation of the successor
   */
  uint64_t roll_right(const std::string k, uchar c) {
    CKmerAPI kmer(k.size());
    kmer.from_string(k);
    kmer.SHR_insert2bits(c);
    
    std::vector<uint64_t> v;
    kmer.to_long(v);
    return v[0];
  }
}