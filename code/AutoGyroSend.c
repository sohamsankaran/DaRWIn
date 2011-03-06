ubyte GyroLft[2];
ubyte GyroRgt[2];
ubyte Nunchuck[4];

task sendMessages;
void checkBTLinkConnected();

task main(){
  checkBTLinkConnected();
  StartTask(sendMessages);
  GyroLft[0]= 23;
  GyroLft[1]= 10;
  wait1Msec(5000);
  for(int i=0; i <= 5; ++i){
  GyroLft[0]= 50;
  GyroLft[1]= 18;
  wait1Msec(2000);
  GyroLft[0]= 23;
  GyroLft[1]= 18;
  wait1Msec(2000);
  }
  GyroLft[0]= 50;
  GyroLft[1]= 18;
  wait1Msec(5000);
  GyroLft[0]= 0;
  GyroLft[1]= 0;
  wait1Msec(5000);
}

task sendMessages()
{
  while(true){
    nxtDisplayTextLine(1,"RUP = %d",GyroLft[0]);
    nxtDisplayTextLine(2,"RRND = %d",GyroLft[1]);

    cCmdMessageWriteToBluetooth(1,GyroLft,2,mailbox1);
    wait1Msec(1);
  	cCmdMessageWriteToBluetooth(2,GyroRgt,2,mailbox1);
    wait1Msec(1);
  	cCmdMessageWriteToBluetooth(3,Nunchuck,4,mailbox1);
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
