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

#endif

