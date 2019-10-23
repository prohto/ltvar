#include "tokenizer.h"
#include <stdexcept>
#include <string>

Tokenizer::Tokenizer(const char path[])
    : path_(path),
      current_position_(0),
      current_index_(0),
      current_tag_(""),
      current_type_(kVoid) {}

bool Tokenizer::hasNext() {
  if (current_position_ >= path_.length()) return false;
  size_t token_position;
  while ((token_position = path_.find_first_of(".[]", current_position_)) !=
         std::string::npos) {
    size_t tag_len = token_position - current_position_;
    char token = path_.at(token_position);
    if (token == ']') {
      throw std::invalid_argument("invalid path");
    } else if (token == '.') {
      if (tag_len == 0) throw std::invalid_argument("invalid path");
      current_tag_ =
          path_.substr(current_position_, token_position - current_position_);
      current_position_ = token_position + 1;
      if (current_position_ == path_.length())
        throw std::invalid_argument("invalid path");
      current_type_ = kTag;
      return true;
    } else if (token == '[') {
      if (tag_len > 0) {
        current_tag_ =
            path_.substr(current_position_, token_position - current_position_);
        current_position_ = token_position;
        current_type_ = kTag;
        return true;
      } else {
        token_position++;
        current_position_ = token_position;
        size_t end_bracket_position = path_.find(']', token_position);
        if (end_bracket_position == std::string::npos)
          throw std::invalid_argument("invalid path");
        char* stoped_at = nullptr;
        current_index_ = static_cast<size_t>(
            std::strtol(&path_.c_str()[token_position], &stoped_at, 10));
        if (&path_.c_str()[end_bracket_position] != stoped_at)
          throw std::invalid_argument("invalid path");
        current_position_ = end_bracket_position + 1;
        if (current_position_ < path_.length() &&
            path_.at(current_position_) == '.') {
          current_position_++;
          if (current_position_ == path_.length())
            throw std::invalid_argument("invalid path");
        }
        current_type_ = kIndex;
        return true;
      }
    }
  }
  if (current_position_ < path_.length()) {
    current_tag_ = path_.substr(current_position_);
    current_type_ = kTag;
    current_position_ = path_.length();
    return true;
  }
  return false;
}

Tokenizer::Types Tokenizer::getType() { return current_type_; }

size_t Tokenizer::getIndex() { return current_index_; }

std::string Tokenizer::getTag() { return current_tag_; }

size_t Tokenizer::stoppedAt() { return current_position_; }
