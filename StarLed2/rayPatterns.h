// rayPatterns.h

#ifndef _RAYPATTERNS_h
#define _RAYPATTERNS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

void rayTracer(bool init);
void rayWhiteTracer(bool init);
void raySkyBalls(bool init);
void rayJuggle(bool init);


void rayTracer(bool init = 0) {

	uint8_t hue = 20;
	uint8_t pos = 0;
	uint8_t prevPos = 0;
	uint32_t timebase = millis() & 0xFFFFFF00;
	//CEveryNSeconds patternTimer(10);

	if (init) {
		//Serial.println("rayTracer init");
		//prevPos = pos;
		init = false;
	}
	//Serial.println("rayTracer");
	while (true && rayPattern) {
		//Serial.println("rayTracer init");
		fadeToBlackBy(rayLeds, cRayLedsCount, 50);
		pos = beat8(30, timebase);
		if (pos == prevPos) {
			break;
		}
		prevPos = pos;
		int ledNo = (pos * cRayLedsCount) / 255;
		rayLeds[ledNo] += CHSV(hue += 2, 255, 192);
		rayLedController.showLeds();
		vTaskDelay(20);
	}
}

void rayWhiteTracer(bool init = 0) {

	uint8_t pos = 0;
	uint8_t prevPos = 0;
	uint32_t timebase = millis() & 0xFFFFFF00;

	//if (init) {
	//	init = false;
	//}
	while (true && rayPattern) {
		fadeToBlackBy(rayLeds, cRayLedsCount, 50);
		pos = beat8(30, timebase);
		if (pos == prevPos) {
			break;
		}
		prevPos = pos;
		int ledNo = (pos * cRayLedsCount) / 255;
		rayLeds[ledNo] = CRGB(180, 180, 180);
		rayLedController.showLeds();
		vTaskDelay(20);
	}
}

void raySkyBalls(bool init = false) {
	int refresh = 0;
	SkyBall redBall = SkyBall(HUE_RED, cRayLedsCount, 10, 50);
	SkyBall greenBall = SkyBall(HUE_GREEN, cRayLedsCount * 9 / 10, 10, 40);
	SkyBall blueBall = SkyBall(HUE_BLUE, cRayLedsCount * 8 / 10, 10, 30);

	//redBall.showPattern();
	//Serial.println("raySkyBalls in");
	while (true && rayPattern) {
		//EVERY_N_SECONDS(10) {
		//	// stop the pattern after 10 seconds
		//	rayPattern = NULL;
		//	return;
		//}
		int redLed = -1;
		int greenLed = -1;
		int blueLed = -1;

		redLed = redBall.showPattern();
		rayLeds[redLed] = redBall.color;

		greenLed = greenBall.showPattern();
		rayLeds[greenLed] = greenBall.color;

		blueLed = blueBall.showPattern();
		rayLeds[blueLed] = blueBall.color;

		//Serial.println("raySkyBalls 1");
		fadeToBlackBy(rayLeds, cRayLedsCount, 0x20);
		rayLedController.showLeds();
		vTaskDelay(10);
		//Serial.println("raySkyBalls 2");
	}
}

// eight colored dots, weaving in and out of sync with each other
void rayJuggle(bool init = false) {
	CEveryNSeconds patternTimer(10);

	while (true) {
		if (init) {
			;
		}
		if (patternTimer.ready()) {
			rayPattern = NULL;
			return;
		}
		fadeToBlackBy(rayLeds, cRayLedsCount, 75);
		byte dothue = 0;
		for (int i = 0; i < 8; i++) {
			rayLeds[beatsin16(i + 7, 0, cRayLedsCount - 1)] |= CHSV(dothue, 200, 255);
			dothue += 32;
		}
		rayLedController.showLeds();
		vTaskDelay(20);
	}
}


//void meteorRain(byte red, byte green, byte blue, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {
//    setAll(0, 0, 0);
//
//    for (int i = 0; i < NUM_LEDS + NUM_LEDS; i++) {
//
//
//        // fade brightness all LEDs one step
//        for (int j = 0; j < NUM_LEDS; j++) {
//            if ((!meteorRandomDecay) || (random(10) > 5)) {
//                fadeToBlack(j, meteorTrailDecay);
//            }
//        }
//
//        // draw meteor
//        for (int j = 0; j < meteorSize; j++) {
//            if ((i - j < NUM_LEDS) && (i - j >= 0)) {
//                setPixel(i - j, red, green, blue);
//            }
//        }
//
//        showStrip();
//        delay(SpeedDelay);
//    }
//}

//void juggle() {
//    // eight colored dots, weaving in and out of sync with each other
//    fadeToBlackBy(leds, NUM_LEDS, 20);
//    byte dothue = 0;
//    for (int i = 0; i < 8; i++) {
//        leds[beatsin16(i + 7, 0, NUM_LEDS - 1)] |= CHSV(dothue, 200, 255);
//        dothue += 32;
//    }
//}

void rayConfetti(bool init = false)
{
	if (init) {
		;
	}
	while (true && starPattern) {
		// random colored speckles that blink in and fade smoothly
		fadeToBlackBy(rayLeds, cRayLedsCount, 20);
		int pos = random16(cRayLedsCount);
		rayLeds[pos] += CHSV(starHue + random8(64), 200, 255);
		rayLedController.showLeds();
		vTaskDelay(100);
	}
	rayPattern = NULL;
}


#endif

