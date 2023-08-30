// rayMeteor.h

#ifndef _RAYMETEOR_h
    #define _RAYMETEOR_h
#endif

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

    void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean metcRayLedsCounteorRandomDecay, int SpeedDelay);
    //void fadeToBlack(int ledNo, byte fadeValue);
    void setPixel(int ledNo, byte red, byte green, byte blue);
    void setAll(byte red, byte green, byte blue);


    void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {

        fadeToBlackBy(rayLeds, cRayLedsCount, 0xFF);    //set all ray leds to black

        for (int i = 0; i < cRayLedsCount ; i++) {
            // fade brightness all LEDs one step
            for (int j = 0; j < cRayLedsCount; j++) {
                if ((!meteorRandomDecay) || (random(10) > 5)) {
                    //fadeToBlack(j, meteorTrailDecay);
                    rayLeds[j].fadeToBlackBy(meteorTrailDecay);
                }
            }

            // draw meteor
            for (int j = 0; j < meteorSize; j++) {
                if ((i - j < cRayLedsCount) && (i - j >= 0)) {
                    rayLeds[i-j] = CRGB(red, blue, green);
                }
            }
            //showStrip();
            rayLedController.showLeds();
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

