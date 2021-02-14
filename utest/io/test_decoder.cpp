#include "io/mockdecoder.h"
#include "test_data.h"
#include "utest.h"

using ::testing::An;

TEST(Decoder, decode_array) {
  LTVar value(test_array);
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
  LTVar value(TEST_VALUE_BOOL_TRUE);
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
  LTVar value(TEST_VALUE_DOUBLE);
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
  LTVar value(test_hash);
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
  LTVar value(TEST_VALUE_INTEGER);
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
  LTVar value(TEST_VALUE_TEXT);
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
  LTVar value;
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

TEST(Decoder, array_not_implemented) {
  LTVar value(test_array);
  NullDecoder decoder(value);
  ASSERT_THROW(decoder.decode(value), std::invalid_argument);
}

TEST(Decoder, decode_bool_not_implemented) {
  LTVar value(TEST_VALUE_BOOL_TRUE);
  NullDecoder decoder(value);
  ASSERT_THROW(decoder.decode(value), std::invalid_argument);
}

TEST(Decoder, decode_double_not_implemented) {
  LTVar value(TEST_VALUE_DOUBLE);
  NullDecoder decoder(value);
  ASSERT_THROW(decoder.decode(value), std::invalid_argument);
}

TEST(Decoder, decode_hash_not_implemented) {
  LTVar value(test_hash);
  NullDecoder decoder(value);
  ASSERT_THROW(decoder.decode(value), std::invalid_argument);
}

TEST(Decoder, decode_integer_not_implemented) {
  LTVar value(TEST_VALUE_INTEGER);
  NullDecoder decoder(value);
  ASSERT_THROW(decoder.decode(value), std::invalid_argument);
}

TEST(Decoder, decode_text_not_implemented) {
  LTVar value(TEST_VALUE_TEXT);
  NullDecoder decoder(value);
  ASSERT_THROW(decoder.decode(value), std::invalid_argument);
}

TEST(Decoder, decode_void_not_implemented) {
  LTVar value;
  NullDecoder decoder(value);
  ASSERT_THROW(decoder.decode(value), std::invalid_argument);
}
