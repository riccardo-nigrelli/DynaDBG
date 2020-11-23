#ifndef _KMER_T_HPP_
  #define _KMER_T_HPP_

  #include <iostream>
  #include <bitset>

  template <typename T, const uint8_t size = 8 * sizeof(T)>
  class kmer_t {

    static constexpr uint8_t encoder[128] = {
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 0, 4, 1, 4, 4,
      4, 2, 4, 4, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 3, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 0, 4, 1,
      4, 4, 4, 2, 4, 4, 4, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 3, 4, 4, 4,
      4, 4, 4, 4, 4, 4, 4, 4
    };

    public:

      T value {0};

      explicit kmer_t(const std::string &str) {
        for (unsigned char _char : str) {
          value = (value << 2) | encoder[_char];
        }
      }

      inline bool operator==(const kmer_t &kmer) const { return value == kmer.value; }

      kmer_t& roll_left(const unsigned char _char) {
        value = (value << 2) | encoder[_char];
        return *this;
      }

      kmer_t& roll_right(const unsigned char _char) {
        value = (value >> 2) | ((T) encoder[_char] << (size - 4));
        return *this;
      }

      std::string to_string() {
        std::string kmer;
        std::string bits = std::bitset<size - 2>(value).to_string();

        for (size_t i = 0; i < bits.length(); i += 2) {
          uint8_t by_val = (uint8_t)(std::bitset<2>(bits.substr(i, 2)).to_ulong());
          auto index = std::find(std::begin(encoder), std::end(encoder), by_val);
          
          if (index != std::end(encoder)) {
            kmer.push_back((char)std::distance(encoder, index));
          }
        }

        return kmer;
      }
  };

#endif