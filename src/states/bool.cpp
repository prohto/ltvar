#include "iterator.h"
#include "ltype.h"
#include "io/io.h"
#include "bool.h"

using namespace Harmonix;

void Bool::encode(Encoder& stream) const { stream.encode(this->value_); }
void Bool::decode(Decoder& stream) { stream.decode(this->value_); }
