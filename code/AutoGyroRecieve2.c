#pragma config(Motor,  motorA,          RND,           tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          UP,            tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#define RANGE 3
int distUp;
int distRnd;
ubyte Rec[2];
int fRec[2];

void checkBTLinkConnected();
task get;
int AbsMove(int MUp, int MRnd){
  int testRnd = 0;
  int testUp = 0;
  while(testUp==0 || testRnd==0){
    nxtDisplayTextLine(1,"UP = %d",nMotorEncoder[UP]);
    nxtDisplayTextLine(2,"RND = %d",nMotorEncoder[RND]);
    distUp = MUp-nMotorEncoder[UP];
    if(MUp <= nMotorEncoder[UP]-RANGE || MUp >= nMotorEncoder[UP]+RANGE){
     motor[UP] = distUp;
    }
    else{
      testUp = 1;
      motor[UP] = 0;
    }

    distRnd = MRnd-nMotorEncoder[RND];
    if(MRnd <= nMotorEncoder[RND]-RANGE || MRnd >= nMotorEncoder[RND]+RANGE){
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

task main(){
  checkBTLinkConnected();
  nMotorEncoder[UP] = 0;
  nMotorEncoder[RND] = 0;
  StartTask(get);
  while(true){
    fRec[0] = Rec[0]*10;
    fRec[1] = Rec[1]*10;
    nxtDisplayTextLine(3,"RUP = %d",fRec[0]);
    nxtDisplayTextLine(4,"RRND = %d",fRec[1]);
    AbsMove(fRec[0], fRec[1]);
  }
}

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

task get(){
  while(true){
    cCmdMessageRead(Rec, 2, mailbox1);
    nxtDisplayTextLine(5,"BUP = %d",Rec[0]);
    nxtDisplayTextLine(6,"BRND = %d",Rec[1]);
  }
}
