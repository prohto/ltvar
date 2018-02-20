#include "ltvar.h"


LTVarIterator::LTVarIterator() : state_(nullptr) {}

LTVarIterator::LTVarIterator(VoidIterator* state) : state_(state) {}

LTVarIterator::LTVarIterator(LTVarIterator&& rhs)
    : state_(std::move(rhs.state_)) {}

LTVarIterator::~LTVarIterator() {}

LTVar LTVarIterator::first() { return state_->first(); }

const LTVar& LTVarIterator::second() { return state_->second(); }

bool LTVarIterator::operator!=(const LTVarIterator& rhs) const {
  if (state_.get() == nullptr || rhs.state_.get() == nullptr) {
  } else if (state_->is_hash() && rhs.state_->is_hash()) {
    return !state_->equals(*rhs.state_);
  } else if (state_->is_array() && rhs.state_->is_array()) {
    return !state_->equals(*rhs.state_);
  }
  return true;
}

bool LTVarIterator::operator==(const LTVarIterator& rhs) const {
  return !(*this != rhs);
}

LTVarIterator& LTVarIterator::operator++() {
  if (state_ != nullptr) state_->increment(1);
  return *this;
}

LTVarIterator& LTVarIterator::operator++(int delta ) {
  if (delta == 0 ) delta=1;
  if (state_ != nullptr) state_->increment(delta);
  return *this;
}

const LTVar& LTVarIterator::operator*() { return state_->second(); }

LTVarIterator& LTVarIterator::operator=(LTVarIterator&& rhs) {
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

LTVar HashIterator::first() { return std::move(LTVar(iterator_->first)); }
const LTVar& HashIterator::second() { return iterator_->second; }

bool ArrayIterator::equals(const VoidIterator& rhs) const {
  return iterator_ == ((ArrayIterator&)rhs).iterator_;
}

void ArrayIterator::increment(int delta) {
  index_ += delta;
  iterator_ += delta;
}

LTVar ArrayIterator::first() { return std::move(LTVar((int)index_)); }
const LTVar& ArrayIterator::second() { return *iterator_; }
