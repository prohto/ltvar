#include "iterator.h"
#include "ltvar.h"
#include "io/io.h"
#include "double.h"


void Double::encode(Encoder& stream) const { stream.encode(this->value_); }
void Double::decode(Decoder& stream) { stream.decode(this->value_); }
