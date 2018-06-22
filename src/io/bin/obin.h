#ifndef OBIN_H
#define OBIN_H

#include <ostream>
#include "io/encoder.h"


class OBin : public Encoder {
 protected:
  virtual void encode(const LTVar& value);
  virtual void encode(const Array& value);
  virtual void encode(const bool& value);
  virtual void encode(const double& value);
  virtual void encode(const Hash& value);
  virtual void encode(const int& value);
  virtual void encode(const std::string& value);
  virtual void encode();

 public:
  OBin(const LTVar& data) : Encoder(data) {}
  static void encode(std::ostream& stream, size_t size);
};
#endif  // OBIN_H
