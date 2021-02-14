#include "hash.h"

#include "io/io.h"
#include "iterator.h"

LTVar& Hash::operator[](const char tag[]) { return value_[tag]; }

const LTVar& Hash::get(const char tag[]) const {
  static LTVar default_value;
  LTVarHash::const_iterator iter = value_.find(tag);
  if (iter == value_.end()) return default_value;
  return iter->second;
}

LTVarIterator Hash::begin() const {
  LTVarIterator iter(new HashIterator(value_.begin()));
  return iter;
}

LTVarIterator Hash::end() const {
  LTVarIterator iter(new HashIterator(value_.end()));
  return iter;
}

LTVarIterator Hash::find(const char tag[]) const {
  LTVarIterator iter(new HashIterator(value_.find(tag)));
  return iter;
}

void Hash::encode(Encoder& stream) const { stream.encode(*this); }

void Hash::decode(Decoder& stream) { stream.decode(*this); }
