/*
 Name:		StarLed2.ino
 Created:	8/18/2023 9:28:21 PM
 Author:	rytec
*/

#include <FastLED.h>
#include "Globals2.h"

void setup() {

    static uint8_t startIndex = 0;

    //Serial.begin(115200);
    delay(3000);

    CLEDController& starLedController = FastLED.addLeds<LED_TYPE, STAR_DATA_PIN, COLOR_ORDER>(starLeds, cStarLedsCount);
    CLEDController& raysLedController = FastLED.addLeds<LED_TYPE, RAYS_DATA_PIN, COLOR_ORDER>(rayLeds, cRayLedsCount);

    FastLED.clear(true);
    starPattern = starPatterns[0];
    starPattern(true);

}

void loop() {
  

    EVERY_N_MILLISECONDS(30) {
        // Call the current pattern function once, updating the 'leds' array
        if (starPattern) {
            starPattern(false);
        }
        if (rayPattern) {
            rayPattern(false);
        }
        FastLED.show();
    }

    if (starTimer.ready()) {
        starPattern = transition;
    }
}


void transition(bool init) {
    starPattern = NULL;
    rayPattern = NULL;

    //Serial.println("In transition");
    for (int i = 0; i < 150; i++) {
        fade_raw(starLeds, cStarLedsCount, 2);
        fade_raw(rayLeds, cRayLedsCount, 2);
        FastLED.show();
        //delay(10);
    }
    nextPattern();
    //Serial.println("Out transition");

}

void nextPattern()
{
    // add one to the current pattern number, and wrap around at the end
    starPatternNo = (starPatternNo + 1) % ARRAY_SIZE(starPatterns);
    //Serial.print("patternNo = "); Serial.println(starPatternNo);

    starPattern = starPatterns[starPatternNo];


    starPattern(true);

}
