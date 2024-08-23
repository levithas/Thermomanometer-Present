#include <map>


#define LED_PIN 15


enum CODE {
  DIT, LONG, SHORT, NEXT, WORD, PAUSE
};

std::map<CODE, uint8_t> code{
  {CODE::DIT, 3},
  {CODE::LONG, 9},
  {CODE::SHORT, 3},
  {CODE::NEXT, 9},
  {CODE::WORD, 21},
  {CODE::PAUSE, 60}
};

class Morser {

  const static uint8_t codeLength = 55;
  CODE message[codeLength] = {
    LONG, LONG, NEXT, SHORT, LONG, NEXT, LONG, SHORT, LONG, SHORT, NEXT, SHORT, SHORT, SHORT, SHORT
  , WORD, LONG , LONG, NEXT, SHORT, SHORT, NEXT, LONG, SHORT, LONG, SHORT, NEXT, SHORT, SHORT, SHORT, SHORT
  , WORD, SHORT, NEXT, SHORT, SHORT, NEXT, SHORT, SHORT, SHORT, NEXT, LONG, SHORT, LONG, NEXT, SHORT, LONG, NEXT, SHORT, LONG, SHORT, SHORT, NEXT, LONG, PAUSE
  };
  
  uint8_t currentLetter = 0;
  uint8_t step = 0;
  bool pause = false;
  uint8_t pausedits = 0;

  const uint8_t MAX_REPEATS = 5;
  uint8_t repeats = 0;

  public:
    Morser() {
      pinMode(LED_PIN, OUTPUT);
    }

    void update() {
      if(repeats >= MAX_REPEATS)
        return;
      
      if(pause) {
        digitalWrite(LED_PIN, LOW);
        pausedits++;
        if(pausedits >= code[CODE::DIT])
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
      if(step >= code[message[currentLetter]])
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
    }
};