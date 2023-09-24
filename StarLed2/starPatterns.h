// starPatterns.h

#ifndef _STARPATTERNS_h
#define _STARPATTERNS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void starRainbow(bool init);
void lj_fill_rainbow(struct CRGB* pFirstLED, int numToFill, uint8_t initialhue, uint8_t deltahue);
void starConfetti(bool init);
void starSparkle(bool init);
void starShift(bool init);
void starNova(bool init);
//void juggle(bool init);


//void starRainbow(bool bInit = false)
//{
//    // FastLED's built-in rainbow generator
//    fill_rainbow(starLeds, cStarLedsCount, gHue++, 7);
//}


void starRainbow(bool init = 0)
{
    //uint8_t lHue = 20;
    CEveryNSeconds patternTimer(10);

    if (init) {
        Serial.println("starRainbow init");
    }
    while (1) {
        if (patternTimer.ready()) {
            starPattern = NULL;
            return;
        }
        // FastLED's built-in rainbow generator
        fill_rainbow(starLeds, cStarLedsCount, starHue +=3, 3);
        starLedController.showLeds();
        //lj_fill_rainbow(starLeds, cStarLedsCount, lHue += 3, 3);
        vTaskDelay(100);
    }
}

void lj_fill_rainbow(struct CRGB* pFirstLED, int numToFill, uint8_t hue, uint8_t deltahue)
{
    static CHSV hsv(hue, 250, 150);
    for (uint8_t i = 0; i < numToFill; ++i) {
        pFirstLED[numToFill - i - 1] = hsv;
        hsv.hue += deltahue;
        starLedController.showLeds();
    }
}

void starConfetti(bool init = false)
{
    CEveryNSeconds patternTimer(10);

    while (true) {
        if (init) {
            ;
        }
        if (patternTimer.ready()) {
            starPattern = NULL;
            return;
        }
        // random colored speckles that blink in and fade smoothly
        fadeToBlackBy(starLeds, cStarLedsCount, 10);
        int pos = random16(cStarLedsCount);
        starLeds[pos] += CHSV(starHue + random8(64), 200, 255);
        starLedController.showLeds();
        vTaskDelay(50);
    }
}

//void confetti()
//{
//    // random colored speckles that blink in and fade smoothly
//    fadeToBlackBy(leds, NUM_LEDS, 10);
//    int pos = random16(NUM_LEDS);
//    leds[pos] += CHSV(gHue + random8(64), 200, 255);
//}

void starSparkle(bool init = 0)
{
    uint8_t lHue = 0;
    CEveryNSeconds patternTimer(10);

    if (init) {
    }
    while (1) {
        if (patternTimer.ready()) {
            starPattern = NULL;
            return;
        }
        uint8_t pos = random8(cStarLedsCount);
        starLeds[pos] = CRGB(250, 230, 250);
        starLedController.showLeds();
        vTaskDelay(100);
        starLeds[pos] = CRGB(0, 0, 0);
    }
}

void starNova(bool init = false) {
    int FlashOnDelay = 80;
    int FlashOffDelay = 100;
    int EndPause = 2000;
    int flashCount = 6;
    //CEveryNSeconds patternTimer(10);

    if (init) {
        init = false;
    }
    //while (1) {
        //if (patternTimer.ready()) {
        //    starPattern = NULL;
        //    return;
        //}
        for (int j = 0; j < flashCount; j++) {
            fill_solid(starLeds, cStarLedsCount, CRGB(64, 64, 64));
            starLedController.showLeds();
            vTaskDelay(FlashOnDelay);
            fill_solid(starLeds, cStarLedsCount, CRGB(0, 0, 0));
            starLedController.showLeds();
            vTaskDelay(FlashOffDelay);
        }
        fill_solid(starLeds, cStarLedsCount, CRGB(250, 250, 250));
        starLedController.showLeds();
        vTaskDelay(EndPause);
        fill_solid(starLeds, cStarLedsCount, CRGB(0, 0, 0));
        starLedController.showLeds();
        starPattern = NULL;
        return;
    //}
    //delay(EndPause);
}

//void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
//    int Position = 0;
//
//    for (int i = 0; i < NUM_LEDS * 2; i++)
//    {
//        Position++; // = 0; //Position + Rate;
//        for (int i = 0; i < NUM_LEDS; i++) {
//            // sine wave, 3 offset waves make a rainbow!
//            //float level = sin(i+Position) * 127 + 128;
//            //setPixel(i,level,0,0);
//            //float level = sin(i+Position) * 127 + 128;
//            setPixel(i, ((sin(i + Position) * 127 + 128) / 255) * red,
//                ((sin(i + Position) * 127 + 128) / 255) * green,
//                ((sin(i + Position) * 127 + 128) / 255) * blue);
//        }
//
//        showStrip();
//        delay(WaveDelay);
//    }
//}

