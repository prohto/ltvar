#ifndef TEST_IODATA_H
#define TEST_IODATA_H

#include <fstream>
#include <sstream>
#include "ltvar.h"

#include "test_data.h"


#define PUT_TYPE_INTO(t, s)                                    \
  {                                                            \
    uint8_t type = t;                                          \
    s.write(reinterpret_cast<char *>(&type), sizeof(uint8_t)); \
  }

template <typename T>
void PUT_VALUE_INTO(const T v, std::ostringstream &s) {
  s.write(reinterpret_cast<const char *>(&v), sizeof(v));
}

void PUT_VALUE_INTO(const std::string v, std::ostringstream &s) {
  PUT_VALUE_INTO(static_cast<unsigned char>(v.size()), s);
  s.write(v.c_str(), v.size());
}

class IOBinData {
  static std::string ucharVecToStr(std::vector<unsigned char> array) {
    return std::string(array.begin(), array.end());
  }

 public:
  static std::string empty_array() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kArray, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(0), og_stream);
    return og_stream.str();
  }

  static std::string bool_true() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kBool, og_stream);
    PUT_VALUE_INTO(bool(TEST_VALUE_BOOL_TRUE), og_stream);
    return og_stream.str();
  }

  static std::string bool_false() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kBool, og_stream);
    PUT_VALUE_INTO(bool(TEST_VALUE_BOOL_FALSE), og_stream);
    return og_stream.str();
  }

  static std::string double_value() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kDouble, og_stream);
    PUT_VALUE_INTO(TEST_VALUE_DOUBLE, og_stream);
    return og_stream.str();
  }

  static std::string empty_hash() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kHash, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(0), og_stream);
    return og_stream.str();
  }

  static std::string integer() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kInteger, og_stream);
    PUT_VALUE_INTO(TEST_VALUE_INTEGER, og_stream);
    return og_stream.str();
  }

  static std::string text() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kText, og_stream);
    PUT_VALUE_INTO(std::string(TEST_VALUE_TEXT), og_stream);
    return og_stream.str();
  }

  static std::string void_value() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kVoid, og_stream);
    return og_stream.str();
  }

  static std::string fill_array() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kArray, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(6), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kBool, og_stream);
    PUT_VALUE_INTO(bool(true), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kDouble, og_stream);
    PUT_VALUE_INTO(double(TEST_VALUE_DOUBLE), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kInteger, og_stream);
    PUT_VALUE_INTO(int(TEST_VALUE_INTEGER), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kText, og_stream);
    PUT_VALUE_INTO(std::string(TEST_VALUE_TEXT), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kVoid, og_stream);
    PUT_TYPE_INTO(LTVar::Type::kHash, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(0), og_stream);
    return og_stream.str();
  }

  static std::string fill_hash() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kHash, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(6), og_stream);
    PUT_VALUE_INTO(std::string("array"), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kArray, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(0), og_stream);
    PUT_VALUE_INTO(std::string("bool"), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kBool, og_stream);
    PUT_VALUE_INTO(bool(true), og_stream);
    PUT_VALUE_INTO(std::string("double"), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kDouble, og_stream);
    PUT_VALUE_INTO(double(TEST_VALUE_DOUBLE), og_stream);
    PUT_VALUE_INTO(std::string("integer"), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kInteger, og_stream);
    PUT_VALUE_INTO(int(TEST_VALUE_INTEGER), og_stream);
    PUT_VALUE_INTO(std::string("text"), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kText, og_stream);
    PUT_VALUE_INTO(std::string(TEST_VALUE_TEXT), og_stream);
    PUT_VALUE_INTO(std::string("void"), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kVoid, og_stream);
    return og_stream.str();
  }

  static std::string array_hash_nested() {
    std::ostringstream og_stream;
    PUT_TYPE_INTO(LTVar::Type::kHash, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(1), og_stream);
    PUT_VALUE_INTO(std::string("array"), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kArray, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(1), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kHash, og_stream);
    PUT_VALUE_INTO(static_cast<unsigned char>(1), og_stream);
    PUT_VALUE_INTO(std::string("void"), og_stream);
    PUT_TYPE_INTO(LTVar::Type::kVoid, og_stream);
    std::istringstream in_stream(og_stream.str());
    return og_stream.str();
  }

  static std::string len87() { return ucharVecToStr({0x57}); }
  static std::string len128() { return ucharVecToStr({0x80, 0x01}); }
  static std::string len4000() { return ucharVecToStr({0xa0, 0x1f}); }
  static std::string len32159() { return ucharVecToStr({0x9f, 0xfb, 0x01}); }
  static std::string len65433() { return ucharVecToStr({0x99, 0xff, 0x03}); }
  static std::string len65535() { return ucharVecToStr({0xff, 0xff, 0x03}); }
  static std::string len65536() { return ucharVecToStr({0x80, 0x80, 0x04}); }
  static std::string len15309671() {
    return ucharVecToStr({0xe7, 0xb6, 0xa6, 0x07});
  }
  static std::string len3603863485() {
    return ucharVecToStr({0xbd, 0xaf, 0xba, 0xb6, 0x0d});
  }
  static std::string len4294967295() {
    return ucharVecToStr({0xff, 0xff, 0xff, 0xff, 0x0f});
  }
};

#endif  // TEST_IODATA_H
