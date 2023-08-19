//#include <FastLED.h>



#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND  50

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

const uint8_t cStarLedsCount = 80;
const uint8_t cRayLedsCount = 70;

const uint8_t STAR_DATA_PIN = 4;
const uint8_t RAYS_DATA_PIN = 5;

// Define the array of leds
CRGB starLeds[cStarLedsCount];
CRGB rayLeds[cRayLedsCount];
CRGB starTransLeds[cStarLedsCount];
CHSV hsvStarLeds[cStarLedsCount];

CEveryNSeconds starTimer(20);

//void transition(bool init);
//void starRainbow(bool init);
//void starDotty(bool init);
//void rayTracer(bool init);
//void starSingleColor(bool init);
//void confetti(bool bInit);
//void starShift(bool init);
//void Fire2012(bool init);
//void starPulse(bool init);
//void lj_starBlend(bool init);

typedef void (*ptrRayPattern)(bool);
ptrRayPattern rayPattern = nullptr; // rayTracer;

typedef void (*ptrStarPattern)(bool);
ptrStarPattern starPattern;

typedef void (*starPatternList[])(bool);
starPatternList starPatterns = {
    //starDotty, transition, 
    //starRainbow, transition,
    //starSingleColor, transition, 
    //confetti, transition, 
    //starPulse, transition, 
    //lj_starBlend, transition

};

uint8_t starPatternNo = 0;

