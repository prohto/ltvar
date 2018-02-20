#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include "ltvar.h"
#include "void.h"

class Array : public Void {
 private:
  LTVarArray value_;
  virtual bool equal_value(const Void& rhs) const {
    if (!rhs.is_array()) return false;
    return (value_ == ((Array&)rhs).value_);
  }

 public:
  Array() {}
  Array(const LTVarArray& value) : value_(value) {}
  virtual Void* copy() const {
    Array* rtn = new Array(value_);
    return rtn;
  }
  virtual bool equal(const LTVarArray& rhs) const { return value_ == rhs; };

  virtual bool is_array() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return value_.size() > 0; }
  virtual double get_double() const { return value_.size(); }
  virtual int get_int() const { return value_.size(); }
  virtual std::string get_text() const { return "<array>"; };

  virtual LTVar& operator[](const size_t idx);
  virtual const LTVar& get(const size_t idx) const;
  virtual const LTVar& get(const char* tag) const { return Void::get(tag); }

  virtual LTVarIterator begin() const;
  virtual LTVarIterator end() const;

  virtual LTVar& set(const size_t idx, const LTVar& value) {
    if (value_.size() <= idx) value_.resize(idx + 1);
    return value_[idx] = value;
  }
  virtual LTVar& set(const char* tag, const LTVar& value) {
    return Void::set(tag, value);
  }
  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
  size_t size() const { return value_.size(); }
  void resize(size_t size) { return value_.resize(size); }
};

#endif  // HASH_H
