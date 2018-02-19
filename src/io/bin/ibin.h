#ifndef IOBINSTREAM_H
#define IOBINSTREAM_H

#include <ostream>
#include "io/decoder.h"


class IBin : public Decoder {
 protected:
  virtual void decode(LTVar& value);
  virtual void decode(Array& value);
  virtual void decode(bool& value);
  virtual void decode(double& value);
  virtual void decode(Hash& value);
  virtual void decode(int& value);
  virtual void decode(std::string& value);
  virtual void decode();

 public:
  IBin(LTVar& data) : Decoder(data){};
  virtual ~IBin() {}
  static void decode(std::istream& stream, size_t& size);
};
#endif  // IOBINSTREAM_H
