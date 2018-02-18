#ifndef MOCKSERIALIZER_H
#define MOCKSERIALIZER_H

#include "gmock/gmock.h"

#include "ltype.h"
#include "io/encoder.h"

using ::testing::An;
using ::testing::Invoke;

namespace Harmonix {

class MockEncoder : public Encoder {
 public:
  MockEncoder(const LType& property) : Encoder(property) {
    EXPECT_CALL(*this, encode(An<const Array&>())).Times(0);
    EXPECT_CALL(*this, encode(An<const bool&>())).Times(0);
    EXPECT_CALL(*this, encode(An<const double&>())).Times(0);
    EXPECT_CALL(*this, encode(An<const Hash&>())).Times(0);
    EXPECT_CALL(*this, encode(An<const int&>())).Times(0);
    EXPECT_CALL(*this, encode(An<const std::string&>())).Times(0);
    EXPECT_CALL(*this, encode()).Times(0);
  }
  void encode(const LType& value) { serializeFrom(value); }
  MOCK_METHOD1(encode, void(const Array&));
  MOCK_METHOD1(encode, void(const bool&));
  MOCK_METHOD1(encode, void(const double&));
  MOCK_METHOD1(encode, void(const Hash&));
  MOCK_METHOD1(encode, void(const int&));
  MOCK_METHOD1(encode, void(const std::string&));
  MOCK_METHOD0(encode, void());
};
}  // namespace Harmonix

#endif  // MOCKSERIALIZER_H
