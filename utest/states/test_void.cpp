#include "ltvar.h"
#include "utest.h"

using ::testing::An;
using ::testing::Matcher;
using ::testing::TypedEq;

TEST(VoidValue, exception) {
  invalid_cast excep;
  ASSERT_EQ(std::string("invalid_cast"), excep.what());
}

TEST(VoidValue, is) {
  Void value;

  ASSERT_FALSE(value.is_array());
  ASSERT_FALSE(value.is_bool());
  ASSERT_FALSE(value.is_double());
  ASSERT_FALSE(value.is_hash());
  ASSERT_FALSE(value.is_integer());
  ASSERT_FALSE(value.is_text());
  ASSERT_TRUE(value.is_void());
}

TEST(VoidValue, get) {
  Void value;
  ASSERT_THROW(value.get_bool(), invalid_cast);
  ASSERT_THROW(value.get_double(), invalid_cast);
  ASSERT_THROW(value.get_int(), invalid_cast);
  ASSERT_EQ(value.get_text(), "<void>");
  ASSERT_THROW(value.get("tag"), invalid_cast);
  ASSERT_THROW(value["tag"], invalid_cast);
  ASSERT_THROW(value.get((size_t)0), invalid_cast);
  ASSERT_THROW(value[(size_t)0], invalid_cast);
  ASSERT_THROW(value.get(nullptr), invalid_cast);
}

TEST(VoidValue, get_const) {
  const Void value;
  ASSERT_THROW(value.get("tag"), invalid_cast);
  ASSERT_THROW(value.get((size_t)0), invalid_cast);
}

TEST(VoidValue, set) {
  Void value;
  ASSERT_THROW(value.set("tag", LTVar()), invalid_cast);
  ASSERT_THROW(value.set((size_t)0, LTVar()), invalid_cast);
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
  LTVarHash hash_value;
  LTVarArray array_value;
  ASSERT_FALSE(lhs_value.equal(hash_value));
  ASSERT_FALSE(lhs_value.equal(array_value));
}

TEST(VoidValue, iteratore) {
  Void value;
  ASSERT_THROW(value.begin(), invalid_cast);
  ASSERT_THROW(value.end(), invalid_cast);
  ASSERT_THROW(value.find("void"), invalid_cast);
}
