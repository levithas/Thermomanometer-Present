#include <Adafruit_NeoPixel.h>
#include "BMP085.h"
#include <Wire.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#include <string>


#define PIN 2

class DataVisualizer
{
  BMP085 barometer;
  Adafruit_NeoPixel strip;

  void drawLEDScala(uint8_t startLED, uint8_t ledCount, bool clockwise, float minValue, float maxValue, float value, uint32_t startColor, uint32_t endColor) {        
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

  static float lerp(float start_value, float end_value, float pct)
  {
      return (start_value + (end_value - start_value) * pct);
  }

  uint32_t colorLerp(uint32_t c1, uint32_t c2, float value) {
    uint8_t r1 = (c1 >> 16) & 255;
    uint8_t g1 = (c1 >> 8) & 255;
    uint8_t b1 = c1 & 255;
    uint8_t r2 = (c2 >> 16) & 255;
    uint8_t g2 = (c2 >> 8) & 255;
    uint8_t b2 = c2 & 255;

    return strip.Color(lerp(r1, r2, value),lerp(g1, g2, value),lerp(b1, b2, value));
  }

  public:
    DataVisualizer() : barometer(), strip(Adafruit_NeoPixel(20, PIN, NEO_GRB + NEO_KHZ800))
    {
      barometer.init();

      strip.begin();
      strip.setBrightness(50);
      strip.show(); // Initialize all pixels to 'off'

      // Debugging
      Serial.begin(9600);
      while(!Serial);
    }
    float getPressure() { return barometer.bmp085GetPressure(barometer.bmp085ReadUP()); }
    float getTemperature() { return barometer.bmp085GetTemperature(barometer.bmp085ReadUT()); }
    void visualize() 
    {
      float temperature = getTemperature();
      float pressure = getPressure();
      
      drawLEDScala(0, 10, true, 15.0, 35.0, temperature, strip.Color(0,0,255), strip.Color(255,0,0));
      drawLEDScala(10, 10, false, 95000.0, 105000.0, pressure, strip.Color(0,255,255), strip.Color(255,255,0));
      strip.show();

      // Debugging
      Serial.print("Temperature: ");
      Serial.print(temperature, 2);
      Serial.println(" °C");
      Serial.print("Pressure: ");
      Serial.print(pressure, 0);
      Serial.println(" Pa");
    }
    void showHexMessage(const std::string &message, const uint8_t pos) {
      for(uint32_t i = 0;i<strip.numPixels(); i++)
      {
        strip.setPixelColor(i, strip.Color(255,255,0));
      }
      strip.show();
    }
};