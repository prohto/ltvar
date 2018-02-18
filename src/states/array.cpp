#include "array.h"
#include "io/io.h"
#include "iterator.h"

using namespace Harmonix;

LType& Array::operator[](const size_t idx) {
  if (idx >= value_.size()) value_.resize(idx + 1);
  return value_[idx];
}

const LType& Array::get(const size_t idx) const {
  static LType default_value;
  if (idx >= value_.size()) return default_value;
  return value_[idx];
}

LTypeIterator Array::begin() const {
  LTypeIterator iter(new ArrayIterator(0, value_.begin()));
  return std::move(iter);
}

LTypeIterator Array::end() const {
  LTypeIterator iter(new ArrayIterator(value_.size(), value_.end()));
  return iter;
}

void Array::encode(Encoder& stream) const { stream.encode(*this); }

void Array::decode(Decoder& stream) { stream.decode(*this); }
