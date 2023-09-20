// raySkyBalls.h

#ifndef _RAYSKYBALLS_h
#define _RAYSKYBALLS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif


class SkyBall {

public:

	CRGB color = CHSV(HUE_BLUE, 0xFF, 0xFF);
	int ledsCount;
	int initialDelay;
	int finalDelay;
	unsigned long targetTime = 0L;
	int currentLedNo = 1;
	int direction = 1;

	const CLEDController& controller{ starLedController };

	SkyBall(int8_t hue, int count, int initial, int final) :
		color{ CHSV(hue, 0xFF, 0xFF) }, 
		ledsCount{count	}, 
		initialDelay{ initial }, 
		finalDelay(final)
	{};

	unsigned long calcDelay(int ledNo) {
		float m = (float)((finalDelay - initialDelay) * ledNo / ((float)(ledsCount-1)) + initialDelay);
		return (unsigned long)m;
	};

	int showPattern() {

		if (millis() >= targetTime) {
			//rayLedController.clearLedData();
			if (direction >= 0) {
				if (++currentLedNo >= ledsCount - 1) {
					direction = -1;
				}
			}
			else {
				if (--currentLedNo <= 1) {
					direction = 1;
				}
			}
			rayLeds[currentLedNo] = color;
			unsigned long x = calcDelay(currentLedNo);
			targetTime = millis() + calcDelay(currentLedNo);
			return currentLedNo;
		}
		return currentLedNo;
	};
};


// global namespace
//
//

void raySkyBalls(bool init = false) {
	int refresh = 0;
	SkyBall redBall = SkyBall(HUE_RED, cRayLedsCount, 10, 50);
	SkyBall greenBall = SkyBall(HUE_GREEN, cRayLedsCount*9/10, 10, 40);
	SkyBall blueBall = SkyBall(HUE_BLUE, cRayLedsCount*8/10, 10, 30);

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
		fadeToBlackBy(rayLeds, cRayLedsCount, 0x10);
		rayLedController.showLeds();
		//Serial.println("raySkyBalls 2");
	}
}


#endif

