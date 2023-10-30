#pragma once

#include <Arduino.h>

class LineSensor
{
private:
    const uint8_t RIGHT_LINE_PIN = 36;
    const uint8_t LEFT_LINE_PIN = 35;

    const uint8_t S_LEFT_WHEEL_PIN = 33;
    const uint8_t S_RIGHT_WHEEL_PIN = 27;

public:
    typedef struct
    {
        bool rightLine;
        bool leftLine;
    } IRLedsStates;

    LineSensor(/* args */);
    ~LineSensor();

    IRLedsStates irStates = {false};

    void updateSensorsReadings();
};
