#ifndef _DYNA_DBG_HPP_
  #define _DYNA_DBG_HPP_
  
  #include <iostream>
  #include "kmer.hpp"
  #include "pgm/pgm_index.hpp"
  #include "kmc_api/kmc_file.h"
  #include "pgm/pgm_index_dynamic.hpp"

  namespace dbg {

    template<class kmer_t>
    class DynaDBG {
      
      private:
        std::vector<kmer_t> data;
        using PGMType = pgm::PGMIndex<kmer_t>;
        pgm::DynamicPGMIndex<kmer_t, uid_t, PGMType, 1> dynamic_index();
  
      protected:
        void initialize(const std::string path) {
          CKMCFile database {};
          std::cout << path << std::endl;
          
          if (!database.OpenForListing(path)) {
            std::cerr << "Error: unable to open " << path << std::endl;
          }
          
          uint32 kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, counter;
          uint64 total_kmer, max_cnt;

          database.Info(kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, max_cnt, total_kmer);
          CKmerAPI kmer_obj(kmer_len);

          // std::string kmer;
          // while (database.ReadNextKmer(kmer_obj, counter)) {
          //   kmer_obj.to_string(kmer);
          //   data.push_back(kmer_t(kmer));
          // }

          // std::sort(data.begin(), data.end());
        }

      public:
        explicit DynaDBG(const std::string path) {
          initialize(path);
        }

        bool exists(const kmer_t &kmer) {
          return false;
        }
    };
  }

#endif