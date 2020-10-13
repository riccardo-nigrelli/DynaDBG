#include <iostream>
#include "kmc_api/kmc_file.h"

const size_t KMER_LENGTH {31};

int main(int argc, char** argv) {

  CKMCFile kmer_database {};
  if (!kmer_database.OpenForListing(argv[1])) {
    std::cerr << "ERROR: unable to open " << argv[1] << std::endl;
    return EXIT_FAILURE;
  }

  uint32 kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, counter;
  uint64 total_kmer, max_cnt;

  kmer_database.Info(kmer_len, mode, cnt_size, prefix_len, signature_len, min_cnt, max_cnt, total_kmer);
  CKmerAPI kmer_obj(kmer_len);

  std::vector<std::string> data;
  char kmer[KMER_LENGTH + 1];
  while (kmer_database.ReadNextKmer(kmer_obj, counter)) {
    kmer_obj.to_string(kmer);
    data.push_back(kmer);
  }

  std::cout << data.size() << std::endl;
  std::cout << data.at(0) << std::endl;

  return 0;
}