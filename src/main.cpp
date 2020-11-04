#include <iostream>
#include <bitset>
#include "kmer.hpp"

int main() {

  typedef kmer_t<uint64_t> short_kmer;

  short_kmer kmer("CTAAAAGTGAAGTCAAATTTGTGAGTAACAA");
  std::cout << "uint64 rapresentation: " << kmer.value << std::endl;
  
  kmer.roll_left('G'); // kmer.value = TAAAAGTGAAGTCAAATTTGTGAGTAACAAG
  kmer.roll_right('C'); // kmer.value = CTAAAAGTGAAGTCAAATTTGTGAGTAACAA

  short_kmer kmer1("CTAAAAGTGAAGTCAAATTTGTGAGTAACAT");
  std::cout << "equality: " << (kmer == kmer1) << std::endl; // Mi aspetto uno 0
  
  return 0;
}

