#include "motor.h"

Motor::Motor(/* args */)
{
    initWheel(&mRightWheel, IN1_A, IN2_A);
    initWheel(&mLeftWheel, IN1_B, IN2_B);

    pinMode(IN1_A, OUTPUT);
    pinMode(IN2_A, OUTPUT);
    pinMode(IN1_B, OUTPUT);
    pinMode(IN2_B, OUTPUT);
}

Motor::~Motor()
{
}

void Motor::stopWheel(eWhatWheel eWheel)
{
    sWheel *pWheel = getWheelFromEnum(eWheel);

    pWheel->direction = IDLE;
    pWheel->speed = 0;

    commitWheelData(pWheel);
}

void Motor::fullStop()
{
    stopWheel(RIGHT_WHEEL);
    stopWheel(LEFT_WHEEL);
}

void Motor::turnWheel(eWhatWheel eWheel, eWhatDirection eDirection, uint8_t speed)
{
    sWheel *pWheel = getWheelFromEnum(eWheel);

    pWheel->direction = eDirection;
    pWheel->speed = speed;

    commitWheelData(pWheel);
}

void Motor::brake()
{
    turnWheel(RIGHT_WHEEL, getOpositeWheelDirection(RIGHT_WHEEL), mRightWheel.speed);
    turnWheel(LEFT_WHEEL, getOpositeWheelDirection(LEFT_WHEEL), mLeftWheel.speed);
}

void Motor::initWheel(sWheel *pWheel, uint8_t pin1, uint8_t pin2)
{
    pWheel->pin1 = pin1;
    pWheel->pin2 = pin2;
    pWheel->speed = 0;
    pWheel->direction = IDLE;
}

Motor::sWheel *Motor::getWheelFromEnum(eWhatWheel eWheel)
{
    switch (eWheel)
    {
    case RIGHT_WHEEL:
        return &mRightWheel;
        break;
    case LEFT_WHEEL:
        return &mLeftWheel;
        break;
    default:
        return nullptr;
        break;
    }
}

Motor::eWhatDirection Motor::getOpositeWheelDirection(eWhatWheel eWheel)
{
    sWheel *pWheel = getWheelFromEnum(eWheel);

    if (pWheel->direction == IDLE)
        return IDLE;

    return (pWheel->direction == FOWARD) ? BACKWARD : FOWARD;
}

void Motor::commitWheelData(sWheel *pWheel)
{
    uint8_t pwmPin;
    uint8_t pullDownPin;

    switch (pWheel->direction)
    {
    case FOWARD:
        pwmPin = pWheel->pin1;
        pullDownPin = pWheel->pin2;
        break;
    case BACKWARD:
        pwmPin = pWheel->pin2;
        pullDownPin = pWheel->pin1;
        break;
    case IDLE:
    default:
        pwmPin = pWheel->pin1;
        pullDownPin = pWheel->pin2;
        pWheel->speed = 0;
        break;
    }

    analogWrite(pullDownPin, STOPED_SPEED);
    if (pWheel->speed > 0 && pWheel->speed <= UINT8_MAX)
        analogWrite(pwmPin, pWheel->speed);
    else
        analogWrite(pwmPin, STOPED_SPEED);

    // Não remover
    printf("\n| PwmPin: %d, Speed: %d, Direction: %d |\n",
           pwmPin, pWheel->speed, pWheel->direction);
}
