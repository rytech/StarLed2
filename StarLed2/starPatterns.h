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
void juggle(bool init);
void theaterChaseRainbow(bool init);

// helper function
uint8_t* Wheel(uint8_t WheelPos);

//void starRainbow(bool bInit = false)
//{
//    // FastLED's built-in rainbow generator
//    fill_rainbow(starLeds, cStarLedsCount, gHue++, 7);
//}


void starRainbow(bool init = 0)
{
    CEveryNSeconds patternTimer(20);

    if (init) {
        //Serial.println("starRainbow init");
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
        vTaskDelay(50);
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

    if (init) {
        ;
    }
    while (true) {
        if (patternTimer.ready()) {
            starPattern = NULL;
            return;
        }
        // random colored speckles that blink in and fade smoothly
        fadeToBlackBy(starLeds, cStarLedsCount, 30);
        int pos = random16(cStarLedsCount);
        starLeds[pos] += CHSV(starHue + random8(128), 200, 255);
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

//void RunningLights(uint8_t red, uint8_t green, uint8_t blue, int WaveDelay) {
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


void theaterChaseRainbow(bool init = false) {

    CEveryNSeconds patternTimer(30);

    if (init) {
        init = false;
    }

    while (1) {
        for (int offset = 0; offset < 3; offset++) {
            for (int i = 0; i < cStarLedsCount; i++) {
                uint8_t x1 = beatsin8(5, 0, 250);
                uint8_t x2 = beatsin8(6, 0, 250, 0, 90);
                uint8_t x3 = beatsin8(6, 0, 250, 0, 180);
                //std::cout << "x1 = " << x1 << " x2 = " << x2 << " x3 = " << x3 << std::endl;
                starLeds[i] = CRGB(x1, x2, x3);
            }
            for (int i = offset; i < cStarLedsCount; i=i+3) {
                    starLeds[i] = CRGB(0, 0, 0);    //turn every third pixel off
            }
            starLedController.showLeds();
            vTaskDelay(100);
            if (patternTimer.ready()) {
                starPattern = NULL;
                return;
            }
        }
    }
}

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

// eight colored dots, weaving in and out of sync with each other
void juggle(bool init = false) {

    CEveryNSeconds patternTimer(10);
 
    if (init) {
        ;
    }
    while (true) {
        if (patternTimer.ready()) {
            starPattern = NULL;
            return;
        }
        fadeToBlackBy(starLeds, cStarLedsCount, 75);
        uint8_t dothue = 0;
        for (int i = 0; i < 8; i++) {
            starLeds[beatsin16(i + 7, 0, cStarLedsCount - 1)] |= CHSV(dothue, 200, 255);
            dothue += 32;
        }
        starLedController.showLeds();
        vTaskDelay(20);
    }
}

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
        vTaskDelay(100);
    }
}

void blend(uint8_t& val1, uint8_t val2) {
    if (val1 < val2) {
        val1++;
    }
    if (val1 > val2) {
        val1--;
    }
}

void blendRGB(CRGB& col1, CRGB col2) {
    blend(col1.r, col2.r);
    blend(col1.g, col2.g);
    blend(col1.b, col2.b);
}

void starBlend(bool init = false) {

    CEveryNSeconds patternTimer(20);
    uint8_t hue = random8(0, 250);
    static CRGB col1;
    if (init) {
        init = false;
        col1 = CHSV(hue, 250, 250);
        CRGB startUp = CRGB(0, 0, 0);
        while (startUp != col1) {
            blendRGB(startUp, col1);
            fill_solid(starLeds, cStarLedsCount, startUp);
            starLedController.showLeds();
            vTaskDelay(20);
        }
    }
    while (true) {
        if (patternTimer.ready()) {
            starPattern = NULL;
            return;
        }
        hue += 1370;
        CRGB col2 = CHSV(hue, 250, 250);
        //CRGB delta = col2 - col1;
        while (col2 != col1) {
            blendRGB(col1, col2);
            fill_solid(starLeds, cStarLedsCount, col1);
            starLedController.showLeds();
            vTaskDelay(30);
        }
        col1 = col2;
    }
}

void colorWipe(bool init = false) {
    
    CEveryNSeconds patternTimer(30);

    if (init) {
        std::cout << "colorWipe" << std::endl;
        init = false;
    }
    for (int i = 0 ; i <2; i++) {
        uint8_t r = random8(150);
        uint8_t g = random8(180);
        uint8_t b = random8(200);
        for (int i = 0; i < cStarLedsCount; i++) {
            starLeds[i] = CRGB(r, g, b);
            starLedController.showLeds();
            vTaskDelay(50);
        }
        vTaskDelay(200);
        fill_solid(starLeds, cStarLedsCount, CRGB(0, 0, 0));
    }
    starPattern = NULL;
    return;
}

#endif

