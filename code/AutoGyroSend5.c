ubyte GyroUp[3];
ubyte GyroRnd[3];
ubyte Nunchuck[14];

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
  PlaySound(soundDownwardTones);
  change(23,20,23,20,100,200,100,0);
  wait1Msec(5000);
  for(int i = 0; i<=3; ++i){
    change(50,20,50,20,0,200,0,0);
    wait1Msec(2000);
    change(23,20,23,20,100,200,100,0);
    wait1Msec(2000);
  }

  change(0,0,0,0,0,0,0,0);
  wait1Msec(5000);
}





task sendMessages()
{
  while(true){
    nxtDisplayTextLine(1,"RUP = %d",GyroUp[0]);
    nxtDisplayTextLine(2,"RRND = %d",GyroUp[1]);

    cCmdMessageWriteToBluetooth(1,GyroUp,2,mailbox1);
    wait1Msec(1);
  	cCmdMessageWriteToBluetooth(2,GyroRnd,2,mailbox1);
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
  GyroUp[0] = GLU;
  GyroUp[1] = GLR;
  GyroRnd[0] = GRU;
  GyroRnd[1] = GRR;
  Nunchuck[1] = NLU;
  Nunchuck[0] = NLR;
  Nunchuck[6] = NRU;
  Nunchuck[5] = NRR;
}
