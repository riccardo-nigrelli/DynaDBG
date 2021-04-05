#ifndef _DYNA_DBG_HPP_
  #define _DYNA_DBG_HPP_
  
  #include <math.h>
  #include <string>
  #include <fstream>
  #include <iostream>
  
  #include "kmer.hpp"
  #include "pgm/pgm_index.hpp"
  #include "kmc_api/kmc_file.h"
  #include "pgm/pgm_index_dynamic.hpp"
  #include "benchmark/include/benchmark/benchmark.h"

  template<class kmer_t>
  class DynaDBG {
    
    typedef typename kmer_t::type_t value_type;
    using PGMType = pgm::PGMIndex<value_type>;

    pgm::DynamicPGMIndex<value_type, size_t, PGMType> dynamic_index;
    
    static constexpr unsigned char bases[4] = { 'A', 'C', 'G', 'T' };

    std::vector<std::pair<value_type, size_t>> read_kmc_file(const std::string path) {

      std::string kmer;
      CKMCFile database;
      std::vector<std::pair<value_type, size_t>> data;

      if (!database.OpenForListing(path)) {
        std::cerr << "Error: unable to open " << path << std::endl;
      }
      
      uint64 total_kmer, max_cnt;
      uint32 kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, counter;

      database.Info(kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, max_cnt, total_kmer);
      CKmerAPI kmer_obj(kmer_len);

      while (database.ReadNextKmer(kmer_obj, counter)) {
        kmer_obj.to_string(kmer);

        kmer_t tmp(kmer);
        data.push_back(std::make_pair(tmp.value, tmp.index));
      }

      return data;
    }

    std::vector<std::pair<value_type, size_t>> read_file(const std::string path, benchmark::State& state) {
      
      #if STOP && CREATION
        state.PauseTiming();
      #endif
      
      std::string kmer;
      std::ifstream file(path);
      if (file.fail()) {
        std::cerr << "Error: unable to open " << path << std::endl;
        exit(EXIT_FAILURE);
      }

      std::vector<std::pair<value_type, size_t>> data;

      while (std::getline(file, kmer)) {
        kmer_t tmp(kmer.substr(0, kmer.find('\t')));
        data.push_back(std::make_pair(tmp.value, tmp.index));
      }

      #if STOP && CREATION
        state.ResumeTiming();
      #endif

      return data;
    }

    public:

      DynaDBG() {
        dynamic_index = pgm::DynamicPGMIndex<value_type, size_t, PGMType>();
      }

      DynaDBG(const std::string path, benchmark::State& state) {
        #if !CREATION
          state.PauseTiming();
        #endif

        std::vector<std::pair<value_type, size_t>> data = read_file(path, state);
        dynamic_index = pgm::DynamicPGMIndex<value_type, size_t, PGMType>(data.begin(), data.end());

        #if !CREATION
          state.ResumeTiming();
        #endif
      }

      ~DynaDBG() {}
 
      bool member(const kmer_t &kmer) {
        return dynamic_index.find(kmer.value) == dynamic_index.end() ? false : true;
      }

      void add(const kmer_t &kmer) { dynamic_index.insert_or_assign(kmer.value, kmer.index); }

      void bulk_add_from_file(const std::string &path, benchmark::State& state) {
        
        #if STOP
          state.PauseTiming();
        #endif

        std::string kmer;
        std::ifstream file(path);
        if (file.fail()) {
          std::cerr << "Error: unable to open " << path << std::endl;
          exit(EXIT_FAILURE);
        }

        std::vector<kmer_t> data;

        while (std::getline(file, kmer)) {
          kmer_t tmp(kmer.substr(0, kmer.find('\t')));
          data.push_back(tmp);
        }

        #if STOP
          state.ResumeTiming();
        #endif
        
        for (kmer_t element : data) add(element);
      }

      void remove(const kmer_t &kmer) {
        dynamic_index.erase(kmer.value);
        kmer.decrement_count();
      }

      std::vector<kmer_t> predecessors(kmer_t kmer) {
        std::vector<kmer_t> preds;
        
        if (member(kmer)) {
          for (unsigned char base : bases) {
            kmer_t tmp = kmer;
            if (member(tmp.roll_right(base))) preds.push_back(tmp);
          }
        }

        return preds;
      }

      std::vector<kmer_t> successors(kmer_t kmer) {
        std::vector<kmer_t> succs;
        
        if (member(kmer)) {
          for (unsigned char base : bases) {
            kmer_t tmp = kmer;
            if (member(tmp.roll_left(base))) succs.push_back(tmp);
          }
        }

        return succs;
      }

      size_t size_in_bytes() const { return dynamic_index.size_in_bytes(); }
      size_t size() const { return dynamic_index.size(); }
  };

#endif
