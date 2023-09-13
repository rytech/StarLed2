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

    typedef void (*ptrRayPattern)(bool);
    ptrRayPattern rayPattern = NULL; // 

    typedef void (*rayPatternList[])(bool);
    rayPatternList rayPatterns = {
        //rayTracer,
        //raySkyBalls,
    };

    typedef void (*ptrStarPattern)(bool);
    ptrStarPattern starPattern;

    //void transition(bool init);
    //void starRainbow(bool init);
    //void starDotty(bool init);
    //void rayTracer(bool init);
    //void starSingleColor(bool init);
    //void confetti(bool bInit);
    //void starShift(bool init);
    //void Fire2012(bool init);
    //void starPulse(bool init);
    //void lj_starBlend(bool init);

    typedef void (*starPatternList[])(bool);
    starPatternList starPatterns = {
        //starDotty, transition, 
        //starRainbow, transition,
        //starSingleColor, transition, 
        //confetti, transition, 
        //starPulse, transition, 
        //lj_starBlend, transition

    };

    uint8_t runItemNo = 0;
    int patternRunTime = 0;

    void starPattern1(bool init) {
        if (init) {
            init = false;
        }
        while (true) {
            EVERY_N_SECONDS(10) {
                // stop the pattern after 10 seconds
                starPattern = NULL;
                Serial.println("starPattern1 out");
                return;
            }
            Serial.println("starPattern1");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    void starPattern2(bool init) {
        if (init) {
            init = false;
        }
        while (true) {
            EVERY_N_SECONDS(10) {
                // stop the pattern after 10 seconds
                starPattern = NULL;
                return;
            }
            Serial.println("starPattern2");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

    }

    void rayPattern1(bool init) {
        if (init) {
            init = false;
        }
        Serial.println("rayPattern1");
        while (true) {
            EVERY_N_SECONDS(10) {
                // stop the pattern after 10 seconds
                rayPattern = NULL;
                return;
            }
            Serial.println("rayPattern1a");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    void rayPattern2(bool init) {
        if (init) {
            init = false;
        }
        Serial.println("rayPattern2");
        while (true) {
            EVERY_N_SECONDS(10) {
                // stop the pattern after 10 seconds
                rayPattern = NULL;
                return;
            }
            Serial.println("rayPattern2a");
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }

    struct runItem {
        ptrStarPattern starPattern;
        ptrRayPattern rayPattern;
        int runTime;
    };

    std::vector<runItem> runList {
        {starPattern1, rayPattern1, 10},
        {starPattern2, rayPattern2, 10}
    };

void starTaskCode(void* pvParameters);
void rayTaskCode(void* pvParameters);



void starTaskCode(void* pvParameters) {
    while (1) {
        Serial.println("This is StarTask");
        if (starPattern) {
            starPattern(true);
        }
        else {
		    vTaskDelay(1000 / portTICK_PERIOD_MS);
 		}
    }
}

void rayTaskCode(void* pvParameters) {
	while (1) {
		Serial.println("This is RayTask");
        if (rayPattern) {
            rayPattern(true);
         }
        else {
		    vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
	}
}

#endif

