#ifndef HASH_H
#define HASH_H

#include "ltvar.h"
#include "void.h"

class Hash : public Void {
 private:
  LTVarHash value_;
  virtual bool equal_value(const Void& rhs) const {
    if (!rhs.is_hash()) return false;
    return (value_ == ((Hash&)rhs).value_);
  }

 public:
  Hash() {}
  Hash(const LTVarHash& value) : value_(value){};
  virtual Void* copy() const { return new Hash(value_); }
  virtual bool equal(const LTVarHash& rhs) const { return value_ == rhs; };

  virtual bool is_hash() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return value_.size() > 0; }
  virtual double get_double() const { return value_.size(); }
  virtual int get_int() const { return value_.size(); }
  virtual std::string get_text() const { return "<hash>"; }

  virtual LTVar& operator[](const std::string& tag);
  virtual const LTVar& get(const std::string& tag) const;
  virtual const LTVar& get(const size_t idx) const { return Void::get(idx); }

  virtual LTVarIterator begin() const;
  virtual LTVarIterator end() const;

  virtual LTVar& set(const std::string& tag, const LTVar& value) {
    return value_[tag] = value;
  }
  virtual LTVar& set(const size_t idx, const LTVar& value) {
    return Void::set(idx, value);
  }
  virtual LTVar& set(const char* tag, const LTVar& value) {
    return Void::set(tag, value);
  }

  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
  size_t size() const { return value_.size(); }
};

#endif  // HASH_H
