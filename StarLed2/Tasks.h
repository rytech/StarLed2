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

    void starPattern1(bool init);
    void starPattern2(bool init);
    void rayPattern1(bool init);
    void rayPattern2(bool init);

    CEveryNSeconds starPatternTimer(20);

    typedef void (*ptrRayPattern)(bool);
    ptrRayPattern rayPattern = NULL; // 

    typedef void (*ptrStarPattern)(bool);
    ptrStarPattern starPattern;

    //typedef void (*starPatternList[])(bool);
    //starPatternList starPatterns = {
        //starDotty, transition, 
        //starRainbow, transition,
        //starSingleColor, transition, 
        //confetti, transition, 
        //starPulse, transition, 
        //lj_starBlend, transition

    //};

    struct runItem {
        ptrStarPattern starPattern;
        ptrRayPattern rayPattern;
        int runTime;
    };

    std::vector<runItem> runList{
        {starRainbow, rayTracer, 10},
        {starPattern2, rayPattern2, 10}
    };




    void starTaskCode(void* pvParameters) {
        while (1) {
            Serial.println("This is StarTask");
            if (starPattern) {
                starPattern(true);
            }
            else {
                vTaskDelay(1000);
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


#endif

