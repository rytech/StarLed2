// confetti.h

#ifndef _CONFETTI_h
#define _CONFETTI_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void starConfetti(bool init);

void starConfetti(bool init = false)
{
    CEveryNSeconds patternTimer(10);

    while(true) {
        if (init) {
        //Serial.println("starRainbow init");
        }
    //Serial.println("starRainbow in");
    //uint8_t hue = 10;
    if (patternTimer.ready()) {
        starPattern = NULL;
        return;
    }
    // random colored speckles that blink in and fade smoothly
    fadeToBlackBy(starLeds, cStarLedsCount, 50);
    int pos = random16(cStarLedsCount);
    starLeds[pos] += CHSV(random8(250), 200, 255);
    starLedController.showLeds();
    vTaskDelay(50);
    }
}


#endif

