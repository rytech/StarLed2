// rayMeteor.h

#ifndef _RAYMETEOR_h
    #define _RAYMETEOR_h
#endif

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
    void rayMeteor(bool init);
    void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean metcRayLedsCounteorRandomDecay, int SpeedDelay);
    //void fadeToBlack(int ledNo, byte fadeValue);
    void setPixel(int ledNo, byte red, byte green, byte blue);
    void setAll(byte green, byte red, byte blue);

    class Meteor {
    public :
        uint8_t len{ 4 };
        uint8_t endPos{ 0 };
        CRGB color{ CRGB(0xFF, 0, 0) };
        uint8_t decayRate{ 0xc0 };

        void draw() {
            int maxLed = cRayLedsCount -1;
            int len2 = len;
            for (endPos = 0; endPos <= maxLed + len; endPos++) {
               for (int j = 0; j < len; j++) {
                    rayLeds[endPos+j] = color;
                   if (endPos + j > maxLed) {
                   }
                   //else {
                   //    endPos--;
                   //    for (int x = len - 1; x >= 0; x--) {
                   //        rayLeds[endPos+x] = color;
                   //    }
                   //}
               }
               //decay
                for (int j = endPos; j >= 0; j--) {
                    if (random(10) > 5) {
                        //fadeToBlack(j, meteorTrailDecay);
                        rayLeds[j].fadeToBlackBy(decayRate);
                    }
                }
                rayLedController.showLeds();
                delay(50);
            }
            //int copyLen = len;
            //if (endPos >= cRayLedsCount) {
            //    endPos = cRayLedsCount - 1;
            //    return 0;
            //}
            //for (int i = endPos; i < cRayLedsCount; i++) {
            //    rayLeds[i] = color;
            //}
            //endPos++;

            //// draw trail
            //return 1;
        }

        void trailDecay() {
            delay(200);
            for (int j = cRayLedsCount - 1 ; j >= 0; j--) {
                if (random(10) > 3) {
                    //fadeToBlack(j, meteorTrailDecay);
                    rayLeds[j].fadeToBlackBy(decayRate);
                }
            }
            rayLedController.showLeds();
        }

        //void fin() {
        //    for (int j = 0; j < 10 ; j++) {
        //        //if (random(10) > 5) {
        //            fadeToBlackBy(rayLeds, cRayLedsCount, 0xF0);
        //            rayLedController.showLeds();
        //            delay(100);
        //        //}
        //    }
        //}

        //void update() {
        //    fadeToBlackBy(rayLeds, cRayLedsCount, 0xFF);    //set all ray leds to black
        //    int cont = 1;
        //    while (cont) {
        //        trailDecay();
        //        cont = draw();
        //        rayLedController.showLeds();
        //        delay(50);
        //    }
        //    trailDecay();
        //}
    };

    void rayMeteor(bool init = false) {
        Meteor meteor = Meteor();
        while (rayPattern) {
            EVERY_N_SECONDS(10) {
                // stop the pattern after 10 seconds
                rayPattern = NULL;
                return;
            }
            //fadeToBlackBy(rayLeds, cRayLedsCount, 0xFF);    //set all ray leds to black
            meteor.trailDecay();
            meteor.draw();
            for (int i = 0; i < 10; i++) {
                meteor.trailDecay();
            }
            //delay(50);
        }
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
            //delay(SpeedDelay);
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

