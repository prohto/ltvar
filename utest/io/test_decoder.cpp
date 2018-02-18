#include "test_data.h"
#include "utest.h"

#include "io/mockdecoder.h"

using namespace Harmonix;
using ::testing::An;

TEST(Decoder, decode_array) {
  LType value(test_array);
  MockDecoder decoder(value);

  EXPECT_CALL(decoder, decode(An<Array&>())).Times(1);
  EXPECT_CALL(decoder, decode(An<bool&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<double&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<Hash&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<int&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<std::string&>())).Times(0);
  EXPECT_CALL(decoder, decode()).Times(0);

  std::stringstream stream;

  stream >> decoder;
}

TEST(Decoder, decode_bool) {
  LType value(TEST_VALUE_BOOL_TRUE);
  MockDecoder decoder(value);

  EXPECT_CALL(decoder, decode(An<Array&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<bool&>())).Times(1);
  EXPECT_CALL(decoder, decode(An<double&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<Hash&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<int&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<std::string&>())).Times(0);
  EXPECT_CALL(decoder, decode()).Times(0);

  std::stringstream stream;

  stream >> decoder;
}

TEST(Decoder, decode_double) {
  LType value(TEST_VALUE_DOUBLE);
  MockDecoder decoder(value);

  EXPECT_CALL(decoder, decode(An<Array&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<bool&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<double&>())).Times(1);
  EXPECT_CALL(decoder, decode(An<Hash&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<int&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<std::string&>())).Times(0);
  EXPECT_CALL(decoder, decode()).Times(0);

  std::stringstream stream;

  stream >> decoder;
}

TEST(Decoder, decode_hash) {
  LType value(test_hash);
  MockDecoder decoder(value);

  EXPECT_CALL(decoder, decode(An<Array&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<bool&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<double&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<Hash&>())).Times(1);
  EXPECT_CALL(decoder, decode(An<int&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<std::string&>())).Times(0);
  EXPECT_CALL(decoder, decode()).Times(0);

  std::stringstream stream;

  stream >> decoder;
}

TEST(Decoder, decode_integer) {
  LType value(TEST_VALUE_INTEGER);
  MockDecoder decoder(value);

  EXPECT_CALL(decoder, decode(An<Array&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<bool&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<double&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<Hash&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<int&>())).Times(1);
  EXPECT_CALL(decoder, decode(An<std::string&>())).Times(0);
  EXPECT_CALL(decoder, decode()).Times(0);

  std::stringstream stream;

  stream >> decoder;
}

TEST(Decoder, decode_text) {
  LType value(TEST_VALUE_TEXT);
  MockDecoder decoder(value);

  EXPECT_CALL(decoder, decode(An<Array&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<bool&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<double&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<Hash&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<int&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<std::string&>())).Times(1);
  EXPECT_CALL(decoder, decode()).Times(0);

  std::stringstream stream;

  stream >> decoder;
}

TEST(Decoder, decode_void) {
  LType value;
  MockDecoder decoder(value);

  EXPECT_CALL(decoder, decode(An<Array&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<bool&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<double&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<Hash&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<int&>())).Times(0);
  EXPECT_CALL(decoder, decode(An<std::string&>())).Times(0);
  EXPECT_CALL(decoder, decode()).Times(1);

  std::stringstream stream;

  stream >> decoder;
}
