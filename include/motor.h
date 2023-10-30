#pragma once

#include <Arduino.h>

class Motor
{
public:
    enum eSpeed : uint8_t
    {
        STOPED_SPEED = 0,
        SLOW_SPEED = UINT8_MAX / 5,
        MID_SPEED = UINT8_MAX / 4,
        HIGH_SPEED = UINT8_MAX / 2,
        FAST_SPEED = UINT8_MAX,
    };

    enum eWhatWheel
    {
        NO_WHEEL = 0,
        RIGHT_WHEEL,
        LEFT_WHEEL,
    };

    enum eWhatDirection
    {
        IDLE = 0,
        FOWARD,
        BACKWARD,
    };

    Motor(/* args */);
    ~Motor();

    void stopWheel(eWhatWheel eWheel);
    void fullStop();
    void turnWheel(eWhatWheel eWheel, eWhatDirection eDirection, uint8_t speed);
    void brake();

private:
    const uint8_t IN1_A = 19;
    const uint8_t IN2_A = 18;
    const uint8_t IN1_B = 17;
    const uint8_t IN2_B = 16;

    typedef struct
    {
        uint8_t pin1;
        uint8_t pin2;
        uint8_t speed;
        eWhatDirection direction;
    } sWheel;

    sWheel mRightWheel;
    sWheel mLeftWheel;

    void initWheel(sWheel *pWheel, uint8_t pin1, uint8_t pin2);
    sWheel *getWheelFromEnum(eWhatWheel eWheel);
    eWhatDirection getOpositeWheelDirection(eWhatWheel eWheel);
    void commitWheelData(sWheel *pWheel);
};