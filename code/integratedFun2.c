////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Nunchuck Send 0.5
//                                    Measures Pitch, Yaw, Roll
//
//
////////////////////////////////////////////////////////////////////////////////////////////////////////



#pragma platform(NXT)
#pragma config(Sensor, S3,     LFTGYROUP,              sensorLowSpeed)
#pragma config(Sensor, S4,     RGTGYROUP,              sensorLowSpeed)

//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
#include "drivers/HTGYRO-driver.h"

long nElapsedTime = 0;
long nNearEndSent = 0;
long nNearEndRead = 0;
int  nFarEndSent  = 0;
int  nFarEndRead  = 0;
long nSendBusy    = 0;

int  nMessage  = 0;
long nRcxNoMsg = 0;
long nReadOutOfSequence  = 0;  // Out Of Sequence

long nMsgXmit     = 0;


byte CMDNunchukInit[] = {0x03, 0xA4, 0x40, 0x00};
byte CMDNunchukWrite[] = {0x02, 0xA4, 0x00};
byte CMDNunchukRead[] = {0x01, 0xA4};

byte outbuf[6];
int outbuf1[6];   //ubyte workaround for ROBOTC

int chuck1val[5];
int chuck2val[3];
int buttonval[4];
ubyte chuck1dat[10];
ubyte buttondat[2];

long LftHeadingUp;
long LftAccumulatorUp;
long RgtHeadingUp;
long RgtAccumulatorUp;

long LftSendUp;
long RgtSendUp;

int time;
int nTime;
ubyte LftSendFin[2];
ubyte RgtSendFin[2];
ubyte BothUp[2];






//  This function allows conversion of an unsigned byte to a signed int
//  This is a workaround for ROBOTC

// port is the NXT port, i2c_cmd is the nunchuk internal address register
// at i2c_cmd=0...5 are 6 Byte of sensor values
// at i2c_cmd=0x20 ... 0x2F  you get 16 Byte of calibration data

sub NunchukGetParamter(tSensors port, byte i2c_cmd)
{
  // Initialize the Nunchuk
  SensorType[port] = sensorI2CCustom;

  //Ask for 0 bytes
  sendI2CMsg(port, CMDNunchukInit[0], 0);

  while (nI2CStatus[port] == STAT_COMM_PENDING) ; // ROBOTC Wait for I2C bus to be ready

  //Write at 0x00: 6 Bytes of sensor values
  CMDNunchukWrite[2] =i2c_cmd;

  //Write Nunchuk register address
  sendI2CMsg(port, CMDNunchukWrite[0], 0);

  while (nI2CStatus[port] == STAT_COMM_PENDING) ; // ROBOTC Wait for I2C bus to be ready

  byte count = 6;
  //Ask for count bytes
  sendI2CMsg(port, CMDNunchukRead[0], count);

  while (nI2CStatus[port] == STAT_COMM_PENDING) ; // Wait for I2C bus to be ready

  if(nI2CBytesReady[port] == count){

    //Read data from buffer
    readI2CReply(port, outbuf[0], 6);

    for(int i=0; i<count; i++ ){
      outbuf1[i]=ubyteToInt(outbuf[i]);   //ubyte workaround for ROBOTC
      outbuf1[i]=(outbuf1[i]^0x17) + 0x17;
    }
  }
  else {
    // error
    memset(outbuf, 0, 0);
  }
}

//
// Function Prorotype Declarations
//
task sendMessages();
void checkBTLinkConnected();




