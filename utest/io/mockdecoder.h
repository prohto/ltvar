#ifndef MOCKDESERIALIZER_H
#define MOCKDESERIALIZER_H

#include "gmock/gmock.h"

#include "io/decoder.h"
#include "ltype.h"

using ::testing::An;
using ::testing::Invoke;

namespace Harmonix {

class MockDecoder : public Decoder {
 private:
  std::stringbuf dummybuffer;

 public:
  MockDecoder(LType& property) : Decoder(property) {
    EXPECT_CALL(*this, decode(An<Array&>())).Times(0);
    EXPECT_CALL(*this, decode(An<bool&>())).Times(0);
    EXPECT_CALL(*this, decode(An<double&>())).Times(0);
    EXPECT_CALL(*this, decode(An<Hash&>())).Times(0);
    EXPECT_CALL(*this, decode(An<int&>())).Times(0);
    EXPECT_CALL(*this, decode(An<std::string&>())).Times(0);
    EXPECT_CALL(*this, decode()).Times(0);
  }
  void decode(LType& value) { deserializeInto(value); }
  MOCK_METHOD1(decode, void(Array&));
  MOCK_METHOD1(decode, void(bool&));
  MOCK_METHOD1(decode, void(double&));
  MOCK_METHOD1(decode, void(Hash&));
  MOCK_METHOD1(decode, void(int&));
  MOCK_METHOD1(decode, void(std::string&));
  MOCK_METHOD0(decode, void());
};
}  // namespace Harmonix

#endif  // MOCKDESERIALIZER_H
