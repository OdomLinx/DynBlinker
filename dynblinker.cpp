#include "dynblinker.h"

void dynblinker::init() {
  this->blinkoncount = 0;
  this->blinkoffcount = 0;
  this->blinkpreviousMillis = 0;
  this->blinkerpreviousMillis = 0;
  this->blinkerdelayinterval = 1000;
  this->blinkerdelayed = false;
  setblinkinterval(200 / this->NUM_PIXELS);
}
dynblinker::dynblinker(uint8_t pin, uint16_t NUM_PIXELS) {
  setpin(pin);
  setNUM_PIXELS(NUM_PIXELS);
  setstartpixel(0);
  setendpixel(NUM_PIXELS - 1);
  this->strip = Adafruit_NeoPixel(NUM_PIXELS, pin, NEO_GRB + NEO_KHZ800);
  this->color = this->strip.Color(255, 69, 0);
  this->init();
}

dynblinker::dynblinker(uint8_t pin, uint16_t startpixel, uint16_t endpixel) {
  setpin(pin);
  setstartpixel(startpixel);
  setendpixel(endpixel);
  setNUM_PIXELS(startpixel, endpixel);
  this->strip = Adafruit_NeoPixel(this->NUM_PIXELS, pin, NEO_GRB + NEO_KHZ800);
  this->color = this->strip.Color(255, 69, 0);
  this->init();
}

void dynblinker::begin() {
  this->strip.begin();
  this->strip.show(); // Initialize all pixels to 'off'
}
void dynblinker::setPixel(uint16_t pixel, uint32_t color) {
  this->strip.setPixelColor(pixel, color);
  this->strip.show();
}

void dynblinker::setpin(uint8_t pin) { this->pin = pin; }
void dynblinker::setNUM_PIXELS(uint16_t NUM_PIXELS) {
  this->NUM_PIXELS = NUM_PIXELS;
}
void dynblinker::setNUM_PIXELS(uint16_t startpixel, uint16_t endpixel) {
  if (this->startpixel > this->endpixel) {
    this->NUM_PIXELS = this->startpixel;
  } else {
    this->NUM_PIXELS = this->endpixel;
  }
}
void dynblinker::dynblinker::setstartpixel(uint16_t startpixel) {
  this->startpixel = startpixel;
}
void dynblinker::setendpixel(uint16_t endpixel) { this->endpixel = endpixel; }
void dynblinker::setblinkinterval(uint16_t blinkinterval) {
  this->blinkinterval = blinkinterval;
}
void dynblinker::setblinkerdelayinterval(uint16_t blinkerdelayinterval) {
  this->blinkerdelayinterval = blinkerdelayinterval;
}
uint16_t dynblinker::getoffset() {
  if (this->startpixel > this->endpixel) {
    return this->endpixel;
  } else {
    return this->startpixel;
  }
}

uint16_t dynblinker::getrealpixel(uint16_t pixel) {
  uint16_t realpixel = 0;
  if (this->startpixel > this->endpixel) {
    realpixel = this->NUM_PIXELS - pixel;
  } else {
    realpixel = pixel;
    ;
  }
  realpixel = realpixel + getoffset();
  return realpixel;
}

void dynblinker::blinkon() {
  unsigned long currentMillis = millis();
  if (currentMillis - this->blinkpreviousMillis >= this->blinkinterval) {
    setPixel(getrealpixel(this->blinkoncount), this->color);
    this->blinkoncount++;
    this->blinkpreviousMillis = currentMillis;
  }
}

void dynblinker::blinkoff() {
  setPixel(getrealpixel(this->blinkoffcount), 0);
  this->blinkoffcount++;
}

bool dynblinker::blinkerdelay() {
  bool delayed = false;
  unsigned long currentMillis = millis();
  if (currentMillis - this->blinkerpreviousMillis >=
      this->blinkerdelayinterval) {
    delayed = true;
    this->blinkerpreviousMillis = currentMillis;
  }
  return delayed;
}
void dynblinker::blink() {

  if (this->blinkoncount < this->NUM_PIXELS) {
    blinkon();
  } else if (this->blinkoffcount < this->NUM_PIXELS) {
    if (this->blinkerdelayed == false) {
      if (blinkerdelay()) {
        this->blinkerdelayed = true;
      }
    } else {
      blinkoff();
    }
  } else {
    if (blinkerdelay()) {
      this->blinkoncount = 0;
      this->blinkoffcount = 0;
      this->blinkerdelayed = false;
      this->strip.clear();
    }
  }
}
