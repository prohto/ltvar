#include "iterator.h"
#include "ltvar.h"
#include "io/io.h"
#include "bool.h"


void Bool::encode(Encoder& stream) const { stream.encode(this->value_); }
void Bool::decode(Decoder& stream) { stream.decode(this->value_); }
