#include "test_data.h"
#include "utest.h"

#include "io/mockencoder.h"

using namespace Harmonix;
using ::testing::An;

TEST(Encoder, encode_array) {
  LType value(test_array);
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
  LType value(TEST_VALUE_BOOL_TRUE);
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
  LType value(TEST_VALUE_DOUBLE);
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
  LType value(test_hash);
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
  LType value(TEST_VALUE_INTEGER);
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
  LType value(TEST_VALUE_TEXT);
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
  LType value;
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
