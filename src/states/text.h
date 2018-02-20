#ifndef TEXT_H
#define TEXT_H

#include "void.h"

#include <iostream>

class Text : public Void {
 private:
  std::string value_;
  virtual bool equal_value( const Void& rhs ) const {
    if( !rhs.is_text() ) return false;
    return ( value_ == rhs.get_text() );
  }
 public:
  Text( std::string default_value = "" ): value_(default_value){}
  virtual Void* copy() const { return new Text(value_);}
  virtual bool is_text() const { return true; }
  virtual bool is_void() const { return false; }

  virtual bool get_bool() const { return (value_ == "true"); }
  virtual double get_double() const { return std::stod( value_ ); }
  virtual int get_int() const { return std::stoi( value_ ); }
  virtual std::string get_text() const { return value_; }
  virtual void encode(Encoder& output) const;
  virtual void decode(Decoder& stream);
};

#endif  // TEXT_H
