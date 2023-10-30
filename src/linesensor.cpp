#include "linesensor.h"

LineSensor::LineSensor(/* args */)
{
    pinMode(RIGHT_LINE_PIN, INPUT);
    pinMode(LEFT_LINE_PIN, INPUT);
    pinMode(S_LEFT_WHEEL_PIN, INPUT);
    pinMode(S_RIGHT_WHEEL_PIN, INPUT);
}

LineSensor::~LineSensor()
{
}

void LineSensor::updateSensorsReadings()
{
    irStates.rightLine = digitalRead(RIGHT_LINE_PIN);
    irStates.leftLine = digitalRead(LEFT_LINE_PIN);

    // printf("| Right: %d, Left: %d |\n", irStates.rightLine, irStates.leftLine);
}
