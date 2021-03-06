ubyte GyroUp[3];
ubyte GyroRnd[3];
ubyte Nunchuck[14];

task sendMessages;
void change(int GLU,int GLR,int GRU,int GRR,int NLU,int NLR,int NRU,int NRR);
void checkBTLinkConnected();

task main(){
  checkBTLinkConnected();
  StartTask(sendMessages);
  change(6,8,6,8,100,150,100,200);
  wait1Msec(3000);
  change(10,13,6,8,200,0,100,200);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200);
  wait1Msec(1000);
  change(6,13,6,8,200,0,100,200);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200);
  wait1Msec(1000);
  change(3,13,6,8,200,0,100,200);
  wait1Msec(1000);

  change(6,8,6,8,100,150,100,200);
  wait1Msec(1500);

  change(6,8,10,13,100,150,200,255);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200);
  wait1Msec(1000);
  change(6,8,6,13,100,150,200,255);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200);
  wait1Msec(1000);
  change(6,8,3,13,100,150,200,255);
  wait1Msec(1000);

  change(6,8,6,8,100,0,100,200);
  wait1Msec(2000);
  PlaySound(soundDownwardTones);
  change(6,10,6,10,100,0,100,255);
  wait1Msec(1500);
  for(int i = 0; i<=10; ++i){
    change(12,10,12,10,200,0,200,255);
    wait1Msec(1000);
    change(6,10,6,10,100,0,100,255);
    wait1Msec(1000);
  }

  change(0,8,0,8,200,0,200,0);
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
  GyroUp[1] = GRU;
  GyroRnd[0] = GLR;
  GyroRnd[1] = GRR;
  Nunchuck[1] = NLU;
  Nunchuck[0] = NLR;
  Nunchuck[6] = NRU;
  Nunchuck[5] = NRR;
}
