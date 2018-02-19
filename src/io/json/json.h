#ifndef JSON_H
#define JSON_H

#include <memory.h>
#include <stack>
#include <iostream>
#include "io/decoder.h"

#include "ltvar.h"


class JsonState;

#define YYSTYPE int
#define YY_EXTRA_TYPE JsonState *

int json_lex(YYSTYPE *, void *);
int json_lex_init(void **);
int json_lex_destroy(void *);
void json_set_extra(YY_EXTRA_TYPE, void *);
int json_parse(YY_EXTRA_TYPE, void *);
void json_error(YY_EXTRA_TYPE, void *, char *);
int32_t json_lineno_get(void *scanner);

using elements_stack_t = std::stack<LTVar>;

class JsonState {
  elements_stack_t stack_;
  std::istream &istream_;
  bool failed_;
  void *yyscanner_;

 public:
  JsonState(std::istream &istream) : istream_(istream), failed_(false) {
    json_lex_init(&yyscanner_);
    json_set_extra(this, yyscanner_);
  }
  ~JsonState() { json_lex_destroy(yyscanner_); }
  void push(LTVar value) { stack_.push(value); }
  LTVar &top() {
    if (stack_.size() == 0) throw std::invalid_argument("json error");
    return stack_.top();
  }
  LTVar pop() {
    LTVar rtn = std::move(stack_.top());
    stack_.pop();
    return rtn;
  }
  size_t readBuffer(char buffer[], size_t max_read) {
    istream_.read(buffer, static_cast<long>(max_read));
    return istream_.gcount();
  }
  void setFailed() { failed_ = true; }
  bool hasFailed() { return failed_; }
  bool deserialize() {
    json_parse(this, yyscanner_);
    return failed_;
  }
  int32_t getCurrentLine() { return json_lineno_get(yyscanner_); }
  static void unescape(char buffer[]) {
    size_t idx = 0;
    for (size_t curr = 0; curr < strlen(buffer); curr++) {
      char c = buffer[curr];
      if (c == '\\') {
        switch (buffer[curr + 1]) {
          case '"':
            buffer[idx] = '"';
            break;
          case '\\':
            buffer[idx] = '\\';
            break;
          case '/':
            buffer[idx] = '/';
            break;
          case 'b':
            buffer[idx] = '\b';
            break;
          case 'f':
            buffer[idx] = '\f';
            break;
          case 'n':
            buffer[idx] = '\n';
            break;
          case 'r':
            buffer[idx] = '\r';
            break;
          case 't':
            buffer[idx] = '\t';
            break;
          case 'u':
            buffer[idx] = '\\';
            idx++;
            buffer[idx] = 'u';
            break;
        }
        curr++;
        idx++;
      } else {
        buffer[idx] = c;
        idx++;
      }
    }
    buffer[idx] = 0;
  }
};

#endif  // JSON_H
