#include "iterator.h"
#include "ltvar.h"
#include "io/io.h"
#include "integer.h"


void Integer::encode(Encoder& stream) const { stream.encode(this->value_); }
void Integer::decode(Decoder& stream) { stream.decode(this->value_); }
