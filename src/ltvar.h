#ifndef LTVAR_H
#define LTVAR_H

#include <memory>
#include <string>
#include "states/void.h"


class Void;
class Decoder;
class Encoder;

class LTVar {
 public:
  enum Type { kVoid, kBool, kDouble, kHash, kInteger, kArray, kText };
  LTVar();
  LTVar(const Type type);
  LTVar(const bool value);
  LTVar(const double value);
  LTVar(const int value);
  LTVar(const char* value);
  LTVar(const std::string& value);
  LTVar(const LTVarHash& value);
  LTVar(const LTVarArray& value);
  LTVar(const LTVar& src);
  LTVar(LTVar&& src);
  virtual ~LTVar();
  LTVar& operator=(const Type type);
  LTVar& operator=(const bool value);
  LTVar& operator=(const double value);
  LTVar& operator=(const int value);
  LTVar& operator=(const char*);
  LTVar& operator=(const std::string& value);
  LTVar& operator=(const LTVarHash& value);
  LTVar& operator=(const LTVarArray& value);
  LTVar& operator=(const LTVar& src);
  size_t size() const;
  bool operator==(const Type rhs) const;
  bool operator==(const LTVar& rhs) const;
  template <typename T>
  bool operator==(const T& rhs) const {
    return state_.get()->equal(rhs);
  }
  bool operator!=(const Type rhs) const;
  bool operator!=(const LTVar& rhs) const;
  template <typename T>
  bool operator!=(const T& rhs) const {
    return !state_.get()->equal(rhs);
  }
  Type get_type() const { return type_; }
  explicit operator bool() const;
  explicit operator double() const;
  explicit operator int() const;
  operator std::string() const;
  LTVar& operator[](const size_t idx);
  const LTVar& operator[](const size_t idx) const;
  LTVar& operator[](const std::string& tag);
  const LTVar& operator[](const std::string& tag) const;

  LTVarIterator begin() const;
  LTVarIterator end() const;

  friend class Decoder;
  friend class Encoder;

 protected:
  std::unique_ptr<Void> state_;
  Type type_;
  void reset(Type type);
  virtual void encode(Encoder& ostream) const;
  virtual void decode(Decoder& istream);
};
template <typename T>
bool operator==(const T lhs, const LTVar& rhs) {
  return rhs == lhs;
}
template <typename T>
bool operator!=(const T lhs, const LTVar& rhs) {
  return rhs != lhs;
}

#include "states/array.h"
#include "states/bool.h"
#include "states/double.h"
#include "states/hash.h"
#include "states/integer.h"
#include "states/text.h"

#endif  // LTVAR_H
