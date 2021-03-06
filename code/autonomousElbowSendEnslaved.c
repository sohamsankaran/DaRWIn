////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                    Nunchuck Send 0.3
//                                    Measures Pitch, Yaw, Roll
//                                    Reminder: Add Gyro Code to v0.4
//                                    Soham Sankaran, October 20, 1540hrs
////////////////////////////////////////////////////////////////////////////////////////////////////////


#pragma platform(NXT)

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

ubyte nMM[4];


ubyte elbowdat[8];
ubyte motordat[2];

task sendMessages();
void checkBTLinkConnected();




////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                        Main Task
//
////////////////////////////////////////////////////////////////////////////////////////////////////////

task main()
{
  cCmdMessageRead(nMM, 4, mailbox1);


  while(true){

  elbowdat[0] = (nMM[0]*-1); //elbow1 right-left
  elbowdat[1] = (nMM[1]*-1); //elbow1 up-down
  elbowdat[5] = (nMM[2]*-1); //elbow2 right-left
  elbowdat[6] = (nMM[3]*-1); //elbow2 up-down



	checkBTLinkConnected();
	eraseDisplay();
	bNxtLCDStatusDisplay = true; // Enable top status line display

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
	const int kMinTimeBetweenMsg = 50;
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

	  cCmdMessageWriteToBluetooth(3,elbowdat,8,mailbox1);
	  wait1Msec(1);
	  cCmdMessageWriteToBluetooth(1,motordat,2,mailbox1);
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
