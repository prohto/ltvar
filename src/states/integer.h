#ifndef INTEGER_H
#define INTEGER_H

#include "void.h"

namespace Harmonix {
class Integer : public Void {
 private:
  int value_;
  virtual bool equal_value( const Void& rhs ) const {
    if( !rhs.is_integer() ) return false;
    return ( value_ == rhs.get_int() );
  }
 public:
  Integer( int default_value = 0): value_(default_value){}
  virtual Void* copy() const { return new Integer(value_);}
  virtual bool is_integer() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return value_; }
  virtual double get_double() const { return value_; }
  virtual int get_int() const { return value_; }
  virtual std::string get_string() const {
    return std::to_string( value_ );
  }
  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
};
}

#endif  // INTEGER_H
