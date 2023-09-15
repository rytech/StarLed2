// starRainbow.h

#ifndef _STARRAINBOW_h
#define _STARRAINBOW_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void starRainbow(bool init);
void lj_fill_rainbow(struct CRGB* pFirstLED, int numToFill, uint8_t initialhue, uint8_t deltahue);


void starRainbow(bool init = 0)
{
    uint8_t lHue = 0;

    if (init) {
        starPatternTimer.setPeriod(10);
    }

    while(1) {
        if (starPatternTimer) {
            starPattern = NULL;
            return;
        }
        // FastLED's built-in rainbow generator
        lj_fill_rainbow(starLeds, cStarLedsCount, lHue += 3, 3);
        vTaskDelay(5);
    }
}

void lj_fill_rainbow(struct CRGB* pFirstLED, int numToFill, uint8_t initialhue, uint8_t deltahue)
{
    CHSV hsv(initialhue, 250, 150);
    for (uint8_t i = 0; i < numToFill; ++i) {
        pFirstLED[numToFill - i - 1] = hsv;
        hsv.hue += deltahue;
    }
}



#endif
