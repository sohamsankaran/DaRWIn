#pragma config(Motor,  motorA,          STS,           tmotorNormal, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main(){
  for(int i = 0;i<=1;++i){
    motor[STS] = 100;
    wait1Msec(1000);
    motor[STS] = -100;
    wait1Msec(1000);
  }
  motor[STS] = 0;
  wait1Msec(500);
}