#include "ltvar.h"

#include <string.h>

#include "tokenizer.h"

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

LTVar& LTVar::operator[](size_t idx) { return (*(state_.get()))[idx]; }
LTVar& LTVar::operator[](int idx) { return (*(state_.get()))[idx]; }
LTVar& LTVar::operator[](const char tag[]) { return (*(state_.get()))[tag]; }
LTVar& LTVar::operator[](const LTVar& value) {
  if (value == Type::kInteger) {
    return (*(state_.get()))[static_cast<int>(value)];
  } else {
    return (*(state_.get()))[static_cast<std::string>(value).c_str()];
  }
}

const LTVar& LTVar::operator[](size_t idx) const {
  return state_.get()->get(idx);
}

const LTVar& LTVar::operator[](int idx) const { return state_.get()->get(idx); }

const LTVar& LTVar::operator[](const char tag[]) const {
  return state_.get()->get(tag);
}

const LTVar& LTVar::operator[](const LTVar& value) const {
  if (value == Type::kInteger) {
    return state_.get()->get(static_cast<int>(value));
  } else {
    return state_.get()->get(static_cast<std::string>(value).c_str());
  }
}

LTVar LTVar::get(const char* path) const {
  Tokenizer tk(path);
  static LTVar void_return;

  const LTVar* rtn = this;
  while (tk.hasNext()) {
    if (rtn->get_type() == Type::kVoid) {
      throw invalid_cast();
    } else if (rtn->get_type() == Type::kHash &&
               tk.getType() == Tokenizer::kTag) {
      auto tag = tk.getTag();
      if (rtn->state_.get()->find(tag.c_str()) == rtn->state_.get()->end()) {
        rtn = &void_return;
      } else {
        rtn = &(*rtn)[tag.c_str()];
      }
    } else if (rtn->get_type() == Type::kArray &&
               tk.getType() == Tokenizer::kIndex) {
      auto index = tk.getIndex();
      if (index >= rtn->size()) {
        rtn = &void_return;
      } else {
        rtn = &(*rtn)[index];
      }
    } else {
      throw invalid_cast();
    }
  }
  return *rtn;
}

LTVar& LTVar::set(const char path[]) {
  Tokenizer tk(path);
  static LTVar void_return;

  LTVar* rtn = this;
  while (tk.hasNext()) {
    if (rtn->get_type() == Type::kVoid) {
      if (tk.getType() == Tokenizer::kTag)
        *rtn = Type::kHash;
      else
        *rtn = Type::kArray;
    }
    if (rtn->get_type() == Type::kHash && tk.getType() == Tokenizer::kTag) {
      auto tag = tk.getTag();
      rtn = &(*rtn)[tag.c_str()];
    } else if (rtn->get_type() == Type::kArray &&
               tk.getType() == Tokenizer::kIndex) {
      auto index = tk.getIndex();
      rtn = &(*rtn)[index];
    } else {
      throw invalid_cast();
    }
  }
  return *rtn;
}

LTVarIterator LTVar::begin() const { return state_.get()->begin(); }
LTVarIterator LTVar::end() const { return state_.get()->end(); }
LTVarIterator LTVar::find(const char tag[]) const {
  return state_.get()->find(tag);
}
