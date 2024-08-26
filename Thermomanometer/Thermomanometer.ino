#include "context.h"

Context* context;

void setup() {
  // put your setup code here, to run once:
  context = new Context();
}

void loop() {
  context->update();
}
