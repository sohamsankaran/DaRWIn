#pragma config(Motor,  motorA,          RND,           tmotorNormal, PIDControl, encoder)
#pragma config(Motor,  motorB,          UP,            tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
int distUp;
int distRnd;

int AbsMove(int MUp, int MRnd){
  int testRnd = 0;
  int testUp = 0;
  while(testUp==0 || testRnd==0){
    nxtDisplayTextLine(1,"UP = %d",nMotorEncoder[UP]);
    nxtDisplayTextLine(2,"RND = %d",nMotorEncoder[RND]);
    distUp = MUp-nMotorEncoder[UP];
    if(MUp <= nMotorEncoder[UP]-2 || MUp >= nMotorEncoder[UP]+2){
     motor[UP] = distUp;
    }
    else{
      testUp = 1;
      motor[UP] = 0;
    }

    distRnd = MRnd-nMotorEncoder[RND];
    if(MRnd <= nMotorEncoder[RND]-2 || MRnd >= nMotorEncoder[RND]+2){
      motor[RND] = distRnd;
    }
    else{
      testRnd = 1;
      motor[RND] = 0;
    }
  }
  motor[UP]= 0;
  motor[RND]= 0;
  return 0;
}

task main(){
  nMotorEncoder[UP] = 0;
  nMotorEncoder[RND] = 0;
  AbsMove(230,100);
  for(int i=0; i <= 5; ++i){
    AbsMove(500,180);
    AbsMove(230,180);
  }
  AbsMove(500,180);
  AbsMove(0,0);
}
