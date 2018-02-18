#include "obin.h"
#include "io.h"
#include "iterator.h"
#include "ltype.h"
#include "states/array.h"
#include "states/bool.h"
#include "states/double.h"
#include "states/hash.h"
#include "states/integer.h"
#include "states/string.h"
#include "states/void.h"

using namespace Harmonix;

void OBin::encode(const LType& value) {
  uint8_t type = value.get_type();
  (*o_stream_).write(reinterpret_cast<char*>(&type), sizeof(type));
  serializeFrom(value);
}

void OBin::encode(std::ostream& stream, size_t size) {
  char c = 0x0000007f & size;
  if ((size & 0xffffff80) == 0) {
    stream.put(c);
    return;
  }
  stream.put(c | 0x80);
  size = size >> 7;

  c = 0x0000007f & size;
  if ((size & 0xffffff80) == 0) {
    stream.put(c);
    return;
  }
  stream.put(c | 0x80);
  size = size >> 7;

  c = 0x0000007f & size;
  if ((size & 0xffffff80) == 0) {
    stream.put(c);
    return;
  }
  stream.put(c | 0x80);
  size = size >> 7;

  c = 0x0000007f & size;
  if ((size & 0xffffff80) == 0) {
    stream.put(c);
    return;
  }
  stream.put(c | 0x80);
  size = size >> 7;

  c = 0x0000007f & size;
  stream.put(c);
}

void OBin::encode(const Array& value) {
  encode((*o_stream_), value.size());
  for (auto iter : value) {
    encode(iter);
  }
}

void OBin::encode(const bool& value) {
  (*o_stream_).write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void OBin::encode(const double& value) {
  (*o_stream_).write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void OBin::encode(const Hash& value) {
  encode((*o_stream_), value.size());
  for (LTypeIterator iter = value.begin(); iter != value.end(); ++iter) {
    std::string tag = iter.first();
    encode(tag);
    encode(iter.second());
  }
}

void OBin::encode(const int& value) {
  (*o_stream_).write(reinterpret_cast<const char*>(&value), sizeof(value));
}

void OBin::encode(const std::string& value) {
  size_t len = value.size();
  encode((*o_stream_), value.size());
  (*o_stream_).write(value.c_str(), static_cast<long>(len));
}

void OBin::encode() {}
