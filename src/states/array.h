#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include "ltype.h"
#include "void.h"

namespace Harmonix {
class Array : public Void {
 private:
  LTypeArray value_;
  virtual bool equal_value(const Void& rhs) const {
    if (!rhs.is_array()) return false;
    return (value_ == ((Array&)rhs).value_);
  }

 public:
  Array() {}
  Array(const LTypeArray& value) : value_(value) {}
  virtual Void* copy() const {
    Array* rtn = new Array(value_);
    return rtn;
  }
  virtual bool equal(const LTypeArray& rhs) const { return value_ == rhs; };

  virtual bool is_array() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return value_.size() > 0; }
  virtual double get_double() const { return value_.size(); }
  virtual int get_int() const { return value_.size(); }
  virtual std::string get_string() const { return "<array>"; };

  virtual LType& operator[](const size_t idx);
  virtual const LType& get(const size_t idx) const;
  virtual const LType& get(const char* tag) const { return Void::get(tag); }

  virtual LTypeIterator begin() const;
  virtual LTypeIterator end() const;

  virtual LType& set(const size_t idx, const LType& value) {
    if (value_.size() <= idx) value_.resize(idx + 1);
    return value_[idx] = value;
  }
  virtual LType& set(const char* tag, const LType& value) {
    return Void::set(tag, value);
  }
  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
  size_t size() const { return value_.size(); }
  void resize(size_t size) { return value_.resize(size); }
};
}  // namespace Harmonix

#endif  // HASH_H
