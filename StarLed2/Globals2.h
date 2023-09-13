// Globals2.h

#ifndef _GLOBALS2_h
#define _GLOBALS2_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

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
    uint8_t rayHue{ 34 };

    TaskHandle_t starTask;
    TaskHandle_t rayTask;


    //CEveryNSeconds starTimer(20);

    void raySkyBalls(bool init);
    //void rayTracer(bool);

#endif

