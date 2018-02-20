#ifndef OJSON_H
#define OJSON_H

#include <sstream>
#include "io/encoder.h"


class OJson : public Encoder {
 private:
  virtual void encode(const Array& value);
  virtual void encode(const bool& value);
  virtual void encode(const double& value);
  virtual void encode(const Hash& value);
  virtual void encode(const int& value);
  virtual void encode(const std::string& value);
  virtual void encode();
  virtual void encode(const LTVar& value);

 public:
  OJson(LTVar& value) : Encoder(value) {}
  virtual ~OJson() {}
};

#endif  // OJSON_H
