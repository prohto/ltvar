#include "iterator.h"
#include "ltvar.h"
#include "io/io.h"
#include "string.h"


void Text::encode(Encoder& stream) const { stream.encode(this->value_); }
void Text::decode(Decoder& stream) { stream.decode(this->value_); }
