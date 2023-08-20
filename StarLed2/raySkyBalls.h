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
	int ledsCount;
	int initialDelay;
	int finalDelay;
	CHSV color = CHSV(0, 0, 0);
	unsigned long targetTime = 0L;


	SkyBall(int count, int initial, int final) :
		ledsCount{ count }, initialDelay{ initial }, finalDelay(final)
	{};

	unsigned long calcDelay(int ledNo) {
		float m = (float)((finalDelay - initialDelay) / ((float)(ledNo * ledNo)) + initialDelay);
		return (unsigned long)m;
	};

	int showPattern() {

		static unsigned long targetTime = 0L;
		static int currentLedNo = 0;
		static int direction = 1;
		
		bool init = true;

		if (init) {				// run this section once
			init = false;
			targetTime = millis() + initialDelay;
		}
		if (millis() >= targetTime) {
			//raysLedController.clearLedData();
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
			//raysLedController.showLeds();
			targetTime = calcDelay(currentLedNo) + initialDelay;
			return 1;
		}
		return 0;
	};
};

// global namespace
//
//


void raySkyBalls(bool init = false) {

	CLEDController& raysLedController = FastLED.addLeds<LED_TYPE, RAYS_DATA_PIN, COLOR_ORDER>(rayLeds, cRayLedsCount);

	int refresh = 0;
	SkyBall redBall = SkyBall(cRayLedsCount, 10, 100);
	refresh += redBall.showPattern();
};

#endif

