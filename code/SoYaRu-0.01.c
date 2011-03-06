#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Servo,  srvo_S1_C2_1,    servo1,                     tServoNormal)
#pragma config(Servo,  srvo_S1_C2_2,    servo2,                     tServoNormal)

/*--------------------------------------------------------------------------------------------------------*\
|*                                                                                                        *|
|*                                              - SoYaRu 1 -                                              *|
|*                                          ROBOTC on NXT + TETRIX                                        *|
|*                                                                                                        *|
|*                                                                                                        *|
|*                                        ROBOT CONFIGURATION                                             *|
|*       Note: Unless you write to them, all the servos on the board will reset to 127.5 or 0             *|
|*                                                                                                        *|
|*    MOTORS & SENSORS:                                                                                   *|
|*    [I/O Port]              [Name]              [Type]              [Description]                       *|
|*    Port 1                  none                TETRIX Controller   TETRIX                              *|
|*    Port 1 - Chan. 1       srvo_S1_C2_1         std. Servo          Arm Up-Down Servo                   *|
|*    Port 1 - Chan. 2       srvo_S1_C2_2         std. Servo          Arm Right-Left Servo                *|
|*    Port A                    motorA            NXT Motor           Elbow Up-Down Motor                 *|
|*    Port B                    motorB            NXT Motor           Elbow Right-Left Motor              *|
\*---------------------------------------------------------------------------------------------------4246-*/
task main()
{
  while(true){
  int sspeed = 10;                        // Create int 'sspeed' to the be Servo Change Rate.

   //begin initial setup code(do not change)

  servoChangeRate[servo1] = sspeed;
  servoChangeRate[servo2] = sspeed;

  servo[servo1] = 81;              //reset the servo on channel 1 to the starting position
  servo[servo2] = 80;              //reset the servo on channel 2 to the starting position

  nMotorEncoder[motorA]=0;              //reset motorA's encoder
  nMotorEncoder[motorB]=0;              //reset motorB's encoder

  //end initial setup code
}


}
