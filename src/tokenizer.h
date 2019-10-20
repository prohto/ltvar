#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>

class Tokenizer {
 private:
  std::string path_;
  size_t current_position_;
  size_t current_index_;
  std::string current_tag_;

 public:
  explicit Tokenizer(const char*);
  bool hasNext();
  enum Types { kVoid, kTag, kIndex };
  Types getType();
  size_t getIndex();
  std::string getTag();
  size_t stoppedAt();

 private:
  Types current_type_;
};

#endif
