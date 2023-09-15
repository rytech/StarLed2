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

    if (init) {
        prevPos = pos;
        init = false;
    }
    Serial.println("rayTracer");
    while (true) {
        EVERY_N_SECONDS(10) {
            // stop the pattern after 10 seconds
            rayPattern = NULL;
            return;
        }
        //Serial.println("rayTracwe");
        fadeToBlackBy(rayLeds, cRayLedsCount, 50);
        pos = beatsin16(8, 0, cRayLedsCount - 1);
        if (pos == prevPos) {
            ;
        }
        else if (pos < prevPos) {
            prevPos = pos;
            pos -= cRayLedsCount - 1;
            pos *= -1;
            rayLeds[pos] += CHSV(hue += 2, 255, 192);
            //Serial.print("pos desc = ");
            //Serial.println(pos);
            //return;
        }
        //prevPos = pos;
        //rayLeds[pos] += CHSV(hue += 2, 255, 192);
        vTaskDelay(100);
    }
}


#endif

