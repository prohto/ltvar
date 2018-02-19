#include "iterator.h"
#include "ltvar.h"
#include "io/io.h"
#include "void.h"


void Void::encode(Encoder& output) const { output.encode(); }
void Void::decode(Decoder& input) { input.decode(); }
