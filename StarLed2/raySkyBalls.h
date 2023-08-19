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

	SkyBall() { 0, 0, 0, CHSV(HUE_RED, 0xFF, 0xFF); };


	SkyBall(int count, int initial, int final) :
		ledsCount{ count }, initialDelay{ initial }, finalDelay{ final }
	{};

	unsigned long calcDelay(int ledNo) {
		float m = (float)((finalDelay - initialDelay) / ((float)(ledNo * ledNo)) + initialDelay);
		return (unsigned long)m;
	}
};

// global namespace
//
//

SkyBall redBall = SkyBall(cRayLedsCount, 10, 100);

void raySkyBalls(bool init = false) {

	static SkyBall& ball = redBall;

	if (init) {
		return;
	}
};

#endif

