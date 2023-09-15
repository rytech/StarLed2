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

    class Meteor {
    public :
        const uint8_t len{ 4 };
        uint8_t endPos;
        CRGB color;
        uint8_t decayRate;
        CLEDController* pController;
        CRGB* leds;
        uint8_t maxPos;
        uint8_t hue;

        Meteor() :
            endPos(0), decayRate(0xC0), pController(nullptr),
            leds(nullptr), maxPos(0)
        {};

        Meteor(CLEDController* _pController, CRGB* _leds, uint8_t ledsCount, uint8_t _decayRate, uint8_t _hue) : 
            pController(_pController), leds(_leds), decayRate(_decayRate), hue(_hue)
        {
            maxPos = ledsCount-1;
            color = CHSV(15, 0xFF, 0xFF);
        };

        void draw() {
            color = CHSV(rayHue, 0xFF, 0xFF);
            for (endPos = 0; endPos <= maxPos; endPos++) {
                rayHue += 10;
                if (endPos + len > maxPos) {
                    for (int j = 0; j + endPos < maxPos ; j++) {
                        leds[endPos + j] = color;
                    }
                }
                else {
                    for (int j = 0; j < len; j++) {
                        leds[endPos + j] = color;
                    }
                }
               //decay
                for (int j = endPos-1; j >= 0; j--) {
                    if (random(10) > 5) {
                        leds[j].fadeToBlackBy(decayRate);
                    }
                }
                pController->showLeds();
                delay(20);
            }
        }

        void trailDecay() {

            //delay(200);
            for (int j = cRayLedsCount - 1 ; j >= 0; j--) {
                if (random(10) > 5) {
                    leds[j].fadeToBlackBy(decayRate);
                }
            }
            pController->showLeds();
        }
    };

    // global namespace
    //
    //

    void meteorShow(Meteor& meteor) {
        while (rayPattern) {
            EVERY_N_SECONDS(10) {
                // stop the pattern after 10 seconds
                rayPattern = NULL;
                return;
            }
            meteor.trailDecay();
            meteor.draw();
            delay(200);
            for (int i = 0; i < 15; i++) {
                meteor.trailDecay();
            }
        }
    }
    void rayMeteor(bool init = false) {

        Meteor meteor = Meteor(&rayLedController, rayLeds, cRayLedsCount, 0xC0, rayHue);
        //meteorShow(meteor);
        while (rayPattern) {
            EVERY_N_SECONDS(10) {
                // stop the pattern after 10 seconds
                rayPattern = NULL;
                return;
            }
            meteor.trailDecay();
            meteor.draw();
            vTaskDelay(200);
            for (int i = 0; i < 15; i++) {
                meteor.trailDecay();
            }
        }


    }

    //void starMeteor(bool init = false) {

    //    Meteor meteor = Meteor(&starLedController, starLeds, cStarLedsCount, 0xC0, rayHue);
    //    meteorShow(meteor);

    //}

