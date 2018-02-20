#ifndef BOOL_H
#define BOOL_H

#include "void.h"

class Bool : public Void {
 private:
  bool value_;
  virtual bool equal_value( const Void& rhs ) const {
    if( !rhs.is_bool() ) return false;
    return ( value_ == rhs.get_bool() );
  }
 public:
  Bool(bool default_value = false ): value_(default_value) {}
  virtual Void* copy() const { return new Bool(value_);}
  virtual bool is_bool() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return value_; }
  virtual double get_double() const { return value_; }
  virtual int get_int() const { return value_; }
  virtual std::string get_text() const { return (value_ ? "true" : "false"); }
  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
};

#endif  // BOOL_H
