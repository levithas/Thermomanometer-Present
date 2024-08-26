#include "context.h"
#include "press_temp_state.h"
#include "wait_for_warm_state.h"
#include "message_state.h"

uint32_t PressTempState::handle(Context& context) 
{
  // Normal Temperature and Pressure Display
  if(context.getDV().getTemperature() < MinTemperature)
  {
    context.setState(new WaitForWarmState(*(new MessageState("Donut")), MinTemperature+3.14159));
    return 0;
  } 
  else if(context.getDV().getPressure() > 105000.00)
  {
    context.setState(new MessageState("Waffeln"));
    return 0;
  }

  if (--superSecretClueTimer == 0)
  {
    context.setState(new MessageState("Pfannkuchen"));
    return 0;
  }

  context.getDV().visualize();
  context.getMorser().update();

  return 100;
}
