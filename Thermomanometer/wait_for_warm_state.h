#ifndef WAITFORWARMSTATE_H
#define WAITFORWARMSTATE_H

#include "state.h"

class Context;

class WaitForWarmState : public State {
  private:
    const float thresholdTemperature;
    
    State* nextState;

    uint8_t brightness = 0;
    bool brightnessUp = true;
    
  public:
    WaitForWarmState(State& nextState, const float thresholdTemperature);
    uint32_t handle(Context& context) override;
};

#endif
