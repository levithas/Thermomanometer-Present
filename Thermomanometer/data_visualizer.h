#ifndef DATA_VISUALIZER_H
#define DATA_VISUALIZER_H

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

  void drawLEDScala(uint8_t startLED, uint8_t ledCount, bool clockwise, float minValue, float maxValue, float value, uint32_t startColor, uint32_t endColor);

  static float lerp(float startValue, float endValue, float pct)
  {
      return (startValue + (endValue - startValue) * pct);
  }

  uint32_t colorLerp(uint32_t c1, uint32_t c2, float value);

  public:
    DataVisualizer();

    float getPressure() { return barometer.bmp085GetPressure(barometer.bmp085ReadUP()); }
    float getTemperature() { return barometer.bmp085GetTemperature(barometer.bmp085ReadUT()); }
    
    void visualize();
    void showBinaryMessage(const std::string &message, const uint8_t pos);
    void solidColor(uint8_t brightness);
};

#endif
