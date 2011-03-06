ubyte GyroLft[2];
ubyte GyroRgt[2];
ubyte Nunchuck[8];

task sendMessages;
void change(int GLU,int GLR,int GRU,int GRR,int NLU,int NLR,int NRU,int NRR);
void checkBTLinkConnected();

task main(){
  checkBTLinkConnected();
  StartTask(sendMessages);
  change(23,0,23,0,100,120,100,80);
  wait1Msec(3000);
  change(23,20,23,0,0,0,100,80);
  wait1Msec(3000);
  change(23,0,23,0,100,120,100,80);
  wait1Msec(3000);
  change(23,0,23,20,100,120,0,0);
  wait1Msec(3000);
  change(23,0,23,0,100,120,100,80);
  wait1Msec(3000);
  change(23,20,23,0,0,0,100,120);
  wait1Msec(3000);
  change(23,0,23,0,100,120,100,80);
  wait1Msec(5000);
  change(0,0,0,0,0,0,0,0);
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
  	cCmdMessageWriteToBluetooth(3,Nunchuck,8,mailbox1);
    wait1Msec(1);
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

void change(int GLU,int GLR,int GRU,int GRR,int NLU,int NLR,int NRU,int NRR){
  GyroLft[0] = GLU;
  GyroLft[1] = GLR;
  GyroRgt[0] = GRU;
  GyroRgt[1] = GRR;
  Nunchuck[1] = NLU;
  Nunchuck[0] = NLR;
  Nunchuck[6] = NRU;
  Nunchuck[5] = NRR;
}
