#ifndef PRESSTEMPSTATE_H
#define PRESSTEMPSTATE_H

#include "state.h"

class Context;

class PressTempState : public State {
  private:
    const float MinTemperature = 1.0;
  public:
    uint32_t handle(Context& context) override;
};

#endif
