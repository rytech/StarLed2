// rayTracer.h

#ifndef _RAYTRACER_h
#define _RAYTRACER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void rayTracer(bool init);

void rayTracer(bool init = 0) {

    uint8_t hue = 20;
    uint8_t pos = 0;
    uint8_t prevPos;
    //CEveryNSeconds patternTimer(10);

    if (init) {
        //Serial.println("rayTracer init");
        prevPos = pos;
        init = false;
    }
    //Serial.println("rayTracer");
    while (true && rayPattern) {
        //Serial.println("rayTracer init");
        fadeToBlackBy(rayLeds, cRayLedsCount, 50);
        pos = beat8(30);
        if (pos == prevPos) {
            Serial.println("rayTracer no change");
            break;
        }
        prevPos = pos;
        int ledNo = (pos * cRayLedsCount) / 255;
        rayLeds[ledNo] += CHSV(hue += 2, 255, 192);
        rayLedController.showLeds();
        vTaskDelay(20);
    }
    //Serial.println("rayTracer out");
}




#endif

