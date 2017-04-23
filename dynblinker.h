#ifndef __DYN_Blinker__
#define __DYN_Blinker__

#include <Adafruit_NeoPixel.h>
#include <Arduino.h>

class dynblinker {

private:
  uint8_t pin;
  uint16_t NUM_PIXELS,
      startpixel,
      endpixel,
      blinkoncount,
      blinkoffcount,
      blinkinterval,
      blinkerdelayinterval,
      getoffset(),
      getrealpixel(uint16_t pixel);
  uint32_t color;
  unsigned long blinkpreviousMillis,
      blinkerpreviousMillis;
  bool blinkerdelay(),
      blinkerdelayed;



  Adafruit_NeoPixel strip;

  void  setpin(uint8_t pin),
      init();

public:
  dynblinker(uint8_t pin, uint16_t NUM_PIXELS); // Default initial, use all
                                                // pixel
  dynblinker(uint8_t pin, uint16_t startpixel,
             uint16_t endpixel); // use only defined pixel

  void begin(),
      setNUM_PIXELS(uint16_t NUM_PIXELS),
      setNUM_PIXELS(uint16_t startpixel, uint16_t endpixel),
      setstartpixel(uint16_t startpixel),
      setendpixel(uint16_t endpixel),
      setblinkinterval(uint16_t blinkinterval),
      setblinkerdelayinterval(uint16_t blinkdelayinterval),
      setPixel(uint16_t pixel, uint32_t color),
      blink(),
      blinkon(),
      blinkoff(),
      clear();
};

#endif
