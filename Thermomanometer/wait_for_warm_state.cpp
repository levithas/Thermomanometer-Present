#include "context.h"
#include "message_state.h"
#include "wait_for_warm_state.h"

uint32_t WaitForWarmState::handle(Context& context) 
    {
      float temperature = context.getDV().getTemperature();
  
      if(temperature > MaxTemperature) {
        context.setState(new MessageState());
        return 0;
      }
      else
      {
        brightness += brightnessUp ? 10 : -10;
        if(brightnessUp && brightness > 250)
          brightnessUp = false;
        if(!brightnessUp && brightness < 10)
          brightnessUp = true;
    
        context.getDV().solidColor(brightness);
      }

      return 100;
    }
