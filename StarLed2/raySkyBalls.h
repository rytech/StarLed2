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
			raysLedController.clearLedData();
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
			return 1;		// refresh ray leds
		}
		return 0;			// refresh not needed
	};
};


// global namespace
//
//

void raySkyBalls(bool init = false) {
	int refresh = 0;
	SkyBall redBall = SkyBall(HUE_RED, cRayLedsCount, 10, 75);
	SkyBall greenBall = SkyBall(HUE_GREEN, cRayLedsCount*3/4, 10, 75);
	SkyBall blueBall = SkyBall(HUE_BLUE, cRayLedsCount*2/3, 10, 75);

	//redBall.showPattern();
	//Serial.println("raySkyBalls in");
	while (true) {
		EVERY_N_SECONDS(10) {
			// stop the pattern after 10 seconds
			rayPattern = NULL;
			return;
		}

		refresh = redBall.showPattern();
		refresh += greenBall.showPattern();
		refresh += blueBall.showPattern();
		if (refresh) {
			//Serial.println("raySkyBalls 1");
			//raysLedController.showLeds();
			FastLED.show();
			refresh = 0;
	//Serial.println("raySkyBalls 2");
		}
	}
}


#endif

