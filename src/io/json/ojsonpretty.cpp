#include "ojsonpretty.h"

using namespace Harmonix;

void OJsonPretty::encode(const Array& value) {
  (*o_stream_) << "[" << std::string(new_line_, '\n');
  lines_ += new_line_;
  level_++;
  size_t idx = 0;
  for (auto iter : value) {
    if (idx > 0) {
      (*o_stream_) << ',' << std::string(new_line_, '\n');
      lines_ += new_line_;
    }
    (*o_stream_) << std::string(tabs_ * level_, ' ');
    encodeValue(iter);
    idx++;
  }
  level_--;
  (*o_stream_) << std::string(new_line_, '\n')
               << std::string(tabs_ * level_, ' ') << "]";
  lines_ += new_line_;
}

void OJsonPretty::encode(const Hash& value) {
  (*o_stream_) << "{" << std::string(new_line_, '\n');
  lines_ += new_line_;
  level_++;
  size_t idx = 0;
  for (LTypeIterator iter = value.begin(); iter != value.end(); ++iter) {
    if (idx > 0) {
      (*o_stream_) << ',' << std::string(new_line_, '\n');
      lines_ += new_line_;
    }
    (*o_stream_) << std::string(tabs_ * level_, ' ');
    encodeValue(iter.first());
    (*o_stream_) << ":" << std::string(space_, ' ');
    encodeValue(iter.second());
    idx++;
  }
  level_--;
  (*o_stream_) << std::string(new_line_, '\n')
               << std::string(tabs_ * level_, ' ') << "}";
  lines_ += new_line_;
}
