#ifndef STRING_H
#define STRING_H

#include "void.h"

#include <iostream>

namespace Harmonix {
class String : public Void {
 private:
  std::string value_;
  virtual bool equal_value( const Void& rhs ) const {
    if( !rhs.is_string() ) return false;
    return ( value_ == rhs.get_string() );
  }
 public:
  String( std::string default_value = "" ): value_(default_value){}
  virtual Void* copy() const { return new String(value_);}
  virtual bool is_string() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return (value_ == "true"); }
  virtual double get_double() const { return std::stod( value_ ); }
  virtual int get_int() const { return std::stoi( value_ ); }
  virtual std::string get_string() const { return value_; }
  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
};
}

#endif  // STRING_H
