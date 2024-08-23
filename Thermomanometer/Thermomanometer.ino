#include "data_visualizer.h"
#include "morser.h"

DataVisualizer *dv;
Morser *morser;

enum STATE {
  PRESSTEMP, MESSAGE, WAITFORWARM
};


STATE currentState = STATE::PRESSTEMP;


// Message State
uint8_t messageRepeats = 0;
const uint8_t MaxMessageRepeats = 3;
uint8_t messagePosition = 0;
std::string message = "Hallo Du";

// WaitForWarm Sate
uint8_t brightness = 0;
bool brightnessUp = true;


uint32_t updateWaitForWarm() {
  float temperature = dv->getTemperature();
  
  if(temperature > 3.14159) {
    currentState = STATE::MESSAGE;
    messagePosition = 0;
    messageRepeats = 0;
  }
  else
  {
    brightness += brightnessUp ? 10 : -10;
    if(brightnessUp && brightness > 250)
      brightnessUp = false;
    if(!brightnessUp && brightness < 10)
      brightnessUp = true;

    dv->solidColor(brightness);
  }

  return 100;
}

uint32_t updateMessage() {
  // HEX Message Display
  dv->showHexMessage(message, messagePosition);
  messagePosition++;

  if(messagePosition >= message.size())
  {
    if(messageRepeats >= MaxMessageRepeats)
    {
      currentState = STATE::PRESSTEMP;
    }
    messageRepeats++;
    messagePosition = 0;
  }

  return 4000;
}

uint32_t updatePressureTemperatureDisplay() {
  // Normal Temperature and Pressure Display

  if(dv->getTemperature() < 1.0)
  {
    currentState = STATE::WAITFORWARM;
    brightnessUp = true;
    brightness = 0;
  }

  dv->visualize();
  morser->update();

  return 100;
}


void setup() {
  // put your setup code here, to run once:
  dv = new DataVisualizer();
  morser = new Morser();
}

void loop() {
  uint32_t time;
  switch(currentState)
  {
    case STATE::PRESSTEMP:
      time = updatePressureTemperatureDisplay();
      break;
    case STATE::MESSAGE:
      time = updateMessage();
      break;
    case STATE::WAITFORWARM:
      time = updateWaitForWarm();
      break;
    default:
      break;
  }

  delay(time);
}