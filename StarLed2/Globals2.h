// Globals2.h

#ifndef _GLOBALS2_h
#define _GLOBALS2_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

//#include "raySkyBalls.h"
//#include "Meteor.h"
//#include "starRainbow.h"
//#include "rayTracer.h"

#define RDEBUG = 1

    #define LED_TYPE    WS2811
    #define COLOR_ORDER GRB
    #define UPDATES_PER_SECOND  50

    #define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))


    const uint8_t cStarLedsCount = 80;
    const uint8_t cRayLedsCount = 70;

    const uint8_t STAR_DATA_PIN = 4;
    const uint8_t RAYS_DATA_PIN = 5;

    // Define the array of leds
    CRGB starLeds[cStarLedsCount];
    CRGB rayLeds[cRayLedsCount];
    CRGB starTransLeds[cStarLedsCount];
    CHSV hsvStarLeds[cStarLedsCount];

    CLEDController& starLedController = FastLED.addLeds<LED_TYPE, STAR_DATA_PIN, COLOR_ORDER>(starLeds, cStarLedsCount);
    CLEDController& rayLedController = FastLED.addLeds<LED_TYPE, RAYS_DATA_PIN, COLOR_ORDER>(rayLeds, cRayLedsCount);

    uint8_t starHue{ 15 };
    uint8_t rayHue{ 80 };

    TaskHandle_t starTask;
    TaskHandle_t rayTask;

    CEveryNSeconds starPatternTimer(20);

    typedef void (*ptrRayPattern)(bool);
    ptrRayPattern rayPattern = NULL; // 

    typedef void (*ptrStarPattern)(bool);
    ptrStarPattern starPattern = NULL;

    struct runItem {
        ptrStarPattern starPattern;
        ptrRayPattern rayPattern;
        int runTime;
    };

    std::vector<runItem> runList;
    //    {starRainbow, rayTracer, 10},
    //    {starPattern2, rayPattern2, 10}
    //};


    //void raySkyBalls(bool init);
    //void rayTracer(bool);

#endif

