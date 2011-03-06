/////////////////////////////////////////////////////////////////////////////////////////
/////       ///      ///   /////  ///    /////  ///      ///////////////////////////////
////  ////////  //  ///  //  //  ///  //  ///  ///  ///////////////////////////////////
///  ////////  //  ///  //  //  ///  ////  /  ///  ///  //////////////////////////////
//       ///      ///    ////  ///  /////    ///       //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////
//////       ///       ///       ///       ///        ///       ///  ///    ////  //////
/////  ///  ///  ////////  ////////  ///  ///  /////////  ////////  ///  /  ///  //////
////       ///        //        //       ///        ///       ///  ///  //  //  //////
///  ///  /////////  ////////  //  ///  /////////  ////////  ///  ///  ///  /  //////
//  ///  ///        ///       //  ///  ///        ///       ///  ///  ////    //////
///////////////////////////////////////////////////////////////////////////////////


ubyte GyroUp[3];
ubyte GyroRnd[3];
ubyte Nunchuck[17];

task sendMessages;
void change(int GLU,int GLR,int GRU,int GRR,int NLU,int NLR,int NRU,int NRR, int LEG1, int LEG2, int HEAD1, int HEAD2, int HEAD3);
void checkBTLinkConnected();
void move(int LFTf, int LFTb, int RGTf, int RGTb);
task main(){
  checkBTLinkConnected();
  StartTask(sendMessages);


////////////DEFAULT//////////////////////
  change(0,8,0,8,200,0,200,0,0,0,0,0,0);
  wait1Msec(2000);
/////////////////////////////////////////

  PlaySound(soundException);
  while(nNxtButtonPressed != kEnterButton);
////////////INTRODUCTION////////////////
  change(6,8,6,8,100,150,100,200,0,0,0,0,0);
  wait1Msec(3000);
  change(6,13,6,8,200,0,100,200,0,0,0,-7,0);
  wait1Msec(2000);
  change(6,8,6,8,100,150,100,200,0,0,0,0,0);
  wait1Msec(2000);
  change(6,8,6,8,200,0,200,255,0,0,0,0,0);
  wait1Msec(2000);
  change(6,8,6,8,100,150,100,200,0,0,0,0,0);
  wait1Msec(2000);
  change(6,8,6,13,100,150,200,255,0,0,0,7,0);
  wait1Msec(2000);
  change(6,8,6,8,100,150,100,200,0,0,0,0,0);
  wait1Msec(5000);
////////////////////////////////////////

  PlaySound(soundException);
  while(nNxtButtonPressed != kEnterButton);

////////////KATHAKALI////////////////////
  change(6,8,6,8,100,150,100,200,0,0,10,0,-10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,20,0,10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,30,0,-10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,15,0,10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,0,0,-10);
  wait1Msec(1000);

  change(6,8,6,8,100,150,100,200,0,0,6,-7,0);
  wait1Msec(1000);
  change(6,10,6,6,100,0,100,200,0,0,0,-7,0);
  wait1Msec(1000);
  change(6,6,6,10,100,150,100,255,0,0,6,7,0);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,0,7,0);
  wait1Msec(1000);
  //RGT
  change(10,13,6,8,200,0,100,200,6,0, 10,0,10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,-10,0,10);
  wait1Msec(1000);
  //LFT
  change(6,8,10,13,100,150,200,255,0,6,10,0,-10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,-10,0,-10);
  wait1Msec(1000);

  //RGT
  change(6,13,6,8,200,0,100,200,6,0,10,0,10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,-10,0,10);
  wait1Msec(1000);
  //LFT
  change(6,8,6,13,100,150,200,255,0,6,10,0,-10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,-10,0,-10);
  wait1Msec(1000);

  //RGT
  change(3,13,6,8,200,0,100,200,6,0,10,0,10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,-10,0,10);
  wait1Msec(1000);
  //LFT
  change(6,8,3,13,100,150,200,255,0,6,10,0,-10);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,-10,0,-10);
  wait1Msec(1000);
//////////////////////////////////////////

