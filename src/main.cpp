#include <Arduino.h>

#include "motor.h"
#include "linesensor.h"

Motor motor;
LineSensor lineSensor;

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  lineSensor.updateSensorsReadings();

  if (lineSensor.irStates.rightLine && lineSensor.irStates.leftLine) // Fica Parado
    motor.fullStop();
  else if (!lineSensor.irStates.rightLine && !lineSensor.irStates.leftLine) // Vai p Frente
  {
    motor.turnWheel(Motor::RIGHT_WHEEL, Motor::FOWARD, Motor::SLOW_SPEED);
    motor.turnWheel(Motor::LEFT_WHEEL, Motor::FOWARD, Motor::SLOW_SPEED);
  }
  else if (lineSensor.irStates.rightLine) // Vai p Esquerda
  {
    motor.turnWheel(Motor::LEFT_WHEEL, Motor::FOWARD, Motor::MID_SPEED);
    motor.turnWheel(Motor::RIGHT_WHEEL, Motor::BACKWARD, Motor::MID_SPEED);
  }
  else if (lineSensor.irStates.leftLine) // Vai p Direita
  {
    motor.turnWheel(Motor::RIGHT_WHEEL, Motor::FOWARD, Motor::MID_SPEED);
    motor.turnWheel(Motor::LEFT_WHEEL, Motor::BACKWARD, Motor::MID_SPEED);
  }
  else // Fica Parado
    motor.fullStop();
}