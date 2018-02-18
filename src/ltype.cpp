#include "ltype.h"

using namespace Harmonix;

LType::LType() : state_(new Void()), type_(kVoid) {}

LType::LType(const Type type) { reset(type); }

LType::LType(const bool value) : state_(new Bool(value)), type_(kBool) {}

LType::LType(const double value) : state_(new Double(value)), type_(kDouble) {}

LType::LType(const int value) : state_(new Integer(value)), type_(kInteger) {}

LType::LType(const char* value) : state_(new String(value)), type_(kText) {}

LType::LType(const std::string& value)
    : state_(new String(value)), type_(kText) {}

LType::LType(const LTypeHash& value) : state_(new Hash(value)), type_(kHash) {}

LType::LType(const LTypeArray& value)
    : state_(new Array(value)), type_(kArray) {}

LType::LType(const LType& src) {
  type_ = src.type_;
  state_.reset(src.state_.get()->copy());
}

LType::LType(LType&& rhs) {
  if (this != &rhs) {
    type_ = rhs.type_;
    state_ = std::move(rhs.state_);
  }
}

LType::~LType() {}

LType& LType::operator=(const Type type) {
  reset(type);
  return *this;
}

LType& LType::operator=(const bool value) {
  type_ = kBool;
  state_.reset(new Bool(value));
  return *this;
}

LType& LType::operator=(const double value) {
  type_ = kDouble;
  state_.reset(new Double(value));
  return *this;
}

LType& LType::operator=(const int value) {
  type_ = kInteger;
  state_.reset(new Integer(value));
  return *this;
}

LType& LType::operator=(const char* value) {
  type_ = kText;
  state_.reset(new String(value));
  return *this;
}

LType& LType::operator=(const std::string& value) {
  type_ = kText;
  state_.reset(new String(value));
  return *this;
}

LType& LType::operator=(const LTypeHash& value) {
  type_ = kHash;
  state_.reset(new Hash(value));
  return *this;
}

LType& LType::operator=(const LTypeArray& value) {
  type_ = kArray;
  state_.reset(new Array(value));
  return *this;
}

LType& LType::operator=(const LType& src) {
  type_ = src.type_;
  state_.reset(src.state_.get()->copy());
  return *this;
}

void LType::reset(Type type) {
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
      state_.reset(new String());
      break;
    case kVoid:
      state_.reset(new Void());
      break;
  }
}

size_t LType::size() const { return state_.get()->size(); }

bool LType::operator==(const Type rhs) const { return type_ == rhs; }

bool LType::operator==(const LType& rhs) const {
  if (type_ == rhs.type_) {
    return state_.get()->equal(*rhs.state_);
  }
  return false;
}

bool LType::operator!=(const LType& rhs) const {
  if (type_ != rhs.type_) {
    return true;
  }
  return !state_.get()->equal(*rhs.state_);
}

bool LType::operator!=(const Type rhs) const { return type_ != rhs; }

void LType::encode(Encoder& ostream) const { state_.get()->encode(ostream); }

void LType::decode(Decoder& istream) { state_.get()->decode(istream); }

LType::operator bool() const { return state_.get()->get_bool(); }
LType::operator double() const { return state_.get()->get_double(); }
LType::operator int() const { return state_.get()->get_int(); }
LType::operator std::string() const { return state_.get()->get_string(); }

LType& LType::operator[](const size_t idx) { return (*(state_.get()))[idx]; }

const LType& LType::operator[](const size_t idx) const {
  return state_.get()->get(idx);
}

LType& LType::operator[](const std::string& tag) {
  return (*(state_.get()))[tag];
}

const LType& LType::operator[](const std::string& tag) const {
  return state_.get()->get(tag);
}

LTypeIterator LType::begin() const { return state_.get()->begin(); }
LTypeIterator LType::end() const { return state_.get()->end(); }