//
//void theaterChaseRainbow(int SpeedDelay) {
//    byte* c;
//
//    for (int j = 0; j < 256; j++) {     // cycle all 256 colors in the wheel
//        for (int q = 0; q < 3; q++) {
//            for (int i = 0; i < NUM_LEDS; i = i + 3) {
//                c = Wheel((i + j) % 255);
//                setPixel(i + q, *c, *(c + 1), *(c + 2));    //turn every third pixel on
//            }
//            showStrip();
//
//            delay(SpeedDelay);
//
//            for (int i = 0; i < NUM_LEDS; i = i + 3) {
//                setPixel(i + q, 0, 0, 0);        //turn every third pixel off
//            }
//        }
//    }
//}

//void rainbowWithGlitter()
//{
//    // built-in FastLED rainbow, plus some random sparkly glitter
//    rainbow();
//    addGlitter(80);
//}
//
//void addGlitter(fract8 chanceOfGlitter)
//{
//    if (random8() < chanceOfGlitter) {
//        leds[random16(NUM_LEDS)] += CRGB::White;
//    }
//}

//void confetti()
//{
//    // random colored speckles that blink in and fade smoothly
//    fadeToBlackBy(leds, NUM_LEDS, 10);
//    int pos = random16(NUM_LEDS);
//    leds[pos] += CHSV(gHue + random8(64), 200, 255);
//}
//
//void sinelon()
//{
//    // a colored dot sweeping back and forth, with fading trails
//    fadeToBlackBy(leds, NUM_LEDS, 20);
//    int pos = beatsin16(13, 0, NUM_LEDS - 1);
//    leds[pos] += CHSV(gHue, 255, 192);
//}

// colored stripes pulsing at a defined Beats-Per-Minute (BPM)
void bpm(bool init = false)
{
    CEveryNSeconds patternTimer(10);

    while (true) {
        if (init) {
            ;
        }
        if (patternTimer.ready()) {
            starPattern = NULL;
            return;
        }
        uint8_t BeatsPerMinute = 62;
        CRGBPalette16 palette = PartyColors_p;
        uint8_t beat = beatsin8(BeatsPerMinute, 64, 255);
        for (int i = 0; i < cStarLedsCount; i++) { //9948
            starLeds[i] = ColorFromPalette(palette, starHue + (i * 2), beat - starHue + (i * 10));
        }
        starLedController.showLeds();
    }
}

//// eight colored dots, weaving in and out of sync with each other
//void juggle(bool init = false) {
//    CEveryNSeconds patternTimer(10);
//
//    while (true) {
//        if (init) {
//            ;
//        }
//        if (patternTimer.ready()) {
//            starPattern = NULL;
//            return;
//        }
//        fadeToBlackBy(starLeds, cStarLedsCount, 75);
//        byte dothue = 0;
//        for (int i = 0; i < 8; i++) {
//            starLeds[beatsin16(i + 7, 0, cStarLedsCount - 1)] |= CHSV(dothue, 200, 255);
//            dothue += 32;
//        }
//        starLedController.showLeds();
//        vTaskDelay(20);
//    }
//}

//void starPulse(bool init = false) {
//
//    //static CHSV bufferLeds[cStarLedsCount];
//    CHSV buff;
//    static uint8_t hue = 0;
//
//    if (init) {
//        ////for (int i = 0; i < cStarLedsCount; i++) {
//        ////    bufferLeds[i] = CHSV(192, 250, 250);    // silver
//        ////    starLeds[i] = bufferLeds[i];
//        ////}
//        rayPattern = rayTracer;
//        rayPattern(true);
//        starTimer.setPeriod(30);
//        //starTimer.reset();
//        hue = random8(0, 250);
//    }
//
//    //uint8_t hue = beatsin8(20, 96, 192);
//    uint8_t sat = beatsin8(12, 200, 250);
//    uint8_t val = beatsin8(15, 50, 200);
//    buff = CHSV(hue, sat, val);
//    for (int i = 0; i < cStarLedsCount; i++) {
//        starLeds[i] = buff;
//    }
//    addStarGlitter(30);
//
//}

void starShift(bool init = false) {
    CEveryNSeconds patternTimer(10);

    while (true) {
        if (init) {
            for (int i = 0; i < cStarLedsCount; ) {
                if (i >= cStarLedsCount) break;
                starLeds[i++] = CRGB(0xFF0000);
                if (i >= cStarLedsCount) break;
                starLeds[i++] = CRGB(0xFF8000);
                if (i >= cStarLedsCount) break;
                starLeds[i++] = CRGB(0x00FF00);
                if (i >= cStarLedsCount) break;
                starLeds[i++] = CRGB(0x00FF80);
                if (i >= cStarLedsCount) break;
                starLeds[i++] = CRGB(0x0000FF);
                if (i >= cStarLedsCount) break;
                starLeds[i++] = CRGB(0x8000FF);
                if (i >= cStarLedsCount) break;
                starLeds[i++] = CRGB(0x000000);
                if (i >= cStarLedsCount) break;
                starLeds[i++] = CRGB(0x000000);
            }
            init = false;
        }

        if (patternTimer.ready()) {
            starPattern = NULL;
            return;
        }

        CRGB save = starLeds[cStarLedsCount - 1];
        for (int i = cStarLedsCount - 1; i > 0; i--) {
            starLeds[i] = starLeds[i - 1];
        }
        starLeds[0] = save;
        starLedController.showLeds();
        vTaskDelay(150);
    }
}


#endif

