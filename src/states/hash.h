#ifndef HASH_H
#define HASH_H

#include "ltype.h"
#include "void.h"

namespace Harmonix {
class Hash : public Void {
 private:
  LTypeHash value_;
  virtual bool equal_value(const Void& rhs) const {
    if (!rhs.is_hash()) return false;
    return (value_ == ((Hash&)rhs).value_);
  }

 public:
  Hash() {}
  Hash(const LTypeHash& value) : value_(value){};
  virtual Void* copy() const { return new Hash(value_); }
  virtual bool equal(const LTypeHash& rhs) const { return value_ == rhs; };

  virtual bool is_hash() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return value_.size() > 0; }
  virtual double get_double() const { return value_.size(); }
  virtual int get_int() const { return value_.size(); }
  virtual std::string get_string() const { return "<hash>"; }

  virtual LType& operator[](const std::string& tag);
  virtual const LType& get(const std::string& tag) const;
  virtual const LType& get(const size_t idx) const { return Void::get(idx); }

  virtual LTypeIterator begin() const;
  virtual LTypeIterator end() const;

  virtual LType& set(const std::string& tag, const LType& value) {
    return value_[tag] = value;
  }
  virtual LType& set(const size_t idx, const LType& value) {
    return Void::set(idx, value);
  }
  virtual LType& set(const char* tag, const LType& value) {
    return Void::set(tag, value);
  }

  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
  size_t size() const { return value_.size(); }
};
}  // namespace Harmonix

#endif  // HASH_H
