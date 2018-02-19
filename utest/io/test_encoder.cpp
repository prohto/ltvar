#include "test_data.h"
#include "utest.h"

#include "io/mockencoder.h"

using ::testing::An;

TEST(Encoder, encode_array) {
  LTVar value(test_array);
  MockEncoder encoder(value);

  EXPECT_CALL(encoder, encode(An<const Array&>())).Times(1);
  EXPECT_CALL(encoder, encode(An<const bool&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const double&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const Hash&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const int&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const std::string&>())).Times(0);
  EXPECT_CALL(encoder, encode()).Times(0);

  std::stringstream stream;

  stream << encoder;
}

TEST(Encoder, encode_bool) {
  LTVar value(TEST_VALUE_BOOL_TRUE);
  MockEncoder encoder(value);

  EXPECT_CALL(encoder, encode(An<const Array&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const bool&>())).Times(1);
  EXPECT_CALL(encoder, encode(An<const double&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const Hash&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const int&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const std::string&>())).Times(0);
  EXPECT_CALL(encoder, encode()).Times(0);

  std::stringstream stream;

  stream << encoder;
}

TEST(Encoder, encode_double) {
  LTVar value(TEST_VALUE_DOUBLE);
  MockEncoder encoder(value);

  EXPECT_CALL(encoder, encode(An<const Array&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const bool&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const double&>())).Times(1);
  EXPECT_CALL(encoder, encode(An<const Hash&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const int&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const std::string&>())).Times(0);
  EXPECT_CALL(encoder, encode()).Times(0);

  std::stringstream stream;

  stream << encoder;
}

TEST(Encoder, encode_hash) {
  LTVar value(test_hash);
  MockEncoder encoder(value);

  EXPECT_CALL(encoder, encode(An<const Array&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const bool&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const double&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const Hash&>())).Times(1);
  EXPECT_CALL(encoder, encode(An<const int&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const std::string&>())).Times(0);
  EXPECT_CALL(encoder, encode()).Times(0);

  std::stringstream stream;

  stream << encoder;
}

TEST(Encoder, encode_integer) {
  LTVar value(TEST_VALUE_INTEGER);
  MockEncoder encoder(value);

  EXPECT_CALL(encoder, encode(An<const Array&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const bool&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const double&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const Hash&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const int&>())).Times(1);
  EXPECT_CALL(encoder, encode(An<const std::string&>())).Times(0);
  EXPECT_CALL(encoder, encode()).Times(0);

  std::stringstream stream;

  stream << encoder;
}

TEST(Encoder, encode_text) {
  LTVar value(TEST_VALUE_TEXT);
  MockEncoder encoder(value);

  EXPECT_CALL(encoder, encode(An<const Array&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const bool&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const double&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const Hash&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const int&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const std::string&>())).Times(1);
  EXPECT_CALL(encoder, encode()).Times(0);

  std::stringstream stream;

  stream << encoder;
}

TEST(Encoder, encode_void) {
  LTVar value;
  MockEncoder encoder(value);

  EXPECT_CALL(encoder, encode(An<const Array&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const bool&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const double&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const Hash&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const int&>())).Times(0);
  EXPECT_CALL(encoder, encode(An<const std::string&>())).Times(0);
  EXPECT_CALL(encoder, encode()).Times(1);

  std::stringstream stream;

  stream << encoder;
}
