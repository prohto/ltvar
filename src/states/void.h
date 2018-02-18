#ifndef VOID_H
#define VOID_H

#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "iterator.h"

namespace Harmonix {

class Encoder;
class Decoder;

class Void {
 protected:
  virtual bool equal_value(const Void& rhs) const {
    if (!rhs.is_void()) return false;
    return true;
  }

 public:
  Void() {}
  virtual ~Void() {}
  virtual Void* copy() const { return new Void(); }
  virtual bool equal(const Void& rhs) const { return equal_value(rhs); }
  virtual bool equal(const LTypeArray& rhs) const { return false; }
  virtual bool equal(bool rhs) const { return get_bool() == rhs; }
  virtual bool equal(const double rhs) const { return get_double() == rhs; }
  virtual bool equal(const LTypeHash& rhs) const { return false; }
  virtual bool equal(int rhs) const { return get_int() == rhs; }
  virtual bool equal(const std::string& rhs) const {
    return get_string() == rhs;
  }

  virtual bool is_array() const { return false; }
  virtual bool is_bool() const { return false; }
  virtual bool is_double() const { return false; }
  virtual bool is_hash() const { return false; }
  virtual bool is_integer() const { return false; }
  virtual bool is_string() const { return false; }
  virtual bool is_void() const { return true; }

  virtual bool get_bool() const { throw std::invalid_argument("invalid cast"); }
  virtual double get_double() const {
    throw std::invalid_argument("invalid cast");
  }
  virtual int get_int() const { throw std::invalid_argument("invalid cast"); }
  virtual std::string get_string() const { return "<void>"; }

  virtual const LType& get(const char* tag) const {
    if (tag == nullptr || tag == 0)
      throw std::invalid_argument("null pointer tag");
    return get(std::string(tag));
  }
  virtual const LType& get(const std::string& tag) const {
    throw std::invalid_argument("invalid cast");
  }
  virtual const LType& get(const size_t idx) const {
    throw std::invalid_argument("invalid cast");
  }

  virtual LType& operator[](const size_t idx) {
    throw std::invalid_argument("invalid cast");
  }
  virtual LType& operator[](const std::string& tag) {
    throw std::invalid_argument("invalid cast");
  }

  virtual LTypeIterator begin() const {
    throw std::invalid_argument("invalid cast");
  }
  virtual LTypeIterator end() const {
    throw std::invalid_argument("invalid cast");
  }

  virtual LType& set(const char* tag, const LType& value) {
    if (tag == nullptr || tag == 0)
      throw std::invalid_argument("null pointer tag");
    return set(std::string(tag), value);
  }
  virtual LType& set(const std::string& tag, const LType& value) {
    throw std::invalid_argument("invalid cast");
  }
  virtual LType& set(const size_t idx, const LType& value) {
    throw std::invalid_argument("invalid cast");
  }
  virtual size_t size() const { throw std::invalid_argument("invalid cast"); }

  bool operator==(const Void& rhs) const { return this->equal(rhs); };
  bool operator!=(const Void& rhs) const { return !this->equal(rhs); };

  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& input);
};
}  // namespace Harmonix
#endif  // VOID_H
