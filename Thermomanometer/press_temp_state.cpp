#include "context.h"
#include "press_temp_state.h"
#include "wait_for_warm_state.h"

uint32_t PressTempState::handle(Context& context) 
{
  // Normal Temperature and Pressure Display
  if(context.getDV().getTemperature() < MinTemperature)
  {
    context.setState(new WaitForWarmState());
    return 0;
  }

  context.getDV().visualize();
  context.getMorser().update();

  return 100;
}
