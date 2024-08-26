#include "context.h"
#include "message_state.h"
#include "press_temp_state.h"

uint32_t MessageState::handle(Context& context) 
{
  // HEX Message Display
  context.getDV().showBinaryMessage(message, messagePosition);
  messagePosition++;

  if(messagePosition >= message.size())
  {
    if(messageRepeats >= MaxMessageRepeats)
    {
      context.setState(new PressTempState());
      return 0;
    }
    messageRepeats++;
    messagePosition = 0;
  }

  return 4000;
}
