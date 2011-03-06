//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int dist;
int time;
void checkBTLinkConnected();

task main(){

  checkBTLinkConnected();
  dist = 0;
  time = 0;
  nMotorEncoder[motorA] = 0;

  while(true){
    wait1Msec(1);
    dist = nMotorEncoder[motorA];

    if(time == 100){
      if(dist != 0){
        sendMessageWithParm(dist);
      }
      time = 0;
    }

    nxtDisplayTextLine(1,"dist = %d", dist);

    if(nNxtButtonPressed == kEnterButton) {
      nMotorEncoder[motorA] = 0;
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
