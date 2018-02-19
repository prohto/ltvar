#ifndef ENCODER_H
#define ENCODER_H

#include <map>
#include <string>
#include "ltvar.h"


class Encoder {
 protected:
  const LTVar& data_;
  mutable std::ostream* o_stream_;
  void serializeInto(std::ostream* o_stream) {
    o_stream_ = o_stream;
    encode(data_);
  }
  virtual void serializeFrom(const LTVar& value) { value.encode(*this); }
  virtual void encode(const LTVar& value) = 0;
  virtual void encode(const Array& value) = 0;
  virtual void encode(const bool& value) = 0;
  virtual void encode(const double& value) = 0;
  virtual void encode(const Hash& value) = 0;
  virtual void encode(const int& value) = 0;
  virtual void encode(const std::string& value) = 0;
  virtual void encode() = 0;
  Encoder(const LTVar& data) : data_(data) {}

  friend class Array;
  friend class Bool;
  friend class Double;
  friend class Hash;
  friend class Integer;
  friend class Text;
  friend class Void;

 public:
  friend std::ostream& operator<<(std::ostream& o_stream, Encoder& json) {
    json.serializeInto(&o_stream);
    return o_stream;
  }
};

#endif  // ENCODER_H
