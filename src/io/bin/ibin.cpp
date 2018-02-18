#include "ibin.h"
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

void IBin::decode(LType& value) {
  uint8_t type = LType::Type::kVoid;
  (*i_stream_).read(reinterpret_cast<char*>(&type), sizeof(type));
  value = LType::Type(type);
  deserializeInto(value);
}

void IBin::decode(std::istream& stream, size_t& size) {
  size = 0;
  unsigned char c = stream.get();
  if ((c & 0x80) == 0) {
    size = c;
    return;
  }
  size = c & 0x7f;

  c = stream.get();
  if ((c & 0x80) == 0) {
    size = size | (c << 7);
    return;
  }
  size = size | ((c & 0x7f) << 7);

  c = stream.get();
  if ((c & 0x80) == 0) {
    size = size | (c << 14);
    return;
  }
  size = size | ((c & 0x7f) << 14);

  c = stream.get();
  if ((c & 0x80) == 0) {
    size = size | (c << 21);
    return;
  }
  size = size | ((c & 0x7f) << 21);
  c = stream.get();
  size = size | (static_cast<size_t>(c) << 28);
}

void IBin::decode(Array& value) {
  size_t size;
  decode((*i_stream_), size);
  value.resize(size);
  for (size_t idx = 0; idx < size; idx++) {
    decode(value[idx]);
  }
}

void IBin::decode(bool& value) {
  (*i_stream_).read(reinterpret_cast<char*>(&value), sizeof(value));
}

void IBin::decode(double& value) {
  (*i_stream_).read(reinterpret_cast<char*>(&value), sizeof(value));
}

void IBin::decode(Hash& value) {
  size_t size;
  std::string tag;
  decode((*i_stream_), size);
  for (size_t idx = 0; idx < size; idx++) {
    decode(tag);
    decode(value[tag]);
  }
}

void IBin::decode(int& value) {
  (*i_stream_).read(reinterpret_cast<char*>(&value), sizeof(value));
}

void IBin::decode(std::string& value) {
  size_t size;
  decode((*i_stream_), size);
  std::vector<char> buffer(size);
  (*i_stream_).read(buffer.data(), static_cast<long>(size));
  value = std::string(buffer.begin(), buffer.end());
}

void IBin::decode() {}
