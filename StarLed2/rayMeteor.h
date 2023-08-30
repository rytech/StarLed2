// rayMeteor.h

#ifndef _RAYMETEOR_h
    #define _RAYMETEOR_h
#endif

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
    void rayMeteorRain(bool init);
    void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean metcRayLedsCounteorRandomDecay, int SpeedDelay);
    //void fadeToBlack(int ledNo, byte fadeValue);
    void setPixel(int ledNo, byte red, byte green, byte blue);
    void setAll(byte green, byte red, byte blue);

    void rayMeteorRain(bool init = false) {
        if (init) {
            fadeToBlackBy(rayLeds, cRayLedsCount, 0xFF);    //set all ray leds to black
            rayLedController.showLeds(0);
            delay(50);
            return;
        }
        meteorRain(0, 0, 0xff, 10, 0xA0, true, 10);
    }


    void meteorRain(byte green, byte red, byte blue, 
        byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {

        while (true && rayPattern) {
            EVERY_N_SECONDS(10) {
                // stop the pattern after 10 seconds
                rayPattern = NULL;
                return;
            }
            for (int i = 0; i < cRayLedsCount; i++) {
                // fade brightness all LEDs one step
                for (int j = 0; j < cRayLedsCount; j++) {
                    if ((!meteorRandomDecay) || (random(10) > 5)) {
                        //fadeToBlack(j, meteorTrailDecay);
                        rayLeds[j].fadeToBlackBy(meteorTrailDecay);
                    }

                    // draw meteor
                    for (int j = 0; j < meteorSize; j++) {
                        if ((i - j < cRayLedsCount) && (i - j >= 0)) {
                            rayLeds[i - j] = CRGB(green, red, blue);
                        }
                    }
                    rayLedController.showLeds();
                }
            }
            //showStrip();
            delay(SpeedDelay);
        }
    }


    // used by meteorrain
    //void fadeToBlack(int ledNo, byte fadeValue) {
    void setPixel(int ledNo, byte red, byte green, byte blue) {
        // FastLED
        rayLeds[ledNo].r = red;
        rayLeds[ledNo].g = green;
        rayLeds[ledNo].b = blue;
    }

    // Set all LEDs to a given color and apply it (visible)
    void setAll(byte red, byte green, byte blue) {
        const CRGB color = CRGB(red, green, blue);
        for (int i = 0; i < cRayLedsCount; i++) {
            rayLeds[i] = color;
            //setPixel(i, red, green, blue);
        }
        rayLedController.showLeds();
        //showStrip();
        //FastLED.show();

    }