////////////KATHAKALI EXTENSION/////////////////

  change(6,8,6,8,100,150,100,200,0,0,0,0,0);
  wait1Msec(2000);
  //RGT
  change(6,13,6,8,200,0,100,200,6,0,10,0,10);
  wait1Msec(1000);

  move(0,100,100,0);
  wait1Msec(4500);
  move(0,0,0,0);

  change(6,8,6,8,100,150,100,200,0,0,-10,0,10);
  wait1Msec(2000);

  //LFT

  change(6,8,6,13,100,150,200,255,0,6,10,0,-10);
  wait1Msec(1000);

  move(100,0,0,100);
  wait1Msec(4500);
  move(0,0,0,0);

  change(6,8,6,8,100,150,100,200,0,0,-10,0,-10);
  wait1Msec(1000);

////////////////////////////////////////////////////


////////////BHANGRA//////////////////////

  change(6,8,6,8,100,150,100,200,0,0,30,40,0);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,20,40,0);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,10,40,0);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,0,40,0);
  wait1Msec(1000);
  change(6,8,6,8,100,150,100,200,0,0,-10,40,0);
  wait1Msec(1000);

  change(6,8,6,8,100,0,100,255,0,0,0,40,0);
  wait1Msec(2000);
  PlaySound(soundDownwardTones);
  change(6,10,6,10,100,0,100,255,0,0,0,40,0);
  wait1Msec(1000);
  for(int i = 0; i<=10; ++i){
    if(i<5){
      change(12,10,12,10,200,0,200,255,6,0,0,40,0);
      wait1Msec(1000);
      change(6,10,6,10,100,0,100,255,0,0,0,40,0);
      wait1Msec(1500);
    }
    if(i==5){
      change(12,10,12,10,200,0,200,255,6,6,0,40,0);
      wait1Msec(1000);
      change(6,10,6,10,100,0,100,255,0,0,0,40,0);
      wait1Msec(1500);
    }
    if(i>5){
      change(12,10,12,10,200,0,200,255,0,6,0,40,0);
      wait1Msec(1000);
      change(6,10,6,10,100,0,100,255,0,0,0,40,0);
      wait1Msec(1500);
    }
  }
/////////////////////////////////////////

////////////DEFAULT//////////////////////
  change(0,8,0,8,200,0,200,0,0,0,0,0,0);
  wait1Msec(5000);
/////////////////////////////////////////
}

task sendMessages()
{
  while(true){
    nxtDisplayTextLine(1,"RUP = %d",GyroUp[0]);
    nxtDisplayTextLine(2,"RRND = %d",GyroUp[1]);
    nxtDisplayTextLine(3,"RRND = %d",Nunchuck[15]);

    cCmdMessageWriteToBluetooth(1,GyroUp,3,mailbox1);
    wait1Msec(1);
  	cCmdMessageWriteToBluetooth(2,GyroRnd,3,mailbox1);
    wait1Msec(1);
  	cCmdMessageWriteToBluetooth(3,Nunchuck,17,mailbox1);
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

void change(int GLU,int GLR,int GRU,int GRR,int NLU,int NLR,int NRU,int NRR, int LEG1, int LEG2, int HEAD1, int HEAD2, int HEAD3){
  GyroUp[0] = GLU;
  GyroUp[1] = GRU;
  GyroRnd[0] = GLR;
  GyroRnd[1] = GRR;
  Nunchuck[1] = NLU;
  Nunchuck[0] = NLR;
  Nunchuck[6] = NRU;
  Nunchuck[5] = -(255-NRR);
  GyroUp[2] = LEG1;
  GyroRnd[2] = LEG2;
  Nunchuck[14] = HEAD1+10;
  Nunchuck[15] = HEAD2+10;
  Nunchuck[16] = HEAD3+10;
}
void move(int LFTf, int LFTb, int RGTf, int RGTb){
  Nunchuck[10] = LFTb;
  Nunchuck[11] = LFTf;
  Nunchuck[12] = RGTb;
  Nunchuck[13] = RGTf;
}
