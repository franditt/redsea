#include "src/ascii_in.h"

#include <iostream>
#include <stdexcept>
#include <string>

#include "src/groups.h"
#include "src/util.h"

namespace redsea {

AsciiBits::AsciiBits(bool has_echo) : is_eof_(false), echo_stdout_(has_echo) {
}

AsciiBits::~AsciiBits() {
}

int AsciiBits::getNextBit() {
  int result = 0;
  while (result != '0' && result != '1' && result != EOF) {
    result = getchar();
    if (echo_stdout_)
      putchar(result);
  }

  if (result == EOF) {
    is_eof_ = true;
    return 0;
  }

  return (result == '1');
}

bool AsciiBits::isEOF() const {
  return is_eof_;
}

Group getNextGroupRSpy() {
  Group group;

  bool finished = false;

  while (!(finished || std::cin.eof())) {
    std::string line;
    std::getline(std::cin, line);
    if (line.length() < 16)
      continue;

    for (int nblok=0; nblok < 4; nblok++) {
      uint16_t bval = 0;
      bool block_still_valid = true;
      group.hasOffset[nblok == 3 ? OFFSET_D : nblok] = true;

      int nyb = 0;
      while (nyb < 4) {
        if (line.length() < 1) {
          finished = true;
          break;
        }

        std::string single = line.substr(0, 1);

        if (single.compare(" ") != 0) {
          try {
            int nval = std::stoi(std::string(single), nullptr, 16);
            bval = (bval << 4) + nval;
          } catch (std::invalid_argument) {
            block_still_valid = false;
            group.hasOffset[nblok == 3 ? OFFSET_D : nblok] = false;
          }
          nyb++;
        }
        line = line.substr(1);
      }

      group.block[nblok == 3 ? OFFSET_D : nblok] = bval;

      if (nblok == 3)
        finished = true;
    }
  }

  group.type = (group.hasOffset[OFFSET_B] ?
      bits(group.block[OFFSET_B], 11, 5) : 0);

  return group;
}

}  // namespace redsea