////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Main Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  time = 0;
nTime = 0;
LftSendFin = 0;
RgtSendFin = 0;

  chuck1val[0] = 0;
  chuck1val[1] = 0;
  chuck1val[2] = 0;
  chuck1val[3] = 0;
  chuck1val[4] = 0;
  chuck2val[0] = 0;
  chuck2val[1] = 0;
  chuck2val[2] = 0;
  buttonval[0] = 0;
  buttonval[1] = 0;

  checkBTLinkConnected();


  LftAccumulatorUp=0;
  LftHeadingUp = 0;


  RgtAccumulatorUp=0;
  RgtHeadingUp = 0;


  time = 0;
  nTime = 0;
  LftSendFin = 0;
  RgtSendFin = 0;


  HTGYROstartCal(LFTGYROUP);
  HTGYROstartCal(RGTGYROUP);




  while(true){



  NunchukGetParamter(S1, 0x00);          //see comment for i2c_cmd

    if (sizeof(outbuf)==6)    {

      // analog stick
      eraseDisplay();
      nxtDrawCircle((outbuf1[0]-0x1E)/2, (outbuf1[1]-0x1E)/3, 3);
       nxtDisplayTextLine(2,"1 = %d", (outbuf1[2]-0x80));

       chuck1val[2] = ((outbuf1[1])-0x80);
       buttonval[0] =  (outbuf1 [5] & 0x01);
       buttonval[1] =  (outbuf1 [5] & 0x02);
       if(((outbuf1 [5]) & 0x01)==0){
       chuck1val[0] = ((outbuf1[2])-0x80);
       chuck1val[1] = ((outbuf1[3])-0x80);
       chuck1val[4] = ((outbuf1[4])-0x80);
     }

     else{
        //chuck1val[0] = 0;
        //chuck1val[1] = 0;
        //chuck1val[4] = 0;

     }

    }
    NunchukGetParamter(S2, 0x00);          //see comment for i2c_cmd

    if (sizeof(outbuf)==6)    {

      chuck1val[3]  = ((outbuf1[1])-0x80);
      buttonval[2] =  (outbuf1 [5] & 0x01);
      buttonval[3] =  (outbuf1 [5] & 0x02);
       if(((outbuf1 [5]) & 0x01)==0){
     chuck2val[0] = ((outbuf1[2])-0x80);
      chuck2val[1] = ((outbuf1[3])-0x80);
      chuck2val[2] = ((outbuf1[4])-0x80);
    }

     else{
        //chuck2val[0] = 0;
        //chuck2val[1] = 0;
        //chuck2val[2] = 0;

     }


    }

      wait1Msec(1);

    LftAccumulatorUp+=HTGYROreadRot(LFTGYROUP);
    RgtAccumulatorUp+=HTGYROreadRot(RGTGYROUP);

    if(time == 10){
      eraseDisplay();

      LftHeadingUp += LftAccumulatorUp;
      RgtHeadingUp += RgtAccumulatorUp;

      if(LftHeadingUp > 1778)
        LftHeadingUp = 1778;
      if(LftHeadingUp < 0)
        LftHeadingUp = 1;
      if(RgtHeadingUp < -1778)
        RgtHeadingUp = -1778;
      if(RgtHeadingUp > 0)
        RgtHeadingUp = -1;

      LftSendUp = (LftHeadingUp*0.009);
      RgtSendUp = (RgtHeadingUp*0.009);
      RgtSendUp = 0-RgtSendUp;

      if(LftSendUp <= 16 && LftSendUp >= 0)
        LftSendFin[0] = LftSendUp;
      if(RgtSendUp <= 16 && RgtSendUp >= 0)
        RgtSendFin[0] = RgtSendUp;

      /*if(nTime == 10){
        cCmdMessageWriteToBluetooth(1,LftSendFin,2,mailbox1);
    	  wait1Msec(1);
  	    cCmdMessageWriteToBluetooth(2,RgtSendFin,2,mailbox1);
        nTime = 0;
      }*/

      BothUp[0] = RgtSendFin[0];
      BothUp[1] = LftSendFin[0];



      nxtDisplayTextLine(1,"LSF = %4d, %4d",LftSendFin[0],LftSendFin[1]);
      nxtDisplayTextLine(2,"RSF = %4d, %4d",RgtSendFin[0],RgtSendFin[1]);
      nxtDisplayTextLine(3,"Press [] to reset");

      LftAccumulatorUp = 0;
      RgtAccumulatorUp = 0;

      time = 0;
      ++nTime;

    }
    if(nNxtButtonPressed == kEnterButton) {

      LftHeadingUp = 0;
      HTGYROstartCal(LFTGYROUP);


      RgtHeadingUp = 0;
      HTGYROstartCal(RGTGYROUP);

    }
    ++time;
	checkBTLinkConnected();
	eraseDisplay();
	bNxtLCDStatusDisplay = true; // Enable top status line display
	chuck1dat[0] = chuck1val[0]+100;
chuck1dat[1] = chuck1val[1]+100;
chuck1dat[4] = chuck1val[4]+100;
chuck1dat[2] = chuck1val[2]+100;
chuck1dat[3] = chuck1val[3]+100;
chuck1dat[5] = chuck2val[0]+100;
chuck1dat[6] = chuck2val[1]+100;
chuck1dat[7] = chuck2val[2]+100;
chuck1dat[8] = BothUp[0];
chuck1dat[9] = BothUp[1];
buttondat[0] = buttonval[0]+100;
buttondat[1] = buttonval[1]+100;
	StartTask(sendMessages);
	wait1Msec(1);

	//return;
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
//                                        Send Messages Task
////////////////////////////////////////////////////////////////////////////////////////////////////////

task sendMessages()
{
	const int kMinTimeBetweenMsg = 1;
	long nInterMsgTime;
	static long nLastSendTime = 0;

	while (true)
	{
		//
		// Delay between messages.
		//
		if ((nPgmTime - nLastSendTime) < kMinTimeBetweenMsg)
		{
			wait1Msec(6);
			continue;
		}

		if (bBTBusy)
		{
			++nSendBusy;
			wait1Msec(5);
			continue;
		}




	  ++nNearEndSent;
		++nMsgXmit;
		//if (nMsgXmit == 0)
			nMsgXmit = 1; // Don't send illegal value

	  cCmdMessageWriteToBluetooth(3,chuck1dat,10,mailbox1);
	  wait1Msec(1);
	  cCmdMessageWriteToBluetooth(1,buttondat,2,mailbox1);
	  wait1Msec(1);
	  cCmdMessageWriteToBluetooth(2,BothUp,2,mailbox1);
    wait1Msec(1);

	  nLastSendTime = nPgmTime;
	}
	return;
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
