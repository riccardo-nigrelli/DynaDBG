#pragma once

#include <iostream>

#include "kmc_api/kmc_file.h"
#include "kmc_api/kmer_api.h"

namespace kmer {
  
  #ifndef DEBUG
    std::string ulong_to_string(const std::vector<uint64_t>&v, uint32_t klen) {
      std::string kmer;
      uint32_t words = (klen + 31) / 32;

      for (uint32_t i = 0; i < klen; ++i) {
        uint32_t index = words - 1 - i / 32;
        uint32_t pos = i % 32;
        uint32_t real_pos = pos * 2;

        char symbol = "ACGT"[(v[index] >> real_pos) & 3];
        kmer.push_back(symbol);
      }
      return std::string(kmer.begin(), kmer.end());
    }
  #endif

  /**
   * Get numeric representation of string kmer
   * @param k kmert to convert 
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
   * @param c numer of bits that rapresent the char {'A' => 0, 'C' => 1, 'G' => 2, 'T' => 3}
   * @return numeric rapresentation of the precessor
   */ 
  uint64_t roll_left(const std::string &k, uchar c) {
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
   * @param c numer of bits that rapresent the char {'A' => 0, 'C' => 1, 'G' => 2, 'T' => 3}
   * @return numeric rapresentation of the successor
   */ 
  uint64_t roll_right(const std::string &k, uchar c) {
    CKmerAPI kmer(k.size());
    kmer.from_string(k);
    kmer.SHR_insert2bits(c);

    std::vector<uint64_t> v;
    kmer.to_long(v);

    return v[0];
  }
}