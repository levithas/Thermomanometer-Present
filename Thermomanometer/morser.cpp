#include "morser.h"

void Morser::update() {
  if(repeats >= MAX_REPEATS)
    return;
  
  if(pause) {
    digitalWrite(LED_PIN, LOW);
    pausedits++;
    if(pausedits >= codeLengthMap[CODE::DIT])
    {
      pause = false;
    }
    return;
  }

  switch(message[currentLetter])
  {
    case LONG:
    case SHORT:
      digitalWrite(LED_PIN, HIGH);
      break;
    case NEXT:
    case WORD:
    case PAUSE:
      digitalWrite(LED_PIN, LOW);
      break;
    default:
      break;
  }

  step++;
  if(step >= codeLengthMap[message[currentLetter]])
  {
    currentLetter++;
    pause = true;
    step = 0;
  }

  if(currentLetter >= codeLength)
  {
    currentLetter = 0;
    repeats++;
  }
};
