#ifndef LTYPE_H
#define LTYPE_H

#include <memory>
#include <string>
#include "states/void.h"

namespace Harmonix {

class Void;
class Decoder;
class Encoder;

class LType {
 public:
  enum Type { kVoid, kBool, kDouble, kHash, kInteger, kArray, kText };
  LType();
  LType(const Type type);
  LType(const bool value);
  LType(const double value);
  LType(const int value);
  LType(const char* value);
  LType(const std::string& value);
  LType(const LTypeHash& value);
  LType(const LTypeArray& value);
  LType(const LType& src);
  LType(LType&& src);
  virtual ~LType();
  LType& operator=(const Type type);
  LType& operator=(const bool value);
  LType& operator=(const double value);
  LType& operator=(const int value);
  LType& operator=(const char*);
  LType& operator=(const std::string& value);
  LType& operator=(const LTypeHash& value);
  LType& operator=(const LTypeArray& value);
  LType& operator=(const LType& src);
  size_t size() const;
  bool operator==(const Type rhs) const;
  bool operator==(const LType& rhs) const;
  template <typename T>
  bool operator==(const T& rhs) const {
    return state_.get()->equal(rhs);
  }
  bool operator!=(const Type rhs) const;
  bool operator!=(const LType& rhs) const;
  template <typename T>
  bool operator!=(const T& rhs) const {
    return !state_.get()->equal(rhs);
  }
  Type get_type() const { return type_; }
  explicit operator bool() const;
  explicit operator double() const;
  explicit operator int() const;
  operator std::string() const;
  LType& operator[](const size_t idx);
  const LType& operator[](const size_t idx) const;
  LType& operator[](const std::string& tag);
  const LType& operator[](const std::string& tag) const;

  LTypeIterator begin() const;
  LTypeIterator end() const;

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
bool operator==(const T lhs, const LType& rhs) {
  return rhs == lhs;
}
template <typename T>
bool operator!=(const T lhs, const LType& rhs) {
  return rhs != lhs;
}
}  // namespace Harmonix

#include "states/array.h"
#include "states/bool.h"
#include "states/double.h"
#include "states/hash.h"
#include "states/integer.h"
#include "states/string.h"

#endif  // LTYPE_H
