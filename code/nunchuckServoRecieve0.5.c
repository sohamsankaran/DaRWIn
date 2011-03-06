#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop)
#pragma config(Servo,  srvo_S1_C2_1,    ,                     tServoNormal)
#pragma config(Servo,  srvo_S1_C2_2,    ,                     tServoNormal)
#pragma config(Servo,  srvo_S1_C2_5,    ,                     tServoNormal)
#pragma config(Servo,  srvo_S1_C2_6,    ,                     tServoNormal)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                chuckrec-for servo
////////////////////////////////////////////////////////////////////////////////////////////////////////







ubyte nMessage[8];




//
// Function Prorotype Declarations
//
int ubyteToInt(ubyte _byte) {
  int _ret = 0;
_ret = (_byte & 0x80) ? (_byte & 0x7F) + 0x80 : _byte;
  return _ret;
}

void checkBTLinkConnected();
void readMessages();


////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Main Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  while(true){
	//
	// Test Ability to Turn Bluetooth On or Off
	//
	checkBTLinkConnected();
	eraseDisplay();
	bNxtLCDStatusDisplay = true; // Enable top status line display


	readMessages();
	wait1Msec(100);
	return;
}
}




////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Receive Messages
////////////////////////////////////////////////////////////////////////////////////////////////////////

void readMessages()
{


	while (true)
	{
	  cCmdMessageRead(nMessage, 8, mailbox1);

	  int Axis1 = nMessage[0]-100;
	  int Axis2 = nMessage[1]-100;
	  int Axis3 = nMessage[4]-100;
	  int Axis4 = nMessage[5]-100;
	  int Axis5 = nMessage[6]-100;
	  int Axis6 = nMessage[7]-100;

	  nxtDisplayTextLine(2,"1 = %d", Axis3);


	     Axis1 = Axis1+55;
	     Axis1 = Axis1*2.3181818181818181818181818181818;
	     Axis1 = Axis1-127.5;


	    Axis2 = Axis2+55;
	    Axis2 = Axis2*2.3181818181818181818181818181818;
	    Axis2 = 255-Axis2;

	    Axis3 = Axis3+55;
	    Axis3 = Axis3*2.3181818181818181818181818181818;

	    Axis4 = Axis4+55;
	    Axis4 = Axis4*2.3181818181818181818181818181818;
	    Axis4 = Axis4-127.5;


	    Axis5 = Axis5+55;
	    Axis5 = Axis5*2.3181818181818181818181818181818;
	    Axis5 = 255-Axis5;

	    Axis6 = Axis6+55;
	    Axis6 = Axis6*2.3181818181818181818181818181818;




    //nxtDisplayTextLine(2,"1 = %d", Axis1);

    servo[servo1] = Axis1;
    servo[servo2] = Axis2;
    servo[servo5] = Axis4;
    servo[servo6] = Axis5;
    //servo[srvo_S1_C2_3] = LftMUp;
    //servo[srvo_S1_C2_4] = LftMRnd;

    }


		}



////////////////////////////////////////////////////////////////////////////////////////////////////////

void checkBTLinkConnected()
{
	if (nBTCurrentStreamIndex >= 0)
	  return;

	PlaySound(soundLowBuzz);
	PlaySound(soundLowBuzz);
	eraseDisplay();
	nxtDisplayCenteredTextLine(3, "BT not");
	nxtDisplayCenteredTextLine(4, "Connected");
	wait1Msec(3000);
	StopAllTasks();
}
