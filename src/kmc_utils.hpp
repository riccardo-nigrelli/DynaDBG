#pragma once

#include <string>
#include <iostream>

#include "kmc/kmc_api/kmc_file.h"
#include "kmc/kmc_api/kmer_api.h"

namespace kmc {

  std::vector<std::pair<uint64_t, uint32_t>> db_parser_pair(const std::string &path) {
    CKMCFile database;
    
    if (!database.OpenForListing(path)) {
      std::cerr << "ERROR: unable to open " << path << std::endl;
    }
    
    uint64 total_kmer, max_cnt;
    uint32 kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, cnt;
    database.Info(kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, max_cnt, total_kmer);
    
    CKmerAPI kmer(kmer_len);

    std::vector<uint64_t> ulong_kmer;
    std::vector<std::pair<uint64_t, uint32_t>> data;

    while (database.ReadNextKmer(kmer, cnt)) {
      kmer.to_long(ulong_kmer);
      data.push_back(std::make_pair(ulong_kmer[0], cnt));
    }

    return data;
  }

  std::vector<uint64_t> db_parser_set(const std::string &path) {
    CKMCFile database;
    
    if (!database.OpenForListing(path)) {
      std::cerr << "ERROR: unable to open " << path << std::endl;
    }
    
    uint64 total_kmer, max_cnt;
    uint32 kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, cnt;
    database.Info(kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, max_cnt, total_kmer);
    
    CKmerAPI kmer(kmer_len);

    std::vector<uint64_t> ulong_kmer;
    std::vector<uint64_t> data;

    while (database.ReadNextKmer(kmer, cnt)) {
      kmer.to_long(ulong_kmer);
      data.push_back(ulong_kmer[0]);
    }

    return data;
  }
}