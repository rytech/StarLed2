/*
 Name:		StarLed2.ino
 Created:	8/18/2023 9:28:21 PM
 Author:	rytec
*/

#include <FastLED.h>
#include "Globals2.h"
#include <vector>
//#include "raySkyBalls.h"
//#include "Meteor.h"
#include "starRainbow.h"
#include "rayTracer.h"
#include "Tasks.h"

void setup() {

    Serial.begin(56000);
    while (!Serial);
    //delay(3000);
    Serial.println("debug message");

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
    
    delay(3000);
    //vTaskDelay(3000 / portTICK_PERIOD_MS);

    FastLED.clear(true);


    //starPattern = starPatterns[0];
    //starPattern(true);
    //rayPattern(true);
    // 

    //rayPattern = rayMeteor;

    //D(Serial.printf("This is a debug message\n"));
    //Serial.println("This is a debug message");
    //Serial.printf("This is a debug message using printf\n");

    nextPattern();

    Serial.println("Setup out");
    //FastLED.showColor(CRGB(0X00, 0X00, 0xFF));
}

void loop() {
    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        Serial.println("loop started");
        while (starPattern) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        rayPattern = NULL;

        transition();
        //Serial.println("loop out");
    }
}


void transition() {
    starPattern = NULL;
    rayPattern = NULL;

    Serial.println("transition in");
    delay(500);
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
    Serial.println("nextPattern in");

    // add one to the current pattern number, and wrap around at the end
    runItemNo = (runItemNo + 1) % runList.size();  //ARRAY_SIZE(starPatterns);

    starPattern = runList[runItemNo].starPattern;
    rayPattern = runList[runItemNo].rayPattern;
    patternRunTime = runList[runItemNo].runTime;
}

