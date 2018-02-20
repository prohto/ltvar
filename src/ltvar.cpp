#include "ltvar.h"


LTVar::LTVar() : state_(new Void()), type_(kVoid) {}

LTVar::LTVar(const Type type) { reset(type); }

LTVar::LTVar(const bool value) : state_(new Bool(value)), type_(kBool) {}

LTVar::LTVar(const double value) : state_(new Double(value)), type_(kDouble) {}

LTVar::LTVar(const int value) : state_(new Integer(value)), type_(kInteger) {}

LTVar::LTVar(const char* value) : state_(new Text(value)), type_(kText) {}

LTVar::LTVar(const std::string& value)
    : state_(new Text(value)), type_(kText) {}

LTVar::LTVar(const LTVarHash& value) : state_(new Hash(value)), type_(kHash) {}

LTVar::LTVar(const LTVarArray& value)
    : state_(new Array(value)), type_(kArray) {}

LTVar::LTVar(const LTVar& src) {
  type_ = src.type_;
  state_.reset(src.state_.get()->copy());
}

LTVar::LTVar(LTVar&& rhs) {
  if (this != &rhs) {
    type_ = rhs.type_;
    state_ = std::move(rhs.state_);
  }
}

LTVar::~LTVar() {}

LTVar& LTVar::operator=(const Type type) {
  reset(type);
  return *this;
}

LTVar& LTVar::operator=(const bool value) {
  type_ = kBool;
  state_.reset(new Bool(value));
  return *this;
}

LTVar& LTVar::operator=(const double value) {
  type_ = kDouble;
  state_.reset(new Double(value));
  return *this;
}

LTVar& LTVar::operator=(const int value) {
  type_ = kInteger;
  state_.reset(new Integer(value));
  return *this;
}

LTVar& LTVar::operator=(const char* value) {
  type_ = kText;
  state_.reset(new Text(value));
  return *this;
}

LTVar& LTVar::operator=(const std::string& value) {
  type_ = kText;
  state_.reset(new Text(value));
  return *this;
}

LTVar& LTVar::operator=(const LTVarHash& value) {
  type_ = kHash;
  state_.reset(new Hash(value));
  return *this;
}

LTVar& LTVar::operator=(const LTVarArray& value) {
  type_ = kArray;
  state_.reset(new Array(value));
  return *this;
}

LTVar& LTVar::operator=(const LTVar& src) {
  type_ = src.type_;
  state_.reset(src.state_.get()->copy());
  return *this;
}

void LTVar::reset(Type type) {
  type_ = type;
  switch (type) {
    case kArray:
      state_.reset(new Array());
      break;
    case kBool:
      state_.reset(new Bool());
      break;
    case kDouble:
      state_.reset(new Double());
      break;
    case kHash:
      state_.reset(new Hash());
      break;
    case kInteger:
      state_.reset(new Integer());
      break;
    case kText:
      state_.reset(new Text());
      break;
    case kVoid:
      state_.reset(new Void());
      break;
  }
}

size_t LTVar::size() const { return state_.get()->size(); }

bool LTVar::operator==(const Type rhs) const { return type_ == rhs; }

bool LTVar::operator==(const LTVar& rhs) const {
  if (type_ == rhs.type_) {
    return state_.get()->equal(*rhs.state_);
  }
  return false;
}

bool LTVar::operator!=(const LTVar& rhs) const {
  if (type_ != rhs.type_) {
    return true;
  }
  return !state_.get()->equal(*rhs.state_);
}

bool LTVar::operator!=(const Type rhs) const { return type_ != rhs; }

void LTVar::encode(Encoder& ostream) const { state_.get()->encode(ostream); }

void LTVar::decode(Decoder& istream) { state_.get()->decode(istream); }

LTVar::operator bool() const { return state_.get()->get_bool(); }
LTVar::operator double() const { return state_.get()->get_double(); }
LTVar::operator int() const { return state_.get()->get_int(); }
LTVar::operator std::string() const { return state_.get()->get_text(); }

LTVar& LTVar::operator[](const size_t idx) { return (*(state_.get()))[idx]; }

const LTVar& LTVar::operator[](const size_t idx) const {
  return state_.get()->get(idx);
}

LTVar& LTVar::operator[](const std::string& tag) {
  return (*(state_.get()))[tag];
}

const LTVar& LTVar::operator[](const std::string& tag) const {
  return state_.get()->get(tag);
}

LTVarIterator LTVar::begin() const { return state_.get()->begin(); }
LTVarIterator LTVar::end() const { return state_.get()->end(); }
