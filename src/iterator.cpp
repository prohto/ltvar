#include "iterator.h"
#include "ltype.h"
#include "states/array.h"
#include "states/bool.h"
#include "states/double.h"
#include "states/hash.h"
#include "states/integer.h"
#include "states/string.h"
#include "states/void.h"

using namespace Harmonix;

LTypeIterator::LTypeIterator() : state_(nullptr) {}

LTypeIterator::LTypeIterator(VoidIterator* state) : state_(state) {}

LTypeIterator::LTypeIterator(LTypeIterator&& rhs)
    : state_(std::move(rhs.state_)) {}

LTypeIterator::~LTypeIterator() {}

LType LTypeIterator::first() { return state_->first(); }

const LType& LTypeIterator::second() { return state_->second(); }

bool LTypeIterator::operator!=(const LTypeIterator& rhs) const {
  if (state_.get() == nullptr || rhs.state_.get() == nullptr) {
  } else if (state_->is_hash() && rhs.state_->is_hash()) {
    return !state_->equals(*rhs.state_);
  } else if (state_->is_array() && rhs.state_->is_array()) {
    return !state_->equals(*rhs.state_);
  }
  return true;
}

bool LTypeIterator::operator==(const LTypeIterator& rhs) const {
  return !(*this != rhs);
}

LTypeIterator& LTypeIterator::operator++() {
  if (state_ != nullptr) state_->increment(1);
  return *this;
}

const LType& LTypeIterator::operator*() { return state_->second(); }

LTypeIterator& LTypeIterator::operator=(LTypeIterator&& rhs) {
  if (this != &rhs) {
    state_ = std::move(rhs.state_);
  }
  return *this;
}

bool HashIterator::equals(const VoidIterator& rhs) const {
  return iterator_ == ((HashIterator&)rhs).iterator_;
}

void HashIterator::increment(int delta) {
  for (int idx = 0; idx < delta; idx++) iterator_++;
}

LType HashIterator::first() { return std::move(LType(iterator_->first)); }
const LType& HashIterator::second() { return iterator_->second; }

bool ArrayIterator::equals(const VoidIterator& rhs) const {
  return iterator_ == ((ArrayIterator&)rhs).iterator_;
}

void ArrayIterator::increment(int delta) {
  index_ += delta;
  iterator_ += delta;
}

LType ArrayIterator::first() { return std::move(LType((int)index_)); }
const LType& ArrayIterator::second() { return *iterator_; }
