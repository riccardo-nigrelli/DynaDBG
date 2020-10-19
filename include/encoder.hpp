#ifndef _ENCODER_HPP_
  #define _ENCODER_HPP_

  #include <map>
  #include <limits>
  #include <iostream>
  #include <algorithm>

  const std::map<char, unsigned short> encoding {
    {'A', 0b00},
    {'C', 0b01},
    {'G', 0b10},
    {'T', 0b11}
  };

  namespace enc {
    
    template<typename T>
    static T encode_string(const std::string kmer) {
      T result {};

      for (auto _char : kmer) {
        if (encoding.find(_char) == encoding.end()) {
          std::cerr << "ERROR: '" << _char << "' is an invalid character" << std::endl;
          exit(EXIT_FAILURE);
        }
        else {
          result <<= 2;
          result |= encoding.find(_char)->second;
        }
      }

      return result;
    }    
  }

#endif