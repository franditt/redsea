/*
 * Copyright (c) Oona Räisänen
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */
#ifndef RDSSTRING_H_
#define RDSSTRING_H_

#include <map>
#include <string>
#include <vector>

#include "src/common.h"

namespace redsea {

class RDSChar {
 public:
  RDSChar();
  explicit RDSChar(uint8_t _code);
  uint8_t code() const;
  std::string str() const;
  void set_codetable(eCodeTable codetable);

 private:
  uint8_t code_;
  eCodeTable codetable_;
};

class RDSString {
 public:
  explicit RDSString(int len = 8);
  void set(int pos, RDSChar chr);
  void set(int pos, RDSChar chr1, RDSChar chr2);
  void set_repertoire(int pos, eCodeTable codetable);
  eCodeTable repertoire_at(int pos) const;
  size_t length_received() const;
  size_t length_expected() const;
  std::vector<RDSChar> chars() const;
  std::string str() const;
  std::string last_complete_string() const;
  std::string last_complete_string(int start, int len) const;
  bool has_chars(int start, int len) const;
  bool complete() const;
  void clear();
  void resize(int n);

 private:
  std::vector<RDSChar> chars_;
  std::vector<RDSChar> last_complete_chars_;
  std::vector<bool> is_char_sequential_;
  int prev_pos_;
  std::string last_complete_string_;
  std::map<int, eCodeTable> repertoire_;
};

}  // namespace redsea
#endif  // RDSSTRING_H_
