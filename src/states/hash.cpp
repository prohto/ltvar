#include "hash.h"
#include "io/io.h"
#include "iterator.h"

using namespace Harmonix;

LType& Hash::operator[](const std::string& tag) { return value_[tag]; }

const LType& Hash::get(const std::string& tag) const {
  static LType default_value;
  LTypeHash::const_iterator iter = value_.find(tag);
  if (iter == value_.end()) return default_value;
  return iter->second;
}

LTypeIterator Hash::begin() const {
  LTypeIterator iter(new HashIterator(value_.begin()));
  return std::move(iter);
}

LTypeIterator Hash::end() const {
  LTypeIterator iter(new HashIterator(value_.end()));
  return iter;
}

void Hash::encode(Encoder& stream) const { stream.encode(*this); }

void Hash::decode(Decoder& stream) { stream.decode(*this); }
