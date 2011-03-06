#pragma config(Sensor, S1,     LFTGYROUP,              sensorLowSpeed)
#pragma config(Sensor, S2,     LFTGYROROUND,              sensorLowSpeed)
#pragma config(Sensor, S3,     RGTGYROUP,              sensorLowSpeed)
#pragma config(Sensor, S4,     RGTGYROROUND,              sensorLowSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "drivers/HTGYRO-driver.h"

long LftHeadingUp;
long LftAccumulatorUp;
long RgtHeadingUp;
long RgtAccumulatorUp;

long LftHeadingRound;
long LftAccumulatorRound;
long RgtHeadingRound;
long RgtAccumulatorRound;

long LftSendUp;
long LftSendRound;
long RgtSendUp;
long RgtSendRound;

int time;
int nTime;
ubyte LftSendFin[2];
ubyte RgtSendFin[2];

void checkBTLinkConnected();

task main (){
  checkBTLinkConnected();


  LftAccumulatorUp=0;
  LftHeadingUp = 0;
  LftAccumulatorRound=0;
  LftHeadingRound = 0;

  RgtAccumulatorUp=0;
  RgtHeadingUp = 0;
  RgtAccumulatorRound=0;
  RgtHeadingRound = 0;


  time = 0;
  nTime = 0;
  LftSendFin = 0;
  RgtSendFin = 0;


  HTGYROstartCal(LFTGYROUP);
  HTGYROstartCal(LFTGYROROUND);
  HTGYROstartCal(RGTGYROUP);
  HTGYROstartCal(RGTGYROROUND);

  while(true){
    wait1Msec(1);

    LftAccumulatorUp+=HTGYROreadRot(LFTGYROUP);
    LftAccumulatorRound+=HTGYROreadRot(LFTGYROROUND);
    RgtAccumulatorUp+=HTGYROreadRot(RGTGYROUP);
    RgtAccumulatorRound+=HTGYROreadRot(RGTGYROROUND);

    if(time == 10){
      eraseDisplay();

      LftHeadingUp += LftAccumulatorUp*1;
      LftHeadingRound += LftAccumulatorRound*1;
      RgtHeadingUp += RgtAccumulatorUp*1;
      RgtHeadingRound += RgtAccumulatorRound*1;

      /*LftSendUp = 16-(LftHeadingUp*0.0001);
      LftSendRound = (LftHeadingRound*0.0001)+8;
      RgtSendUp = -(RgtHeadingUp*0.0001);
      RgtSendRound = (RgtHeadingRound*0.0001)+8;
      */
      LftSendUp = (LftHeadingUp*0.0001)+1;
      LftSendRound = (LftHeadingRound*0.0001)+6;
      RgtSendUp = (RgtHeadingUp*0.0001)+1;
      RgtSendRound = (RgtHeadingRound*0.0001)+6;

      if(LftSendUp <= 16 && LftSendUp > 0)
        LftSendFin[0] = LftSendUp;
      if(LftSendRound <= 16 && LftSendRound > 0)
        LftSendFin[1] = LftSendRound;
      if(RgtSendUp <= 16 && RgtSendUp > 0)
        RgtSendFin[0] = RgtSendUp;
      if(RgtSendRound <= 16 && RgtSendRound > 0)
        RgtSendFin[1] = RgtSendRound;

      //LftSendFin = (LftSendUp*100)+ LftSendRound;
      //RgtSendFin = (RgtSendUp*100)+ RgtSendRound;

      if(nTime == 10){
        cCmdMessageWriteToBluetooth(1,LftSendFin,2,mailbox1);
    	  wait1Msec(1);
  	    cCmdMessageWriteToBluetooth(2,RgtSendFin,2,mailbox1);
        //sendMessageWithParm(LftSendFin, RgtSendFin);
        nTime = 0;
      }

      nxtDisplayTextLine(1,"LSF = %4d, %4d",LftSendFin[0],LftSendFin[1]);
      nxtDisplayTextLine(2,"RSF = %4d, %4d",RgtSendFin[0],RgtSendFin[1]);
      nxtDisplayTextLine(3,"Press [] to reset");

      LftAccumulatorUp = 0;
      LftAccumulatorRound = 0;
      RgtAccumulatorUp = 0;
      RgtAccumulatorRound = 0;

      time = 0;
      ++nTime;

    }
    if(nNxtButtonPressed == kEnterButton) {

      LftHeadingUp = 0;
      HTGYROstartCal(LFTGYROUP);

      LftHeadingRound = 0;
      HTGYROstartCal(LFTGYROROUND);

      RgtHeadingUp = 0;
      HTGYROstartCal(RGTGYROUP);

      RgtHeadingRound = 0;
      HTGYROstartCal(RGTGYROROUND);
    }
    ++time;
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
