#ifndef MESSAGESTATE_H
#define MESSAGESTATE_H

#include <string>
#include "state.h"

class Context;

class MessageState : public State {
  private:
    const uint8_t MaxMessageRepeats = 3;
    const std::string message = "Hallo Du";

    uint8_t messageRepeats = 0;
    uint8_t messagePosition = 0;

  public:
    uint32_t handle(Context& context) override;
};

#endif
