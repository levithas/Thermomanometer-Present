#ifndef WAITFORWARMSTATE_H
#define WAITFORWARMSTATE_H

#include "state.h"

class Context;

class WaitForWarmState : public State {
  private:
    const float MaxTemperature = 3.14159;
    
    uint8_t brightness = 0;
    bool brightnessUp = true;
    
  public:
    uint32_t handle(Context& context) override;
};

#endif
