#include "ltype.h"
#include "utest.h"

using namespace Harmonix;
using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

TEST(VoidValue, is) {
  Void value;

  ASSERT_FALSE(value.is_array());
  ASSERT_FALSE(value.is_bool());
  ASSERT_FALSE(value.is_double());
  ASSERT_FALSE(value.is_hash());
  ASSERT_FALSE(value.is_integer());
  ASSERT_FALSE(value.is_string());
  ASSERT_TRUE(value.is_void());
}

TEST(VoidValue, get) {
  Void value;
  ASSERT_THROW(value.get_bool(), std::invalid_argument);
  ASSERT_THROW(value.get_double(), std::invalid_argument);
  ASSERT_THROW(value.get_int(), std::invalid_argument);
  ASSERT_EQ(value.get_string(), "<void>");
  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value["tag"], std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
  ASSERT_THROW(value[(size_t)0], std::invalid_argument);
  ASSERT_THROW(value.get(nullptr), std::invalid_argument);
}

TEST(VoidValue, get_const) {
  const Void value;
  ASSERT_THROW(value.get("tag"), std::invalid_argument);
  ASSERT_THROW(value.get((size_t)0), std::invalid_argument);
}

TEST(VoidValue, set) {
  Void value;
  ASSERT_THROW(value.set("tag", LType()), std::invalid_argument);
  ASSERT_THROW(value.set((size_t)0, LType()), std::invalid_argument);
}

TEST(VoidValue, copy) {
  Void value;
  std::unique_ptr<Void> ptr(value.copy());
  ASSERT_EQ(ptr->is_void(), true);
}

TEST(VoidValue, differ) {
  Void lhs_value;
  Integer rhs_value;
  ASSERT_NE(lhs_value, rhs_value);
  LTypeHash hash_value;
  LTypeArray array_value;
  ASSERT_FALSE(lhs_value.equal(hash_value));
  ASSERT_FALSE(lhs_value.equal(array_value));
}

TEST(VoidValue, iteratore) {
  Void value;
  ASSERT_THROW(value.begin(), std::invalid_argument);
  ASSERT_THROW(value.end(), std::invalid_argument);
}
