#ifndef __DYN_Blinker__
#define __DYN_Blinker__

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>



class dynblinker {

	private:
		uint8_t pin;
		uint16_t NUM_PIXELS;
		uint16_t startpixel;
		uint16_t endpixel;
		uint16_t offset;
		uint32_t color;
		Adafruit_NeoPixel strip;
		bool blinkonrun;
		bool blinkonready;
		uint16_t blinkoncount;
		bool blinkoffrun;
		bool blinkoffready;
		uint16_t blinkoffcount;
		unsigned long blinkpreviousMillis;
		uint16_t blinkinterval;
    unsigned long blinkdpreviousMillis;
    uint16_t blinkdinterval;
    bool blinkddelayed;

	public:
		dynblinker (uint8_t pin, uint16_t NUM_PIXELS);  //Default initial, use all pixel
		dynblinker (uint8_t pin, uint16_t startpixel, uint16_t endpixel);  //use only defined pixel

		void begin();
		void setPixel(uint16_t pixel, uint32_t color);
		void blink();
		void blinkon();
		void blinkoff();
		void clear();


		//void setRGB(int r, int g, int b) ;
		//void blink(char color, byte times, unsigned int ms);
};






#endif
