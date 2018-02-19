#include "array.h"
#include "io/io.h"
#include "iterator.h"


LTVar& Array::operator[](const size_t idx) {
  if (idx >= value_.size()) value_.resize(idx + 1);
  return value_[idx];
}

const LTVar& Array::get(const size_t idx) const {
  static LTVar default_value;
  if (idx >= value_.size()) return default_value;
  return value_[idx];
}

LTVarIterator Array::begin() const {
  LTVarIterator iter(new ArrayIterator(0, value_.begin()));
  return std::move(iter);
}

LTVarIterator Array::end() const {
  LTVarIterator iter(new ArrayIterator(value_.size(), value_.end()));
  return iter;
}

void Array::encode(Encoder& stream) const { stream.encode(*this); }

void Array::decode(Decoder& stream) { stream.decode(*this); }
