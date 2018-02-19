#ifndef DECODER_H
#define DECODER_H

#include <map>
#include <string>
#include "ltvar.h"


class Decoder {
 protected:
  LTVar& data_;
  mutable std::istream* i_stream_;
  void deserializeFrom(std::istream* i_stream) {
    i_stream_ = i_stream;
    decode(data_);
  }
  virtual void deserializeInto(LTVar& value) { value.decode(*this); }
  virtual void decode(LTVar& value) = 0;
  virtual void decode(Array& value){ throw std::invalid_argument("Array value no supported by decoder"); }
  virtual void decode(bool& value){ throw std::invalid_argument("Bool value no supported by decoder"); }
  virtual void decode(double& value){ throw std::invalid_argument("Double value no supported by decoder"); }
  virtual void decode(Hash& value){ throw std::invalid_argument("Hash value no supported by decoder"); }
  virtual void decode(int& value){ throw std::invalid_argument("Int value no supported by decoder"); }
  virtual void decode(std::string& value){ throw std::invalid_argument("String value no supported by decoder"); }
  virtual void decode(){ throw std::invalid_argument("Void value no supported by decoder"); }
  Decoder(LTVar& data) : data_(data) {}

  friend class Array;
  friend class Bool;
  friend class Double;
  friend class Hash;
  friend class Integer;
  friend class Text;
  friend class Void;

 public:
  friend std::istream& operator>>(std::istream& i_stream, Decoder& decoder) {
    decoder.deserializeFrom(&i_stream);
    return i_stream;
  }
};

#endif  // DECODER_H
