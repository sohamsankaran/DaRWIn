int temp;
int dist;

task main(){

  nMotorEncoder[motorA] = 0;
  temp = 0;
  dist = 0;

  while(true){

    wait1Msec(1);
    nxtDisplayTextLine(4,"dist = %d", nMotorEncoder[motorA]);

    while (bQueuedMsgAvailable()){
      ClearMessage();
      temp = message;
      dist = temp-nMotorEncoder[motorA];
      if(temp != nMotorEncoder[motorA]){
        motor[motorA] = dist;
      }
      else{
        motor[motorA] = 0;
      }
    }
    if(message == 0){
      wait1Msec(5);
      nxtDisplayTextLine(2,"no message");
      continue;
    }

    nxtDisplayTextLine(1,"message = %d",temp);
  }
}
