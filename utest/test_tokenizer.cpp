#include "tokenizer.h"
#include "utest.h"

TEST(Tokenizer, hash_first_level) {
  Tokenizer tk("level1");

  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level1"), tk.getTag());
  ASSERT_FALSE(tk.hasNext());
}

TEST(Tokenizer, hash_second_level) {
  Tokenizer tk("level1.level2");

  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level1"), tk.getTag());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level2"), tk.getTag());
  ASSERT_FALSE(tk.hasNext());
}

TEST(Tokenizer, hash_third_level) {
  Tokenizer tk("level1.level2.level3");

  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level1"), tk.getTag());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level2"), tk.getTag());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level3"), tk.getTag());
  ASSERT_FALSE(tk.hasNext());
}

TEST(Tokenizer, array_first_level) {
  Tokenizer tk("[1]");

  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(1, tk.getIndex());
  ASSERT_FALSE(tk.hasNext());
}

TEST(Tokenizer, array_second_level) {
  Tokenizer tk("[1][2]");

  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(1, tk.getIndex());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(2, tk.getIndex());
  ASSERT_FALSE(tk.hasNext());
}

TEST(Tokenizer, array_third_level) {
  Tokenizer tk("[1][2][3]");

  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(1, tk.getIndex());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(2, tk.getIndex());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(3, tk.getIndex());
  ASSERT_FALSE(tk.hasNext());
}

TEST(Tokenizer, mixed_hash_start) {
  Tokenizer tk("level1[3].level3");

  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level1"), tk.getTag());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(3, tk.getIndex());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level3"), tk.getTag());
  ASSERT_FALSE(tk.hasNext());
}

TEST(Tokenizer, mixed_array_start) {
  Tokenizer tk("[3].level2[5]");

  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(3, tk.getIndex());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kTag, tk.getType());
  ASSERT_EQ(std::string("level2"), tk.getTag());
  ASSERT_TRUE(tk.hasNext());
  ASSERT_EQ(Tokenizer::kIndex, tk.getType());
  ASSERT_EQ(5, tk.getIndex());
  ASSERT_FALSE(tk.hasNext());
}

TEST(Tokenizer, dot_start) {
  Tokenizer tk(".level1");

  ASSERT_THROW(tk.hasNext(), std::invalid_argument);
  ASSERT_EQ(0, tk.stoppedAt());
}

TEST(Tokenizer, dots_together_after_tag) {
  Tokenizer tk("level1..level2");

  tk.hasNext();
  ASSERT_THROW(tk.hasNext(), std::invalid_argument);
  ASSERT_EQ(7, tk.stoppedAt());
}

TEST(Tokenizer, dots_together_after_index) {
  Tokenizer tk("[1]..");

  tk.hasNext();
  ASSERT_THROW(tk.hasNext(), std::invalid_argument);
  ASSERT_EQ(4, tk.stoppedAt());
}

TEST(Tokenizer, dot_end_after_tag) {
  Tokenizer tk("level1.");

  ASSERT_THROW(tk.hasNext(), std::invalid_argument);
  ASSERT_EQ(7, tk.stoppedAt());
}

TEST(Tokenizer, dot_end_after_index) {
  Tokenizer tk("[1].");

  ASSERT_THROW(tk.hasNext(), std::invalid_argument);
  ASSERT_EQ(4, tk.stoppedAt());
}

TEST(Tokenizer, index_invalid_int) {
  Tokenizer tk("[aaa]");

  ASSERT_THROW(tk.hasNext(), std::invalid_argument);
  ASSERT_EQ(1, tk.stoppedAt());
}

TEST(Tokenizer, index_missing_open_bracket) {
  Tokenizer tk("1]");

  ASSERT_THROW(tk.hasNext(), std::invalid_argument);
  ASSERT_EQ(size_t(0), tk.stoppedAt());
}

TEST(Tokenizer, index_missing_close_bracket) {
  Tokenizer tk("[1");

  ASSERT_THROW(tk.hasNext(), std::invalid_argument);
  ASSERT_EQ(1, tk.stoppedAt());
}
