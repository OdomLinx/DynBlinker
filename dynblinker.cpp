#include "dynblinker.h"

dynblinker::dynblinker(uint8_t pin, uint16_t NUM_PIXELS) {
  this->pin = pin;
  this->NUM_PIXELS = NUM_PIXELS;
  this->startpixel = 0;
  this->endpixel = NUM_PIXELS - 1;
  this->offset = 0;
  this->strip = Adafruit_NeoPixel(NUM_PIXELS, pin, NEO_GRB + NEO_KHZ800);
  this->color = this->strip.Color(255, 69, 0);
  this->blinkonrun = false;
  this->blinkonready = false;
  this->blinkoncount = 0;
  this->blinkoffrun = false;
  this->blinkoffcount = 0;
  this->blinkoffready = false;
  this->blinkpreviousMillis = 0;
  this->blinkinterval = 200 / NUM_PIXELS;
  this->blinkdpreviousMillis = 0;
  this->blinkdinterval = 1000;
  this->blinkddelayed = false;
}

dynblinker::dynblinker(uint8_t pin, uint16_t startpixel, uint16_t endpixel) {
  this->pin = pin;

  this->startpixel = startpixel;
  this->endpixel = endpixel;
  if (this->startpixel > this->endpixel) {
    this->NUM_PIXELS = this->startpixel - this->endpixel;
    this->offset = this->endpixel;
  } else {
    this->NUM_PIXELS = this->endpixel - this->startpixel;
    this->offset = this->startpixel;
  }

  this->strip = Adafruit_NeoPixel(this->NUM_PIXELS + this->offset, pin,
                                  NEO_GRB + NEO_KHZ800);
  this->color = this->strip.Color(255, 69, 0);
  this->blinkonrun = false;
  this->blinkonready = false;
  this->blinkoncount = 0;
  this->blinkoffrun = false;
  this->blinkoffcount = 0;
  this->blinkoffready = false;
  this->blinkpreviousMillis = 0;
  this->blinkinterval = 200 / NUM_PIXELS;
  this->blinkdpreviousMillis = 0;
  this->blinkdinterval = 1000;
  this->blinkddelayed = false;
}

void dynblinker::begin() {
  this->strip.begin();
  this->strip.show(); // Initialize all pixels to 'off'
}
void dynblinker::setPixel(uint16_t pixel, uint32_t color) {
  Serial.print("setpixel: ");
  Serial.println(pixel);
  Serial.print("color: ");
  Serial.println(color);
  this->strip.setPixelColor(pixel, color);
  this->strip.show();
}
void dynblinker::blinkon() {

  if (this->blinkoncount < this->NUM_PIXELS) {

    this->blinkonrun = true;
    unsigned long currentMillis = millis();
    if (currentMillis - this->blinkpreviousMillis >= this->blinkinterval) {
      uint16_t pixel = 0;
      if (this->startpixel > this->endpixel) {
        pixel = this->NUM_PIXELS - this->blinkoncount;
      } else {
        pixel = this->blinkoncount;
      }
      pixel = pixel + this->offset;
      setPixel(pixel, this->color);
      this->blinkoncount++;
      this->blinkpreviousMillis = currentMillis;
    }
  } else {
    this->strip.clear();
    this->blinkonready = true;
    this->blinkddelayed = false;
  }
}

void dynblinker::blinkoff() {
  if (this->blinkoffcount < this->NUM_PIXELS) {
    Serial.println("off");
    this->blinkoffrun = true;
    uint16_t pixel = 0;
    pixel = this->blinkoffcount + this->offset;
    setPixel(pixel, 0);
    this->blinkoffcount++;

  } else {
    this->strip.clear();
    this->blinkoffready = true;
    this->blinkddelayed = false;
  }
}
void dynblinker::blink() {

  if (this->blinkoffrun == false) {

    blinkon();
  } else {

    if (this->blinkonready) {

      blinkoff();
    }
  }

  if (this->blinkddelayed == false) {

    unsigned long currentMillis = millis();
    if (currentMillis - this->blinkdpreviousMillis >= this->blinkdinterval) {

      if (blinkonready == true) {

        this->blinkonrun = false;
        this->blinkoffrun = true;
        this->blinkoncount = 0;
      }
      if (blinkoffready == true) {
        this->blinkoffrun = false;
        this->blinkoffcount = 0;
        this->blinkoffready = false;
      }

      this->blinkddelayed = true;
      this->blinkdpreviousMillis = currentMillis;
    }
  }
}
