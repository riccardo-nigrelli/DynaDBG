#include <iostream>
#include "encoder.hpp"
#include "pgm/pgm_index.hpp"
#include "kmc_api/kmc_file.h"
#include "pgm/pgm_index_dynamic.hpp"

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

  std::vector<uint64_t> data;
  char kmer[KMER_LENGTH + 1];
  while (kmer_database.ReadNextKmer(kmer_obj, counter)) {
    kmer_obj.to_string(kmer);
    data.push_back(enc::encode_string<uint64_t>(kmer));
  }

  std::sort(data.begin(), data.end());

  const int epsilon = 128;
  const pgm::PGMIndex<uint64_t, epsilon> index(data);
  std::cout << "PGM-Index dimension: " << index.size_in_bytes() << "[byte]" << std::endl;

  std::string input {};
  std::cout << "Enter the kmer you want to search for: ";
  std::cin >> input;

  uint64_t query = enc::encode_string<uint64_t>(input);
  pgm::ApproxPos range = index.search(query);
  std::cout << "Range: [" << range.lo << ", " << range.hi << ")" << std::endl;
  std::cout << "Approximate position: ~" << range.pos << std::endl;

  auto result = std::lower_bound(data.begin() + range.lo, data.begin() + range.hi, query);

  if (*result == query) std::cout << "K-mer found" << std::endl;
  else std::cerr << "K-mer not found" << std::endl;

  return 0;
}
