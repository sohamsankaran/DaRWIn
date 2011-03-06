#pragma config(Sensor, S2,     LFTGYROROUND,              sensorLowSpeed)
#pragma config(Sensor, S4,     RGTGYROROUND,              sensorLowSpeed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "drivers/HTGYRO-driver.h"
long LftHeadingRound;
long LftAccumulatorRound;
long RgtHeadingRound;
long RgtAccumulatorRound;

long LftSendRound;
long RgtSendRound;

int time;
int nTime;
ubyte LftSendFin[2];
ubyte RgtSendFin[2];

void checkBTLinkConnected();

task main (){
  //checkBTLinkConnected();

  LftAccumulatorRound=0;
  LftHeadingRound = 0;

  RgtAccumulatorRound=0;
  RgtHeadingRound = 0;


  time = 0;
  nTime = 0;
  LftSendFin = 0;
  RgtSendFin = 0;

  HTGYROstartCal(LFTGYROROUND);
  HTGYROstartCal(RGTGYROROUND);

  while(true){
    wait1Msec(1);

    LftAccumulatorRound+=HTGYROreadRot(LFTGYROROUND);
    RgtAccumulatorRound+=HTGYROreadRot(RGTGYROROUND);

    if(time == 10){
      eraseDisplay();

      LftHeadingRound += LftAccumulatorRound;
      RgtHeadingRound += RgtAccumulatorRound;

      if(LftHeadingRound > 80000)
        LftHeadingRound = 80000;
      if(LftHeadingRound < -80000)
        LftHeadingRound = -80000;
      if(RgtHeadingRound < -80000)
        RgtHeadingRound = -80000;
      if(RgtHeadingRound > 80000)
        RgtHeadingRound = 80000;

      LftSendRound = (LftHeadingRound*0.0001)+8;
      RgtSendRound = (RgtHeadingRound*0.0001);
      RgtSendRound = 0-RgtSendRound+8;

      if(LftSendRound <= 16 && LftSendRound > 0)
        LftSendFin[1] = LftSendRound;

      if(RgtSendRound <= 16 && RgtSendRound > 0)
        RgtSendFin[1] = RgtSendRound;

      if(nTime == 10){
        cCmdMessageWriteToBluetooth(1,LftSendFin,2,mailbox1);
    	  wait1Msec(1);
  	    cCmdMessageWriteToBluetooth(2,RgtSendFin,2,mailbox1);
        nTime = 0;
      }

      nxtDisplayTextLine(1,"LSF = %4d, %4d",LftSendFin[0],LftSendFin[1]);
      nxtDisplayTextLine(2,"RSF = %4d, %4d",RgtSendFin[0],RgtSendFin[1]);
      nxtDisplayTextLine(3,"Press [] to reset");

      LftAccumulatorRound = 0;
      RgtAccumulatorRound = 0;

      time = 0;
      ++nTime;

    }
    if(nNxtButtonPressed == kEnterButton) {

      LftHeadingRound = 0;
      HTGYROstartCal(LFTGYROROUND);

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