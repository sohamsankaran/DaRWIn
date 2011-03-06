#pragma config(Hubs,  S1, HTMotor,  HTServo,  none,     none)
#pragma config(Motor,  motorA,          UP,            tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          RND,           tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorC,          STS,           tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C1_1,     motorD,        tmotorNormal, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     motorE,        tmotorNormal, openLoop, reversed)
#pragma config(Servo,  srvo_S1_C2_1,    ,                     tServoNormal)
#pragma config(Servo,  srvo_S1_C2_2,    ,                     tServoNormal)
#pragma config(Servo,  srvo_S1_C2_5,    ,                     tServoNormal)
#pragma config(Servo,  srvo_S1_C2_6,    ,                     tServoNormal)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                chuckrec-for servo
////////////////////////////////////////////////////////////////////////////////////////////////////////


int distUp;
int distRnd;
int Rec[2];
int LRec[2];
bool new;
ubyte nMessage[17];


int AbsMove(int MUp, int MRnd){
  int testRnd = 0;
  int testUp = 0;
  while(testUp==0 || testRnd==0){
    if(new){
      break;
    }
    nxtDisplayTextLine(1,"UP = %d",nMotorEncoder[UP]);
    nxtDisplayTextLine(2,"RND = %d",nMotorEncoder[RND]);
    distUp = MUp-nMotorEncoder[UP];
    //if(MUp <= nMotorEncoder[UP]-RANGE || MUp >= nMotorEncoder[UP]+RANGE){
    if(MUp != nMotorEncoder[UP]){
     motor[UP] = distUp;
    }
    else{
      testUp = 1;
      motor[UP] = 0;
    }

    distRnd = MRnd-nMotorEncoder[RND];
    //if(MRnd <= nMotorEncoder[RND]-RANGE || MRnd >= nMotorEncoder[RND]+RANGE){
    if(MRnd != nMotorEncoder[RND]){
      motor[RND] = distRnd;
    }
    else{
      testRnd = 1;
      motor[RND] = 0;
    }
  }
  motor[UP]= 0;
  motor[RND]= 0;
  return 0;
}




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
task head;

////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Main Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  StartTask(head);
  nMotorEncoder[UP] = 0;
  nMotorEncoder[RND] = 0;
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

task head(){
  while(true){
    switch(nMessage[16]){
    case 1:
      motor[STS] = 100;
      wait1Msec(500);
      motor[STS] = -100;
      wait1Msec(500);
      motor[STS] = 0;
      break;
    default:
      motor[STS] = 0;
      break;
    }
    AbsMove(Rec[0], Rec[1]);
  }
}



////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Receive Messages
////////////////////////////////////////////////////////////////////////////////////////////////////////

void readMessages()
{

  new = false;
  LRec[0] = 0;
  LRec[1] = 0;

	while (true)
	{
	  cCmdMessageRead(nMessage, 17, mailbox1);

	  if(LRec[0]!= nMessage[14] || LRec[1]!= nMessage[15]){
      new = true;
      LRec[0] = nMessage[14];
      LRec[1] = nMessage[15];
      wait1Msec(10);
    }
    else{
      new = false;
    }

    Rec[0] = nMessage[14]*40;
    Rec[1] = (nMessage[15]-10)*40;

	  int Axis1 = nMessage[0]-100;
	  int Axis2 = nMessage[1]-100;
	  int Axis3 = nMessage[4]-100;
	  int Axis4 = nMessage[5]-100;
	  int Axis5 = nMessage[6]-100;
	  int Axis6 = nMessage[7]-100;

	  nxtDisplayTextLine(2,"1 = %d", nMessage[11]);


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
    servo[servo2] = (Axis2-(15.9375*nMessage[8]));
    servo[servo5] = Axis4;
    servo[servo6] = (Axis5-(15.9375*nMessage[9]));
    //servo[srvo_S1_C2_3] = LftMUp;
    //servo[srvo_S1_C2_4] = LftMRnd;

    if(nMessage[10] == 100){
      motor[motorD] = 20;
    }
    else if(nMessage[11] == 100){
       motor[motorD] = -20;
    }
    else{
      motor[motorD] = 0;
    }

    if(nMessage[12] == 100){
      motor[motorE] = 20;
    }
    else if(nMessage[13] == 100){
       motor[motorE] = -20;
    }
    else{
      motor[motorE] = 0;
    }

    /*Rec[0] = nMessage[14]*40;
    Rec[1] = nMessage[15]*40;

    AbsMove(Rec[0], Rec[1]);*/

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