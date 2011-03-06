// DaRWIn Library 0.1
// Author : Soham Sankaran, the 4th of October, 2010.
// Functions:
// 1] ServoFreeze - to freeze servos in position - input : int servoNum, int servoAngle
// 2] MotorTurnAngle - to turn NXT Motors to an angle at a speed - input : int motorNum, int angle, int mspeed
// 3] ResetServos - to reset all the servos to their start position - input : none
// 4] ResetToNamaste -  to reset all the servos to the Namaste position - input : none
// Expected Configuration:
/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port 1                  none                TETRIX Controller   TETRIX                              *|
|*    Port 1 - Chan. 1       srvo_S1_C2_1         std. Servo          Arm Up-Down Servo                   *|
|*    Port 1 - Chan. 2       srvo_S1_C2_2         std. Servo          Arm Right-Left Servo                *|
|*    Port A                    motorA            NXT Motor           Elbow Up-Down Motor                 *|
|*    Port B                    motorB            NXT Motor           Elbow Right-Left Motor              *|
\*---------------------------------------------------------------------------------------------------4246-*/

void ServoFreeze(int servoNum, int servoAngle){
  switch (servoNum)
  {
  case 1:
    servo[srvo_S1_C2_1] = servoAngle;
    break;

  case 2:
    servo[srvo_S1_C2_2] = servoAngle;
    break;

  case 3:
    servo[srvo_S1_C2_3] = servoAngle;
    break;

  case 4:
    servo[srvo_S1_C2_4] = servoAngle;
    break;

  case 5:
    servo[srvo_S1_C2_5] = servoAngle;
    break;

  case 6:
    servo[srvo_S1_C2_6] = servoAngle;
    break;

  default:
    break;

  }
}

void MotorTurnAngle(int motorNum, int angle, int mspeed)
{

  switch (motorNum)
  {
  case 1:
    nMotorEncoderTarget[motorA] = nMotorEncoder[motorA]+angle;
    motor[motorA] = mspeed; //turn both motors on at 30 percent power
  while (nMotorRunState[motorA] != runStateIdle) //while the encoder wheel turns
  {
    // This condition waits for motor A to come to an idle position. The motor stops
    // and then jumps out of the loop
  }
  motor[motorA] = 0;

    break;

  case 2:
    nMotorEncoderTarget[motorB] = nMotorEncoder[motorB]+angle;
    motor[motorB] = mspeed;
  while (nMotorRunState[motorB] != runStateIdle) //while the encoder wheel turns
  {
  }
   motor[motorB] = 0;
    break;

  case 3:
    nMotorEncoderTarget[motorC] = nMotorEncoder[motorC]+angle;
    motor[motorC] = mspeed;
  while (nMotorRunState[motorC] != runStateIdle) //while the encoder wheel turns
  {
  }
  motor[motorC] = 0;
    break;

  default:
    break;

  }
}

void ResetServos(){
   servo[srvo_S1_C2_1] = 127.5;              //reset the servo on channel 1 to the starting position
   servo[srvo_S1_C2_2] = 127.5;              //reset the servo on channel 2 to the starting position
 }

 void ResetToNamaste(){
  servo[srvo_S1_C2_1] = 0;
  servo[srvo_S1_C2_2] = 100;
  wait1Msec(2000);
  servo[srvo_S1_C2_1] = 128;
  wait1Msec(2000);
 // MotorTurnAngle(1,100,50);
  wait1Msec(2000);             //reset the servo on channel 2 to the starting position

}
