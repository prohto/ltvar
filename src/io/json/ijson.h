#ifndef IOJSONSTREAM_H
#define IOJSONSTREAM_H

#include <sstream>
#include "io/decoder.h"

namespace Harmonix {

class IJson : public Decoder {
 private:
  size_t lines_read_;
  virtual void decode(LType& value);

 public:
  IJson(LType& data) : Decoder(data), lines_read_(0) {}
  virtual ~IJson() {}
  size_t getLinesRead() const { return lines_read_; }
};

}  // namespace Harmonix
#endif  // IOJSONSTREAM_H
