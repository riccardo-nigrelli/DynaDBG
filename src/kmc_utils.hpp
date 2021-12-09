#pragma once

#include <string>
#include <iterator>

#include "kmc/kmc_api/kmc_file.h"
#include "kmc/kmc_api/kmer_api.h"

namespace KMC {

  std::vector<std::pair<uint64_t, uint32_t>> db_parser_pair(const std::string &path) {
    CKMCFile database;
    
    if (!database.OpenForListing(path)) {
      std::cerr << "ERROR: unable to open " << path << std::endl;
    }
    
    CKMCFileInfo info;
    database.Info(info);
    CKmerAPI kmer(info.kmer_length);

    uint32 cnt;
    std::vector<uint64> ulong_kmer;
    std::vector<std::pair<uint64_t, uint32_t>> data;

    while (database.ReadNextKmer(kmer, cnt)) {
      kmer.to_long(ulong_kmer);
      data.push_back(std::make_pair(ulong_kmer.front(), cnt));
    }

    return data;
  }

  class Iterator {
    uint64_t kmer;
    CKMCFile *database;
    CKMCFileInfo *info;
    CKmerAPI tmp;
    std::vector<uint64> kmer_ulong;
    friend class FileWrapper;

    void read_next() {
      uint32_t cnt;
      tmp = CKmerAPI(info->kmer_length);
      
      if (database->ReadNextKmer(tmp, cnt)) {
        tmp.to_long(kmer_ulong);
        kmer = kmer_ulong.front();
      }
      else database = nullptr;
    }

    bool is_end() const { return database == nullptr; }

    public:
      uint64_t operator*() const { return kmer; }
      
      Iterator& operator++() {
        read_next();
        return *this;
      }

      bool operator==(const Iterator &rhs) const {
        if (is_end()) return rhs.is_end();
        if (rhs.is_end()) return false;
        return database == rhs.database;
      }

      bool operator!=(const Iterator &rhs) const { return !operator==(rhs); }
  };

  class FileWrapper {
    CKMCFile database;
    CKMCFileInfo info;

    public:
      explicit FileWrapper(const std::string &path) {
        if (!database.OpenForListing(path)) {
          std::cerr << "ERROR: unable to open " << path << std::endl;
        }
        database.Info(info);
      }

      Iterator begin() { 
        Iterator it;
        it.database = &database;
        it.info = &info;

        it.read_next();
        return it;
      }

      Iterator end() const { 
        Iterator it;
        it.database = nullptr;
        return it;
      }

      uint32_t kmer_len() const { return info.kmer_length; }
      uint64_t size() const { return info.total_kmers; }
  };

  std::vector<uint64_t> db_parser_set(const std::string &path) {
    CKMCFile database;
    
    if (!database.OpenForListing(path)) {
      std::cerr << "ERROR: unable to open " << path << std::endl;
    }
    
    CKMCFileInfo info;
    database.Info(info);
    
    CKmerAPI kmer(info.kmer_length);

    uint32 cnt;
    std::vector<uint64_t> data;
    std::vector<uint64> kmer_ulong;
    data.reserve(info.total_kmers);
    
    while (database.ReadNextKmer(kmer, cnt)) {
      kmer.to_long(kmer_ulong);
      data.push_back(kmer_ulong.front());
    }

    return data;
  }
}