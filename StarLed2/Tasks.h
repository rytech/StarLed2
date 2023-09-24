// Tasks.h

#ifndef _TASKS_h
#define _TASKS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

// globalnamespace
//
//

    void starTaskCode(void* pvParameters);
    void rayTaskCode(void* pvParameters);

    //typedef void (*starPatternList[])(bool);
    //starPatternList starPatterns = {
        //starDotty, transition, 
        //starRainbow, transition,
        //starSingleColor, transition, 
        //confetti, transition, 
        //starPulse, transition, 
        //lj_starBlend, transition

    //};

    void starTaskCode(void* pvParameters) {
        while (1) {
            //Serial.println("This is StarTask");
            if (starPattern) {
                starPattern(true);
            }
            else {
                vTaskDelay(100);
            }
        }
    }

    void rayTaskCode(void* pvParameters) {
        while (1) {
            //Serial.println("This is RayTask");
            if (rayPattern) {
                rayPattern(true);
            }
            else {
                vTaskDelay(100);
            }
        }
    }

#endif

