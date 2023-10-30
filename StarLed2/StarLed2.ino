/*
 Name:		StarLed2.ino
 Created:	8/18/2023 9:28:21 PM
 Author:	rytec
*/

#include <iostream>
#include <vector>
#include <FastLED.h>
#include "Globals2.h"
#include "Tasks.h"
#include "raySkyBalls.h"
#include "starPatterns.h"
#include "rayPatterns.h"

void setup() {

    Serial.begin(115200);        // default 115200
    while (!Serial);

    //TaskHandle_t Task1; // create a task handle
    //xTaskCreatePinnedToCore(
    //    Task1code, // function to implement the task
    //    "Task1", // name of the task
    //    10000, // stack size in words
    //    NULL, // task input parameter
    //    0, // priority of the task
    //    &Task1, // task handle
    //    0); // core where the task should run
    xTaskCreatePinnedToCore(starTaskCode, "StarTask", 10000, NULL, 2, &starTask, 1);
    xTaskCreatePinnedToCore(rayTaskCode, "RayTask", 10000, NULL, 2, &rayTask, 1);
    
    createRunList();
    vTaskDelay(3000);
    FastLED.clear(true);
    nextPattern();

    Serial.println("Setup out");
}

void loop() {
    while (true) {
        vTaskDelay(200);
        //Serial.println("loop started");
        while (starPattern) {
            vTaskDelay(100);
        }
        rayPattern = NULL;
        transition();
        //Serial.println("loop out");
    }
}


void transition() {
    starPattern = NULL;
    rayPattern = NULL;

    //Serial.println("transition in");
    vTaskDelay(500);
    for (int i = 0; i < 150; i++) {
        fade_raw(starLeds, cStarLedsCount, 4);
        fade_raw(rayLeds, cRayLedsCount, 4);
        FastLED.show();
    }
    nextPattern();
}

uint8_t runItemNo = -1;
int patternRunTime = 0;

void nextPattern()
{
    //` Serial.println("nextPattern in");

    // add one to the current pattern number, and wrap around at the end
    runItemNo = (runItemNo + 1) % runList.size();  //ARRAY_SIZE(starPatterns);

    starPattern = runList[runItemNo].starPattern;
    rayPattern = runList[runItemNo].rayPattern;
    //patternRunTime = runList[runItemNo].runTime;
}

void createRunList() {
    runList.push_back(runItem{ colorWipe, rayTracer, 10});
    runList.push_back(runItem{ starBlend, rayTracer, 10});
    //runList.push_back(runItem{ starConfetti, raySkyBalls, 10});
    runList.push_back(runItem{ juggle, rayWhiteTracer, 10});
    runList.push_back(runItem{ theaterChaseRainbow, raySkyBalls, 10});
    runList.push_back(runItem{ starRainbow, rayTracer, 10});
    runList.push_back(runItem{ starShift, rayWhiteTracer, 10});
    runList.push_back(runItem{ starFinale, nullptr, 10});
}
