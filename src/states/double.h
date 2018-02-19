#ifndef DOUBLE_H
#define DOUBLE_H

#include "void.h"

class Double : public Void {
 private:
  double value_;
  virtual bool equal_value( const Void& rhs ) const {
    if( !rhs.is_double() ) return false;
    return ( value_ == rhs.get_double() );
  }

 public:
  Double( double default_value = 0.0 ): value_(default_value){}
  virtual Void* copy() const { return new Double(value_);}
  virtual bool is_double() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return value_; }
  virtual double get_double() const { return value_; }
  virtual int get_int() const { return value_; }
  virtual std::string get_text() const {
    return std::to_string( value_ );
  }
  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
};

#endif  // DOUBLE_H
