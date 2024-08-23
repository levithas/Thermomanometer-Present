#include "data_visualizer.h"
#include "morser.h"

DataVisualizer *dv;
Morser *morser;

bool showMessage = false;
uint8_t messagePosition = 0;
std::string message = "Hallo Du";


void setup() {
  // put your setup code here, to run once:
  dv = new DataVisualizer();
  morser = new Morser();
}

void loop() {
  if(dv->getTemperature() < 15.0)
  {
    showMessage = true;
    messagePosition = 0;
  }

  if(showMessage)
  {
    dv->showHexMessage(message, messagePosition);
    messagePosition++;
    if(messagePosition >= message.size())
    {
      showMessage = false;
    }
    delay(1900);
  }
  else
  {
    dv->visualize();
    morser->update();
  }

  delay(100);
}
