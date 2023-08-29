/*
 Name:		StarLed2.ino
 Created:	8/18/2023 9:28:21 PM
 Author:	rytec
*/

#include <FastLED.h>
#include "Globals2.h"
#include "raySkyBalls.h"

void setup() {

    Serial.begin(115200);
    delay(3000);

    FastLED.clear(true);
    //starPattern = starPatterns[0];
    //starPattern(true);
    //rayPattern(true);
    // 

    rayPattern = raySkyBalls;

    //D(Serial.printf("This is a debug message\n"));
    //Serial.println("This is a debug message");
    //Serial.printf("This is a debug message using printf\n");

    //SkyBall redBall = SkyBall(HUE_RED, cRayLedsCount, 20, 200);
    //for (int i = 0 ; i < cRayLedsCount; ++i) {
    //    unsigned long x = redBall.calcDelay(i);
    //    Serial.print("led = ");
    //    Serial.print(i);
    //    Serial.print("delay = ");
    //    Serial.println(x);
    //}
    Serial.println("Setup out");
    //FastLED.showColor(CRGB(0X00, 0X00, 0xFF));
}

void loop() {

    //if (starTimer.ready()) {
    //    starPattern = transition;
    //}
    // 
    if (starPattern) {
        starPattern(false);
    }
    if (rayPattern) {
        rayPattern(false);
    }
    //FastLED.show();

    //Serial.println("rayPattern to be called");
    //rayPattern(true);

    //int x = 10;
    //delay(5000);
    transition(false);
    //Serial.println("loop out");
}


void transition(bool init) {
    starPattern = NULL;
    rayPattern = NULL;

    Serial.println("transition in");
    delay(500);
    for (int i = 0; i < 150; i++) {
        fade_raw(starLeds, cStarLedsCount, 4);
        fade_raw(rayLeds, cRayLedsCount, 4);
        FastLED.show();
    }
    nextPattern();
}

void nextPattern()
{
    Serial.println("nextPattern in");

    // add one to the current pattern number, and wrap around at the end
    //starPatternNo = (starPatternNo + 1) % ARRAY_SIZE(starPatterns);

    //starPattern = starPatterns[starPatternNo];
    //starPattern(true);
    
    // for test purposes
    rayPattern = raySkyBalls;
    rayPattern(true);
}

