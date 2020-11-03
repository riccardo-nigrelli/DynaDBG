#pragma once

#ifndef _KMER_T_HPP_
  #define _KMER_T_HPP_

  #include <iostream>

  template <typename T>
  class kmer_t {

    const uint8_t encoder[128] = {
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
          if (encoder[_char] == 4) exit(EXIT_FAILURE);
          value = (value << 2) | encoder[_char];
        }
      }

      bool operator==(const kmer_t &kmer) const {
        return (value == kmer.value);
      }

      void roll_left(const unsigned char _char) {
        if (encoder[_char] == 4) exit(EXIT_FAILURE);
        value = (value << 2) | encoder[_char];
      }

      void roll_right(const unsigned char _char) {
        if (encoder[_char] == 4) exit(EXIT_FAILURE);
        value = encoder[_char] | (value >> 2);
      }
  };

#endif