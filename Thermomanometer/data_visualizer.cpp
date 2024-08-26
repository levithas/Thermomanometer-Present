#include "data_visualizer.h"

DataVisualizer::DataVisualizer() : barometer(), strip(Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800))
{
  barometer.init();

  strip.begin();
  strip.setBrightness(50);
  strip.show(); // Initialize all pixels to 'off'

  // Debugging
  Serial.begin(9600);
  while(!Serial);
}

uint32_t DataVisualizer::colorLerp(uint32_t c1, uint32_t c2, float value) {
  uint8_t r1 = (c1 >> 16) & 255;
  uint8_t g1 = (c1 >> 8) & 255;
  uint8_t b1 = c1 & 255;
  uint8_t r2 = (c2 >> 16) & 255;
  uint8_t g2 = (c2 >> 8) & 255;
  uint8_t b2 = c2 & 255;

  return strip.Color(lerp(r1, r2, value),lerp(g1, g2, value),lerp(b1, b2, value));
}

void DataVisualizer::drawLEDScala(uint8_t startLED, uint8_t ledCount, bool clockwise, float minValue, float maxValue, float value, uint32_t startColor, uint32_t endColor) 
{        
  for(uint8_t led = startLED; led < startLED+ledCount;led++)
  {
    float perc = clockwise ? (led-startLED)/(float)ledCount : 1.0 - (led-startLED)/(float)ledCount;
    uint32_t color = colorLerp(startColor, endColor, perc);
    float ledValue = lerp(minValue, maxValue, perc);

    if(ledValue < value)
    {
      strip.setPixelColor(led, color);
    }
    else
    {
      strip.setPixelColor(led, strip.Color(0,0,0));
    }
  }
}

void DataVisualizer::visualize() 
{
  float temperature = getTemperature();
  float pressure = getPressure();
  
  float minTemp, maxTemp;
  float minPress, maxPress;
  uint32_t minColorTemp, maxColorTemp, minColorPress, maxColorPress;

  if(temperature < 10.5)
  {
    minTemp = 0.5;// °C
    maxTemp = 10.5;// °C
    minColorTemp = strip.Color(255,255,255);
    maxColorTemp = strip.Color(128,255,255);
  }
  else if(temperature < 20.5)
  {
    minTemp = 10.5;// °C
    maxTemp = 20.5;// °C
    minColorTemp = strip.Color(128,255,255);
    maxColorTemp = strip.Color(0,255,0);
  }
  else if(temperature < 30.5)
  {
    minTemp = 20.5;// °C
    maxTemp = 30.5;// °C
    minColorTemp = strip.Color(0,255,0);
    maxColorTemp = strip.Color(255,160,0);
  }
  else
  {
    minTemp = 30.5;// °C
    maxTemp = 40.5;// °C
    minColorTemp = strip.Color(255,160,0);
    maxColorTemp = strip.Color(255,0,0);
  }

  minPress = 95000.0; //Pa
  maxPress = 105000.0; //Pa
  minColorPress = strip.Color(60,0,255);
  maxColorPress = strip.Color(255,60,200);

  drawLEDScala(0, 10, true, minTemp, maxTemp, temperature, minColorTemp, maxColorTemp);
  drawLEDScala(10, 10, false, minPress, maxPress, pressure, minColorPress, maxColorPress);
  strip.show();

  // Debugging
  Serial.print("Temperature: ");
  Serial.print(temperature, 2);
  Serial.println(" °C");
  Serial.print("Pressure: ");
  Serial.print(pressure, 0);
  Serial.println(" Pa");
}

void DataVisualizer::showBinaryMessage(const std::string &message, const uint8_t pos) {
  for(uint32_t i = 0;i<strip.numPixels(); i++)
  {
    uint32_t color = 0;
    if(i == 0)
    {
      color = strip.Color(0,255,255);
    }
    else if(i < 9)
    {
      // Encoding of the message
      if((message[pos] >> (8-i)) & 1)
      {
        color = strip.Color(255,0,0);
      }
    }
    else if(i == 9)
    {
      color = strip.Color(0,255,255);
    }
    else
    {
      // Showing the position of the current character in the message
      if(pos == 19 - i)
      {
        color = strip.Color(0,0,255);
      }
    }
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void DataVisualizer::solidColor(uint8_t brightness){
  for(uint32_t i = 0;i<strip.numPixels();i++)
  {
    strip.setPixelColor(i, strip.Color(brightness,brightness,0));
  }
  strip.show();
}
