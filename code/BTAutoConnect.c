task main(){
  btDisconnectAll();
  wait1Msec(7000);
  PlaySound(soundBlip);
  btConnect(1, "1-DaRWIn");
  wait1Msec(7000);
  PlaySound(soundBlip);
  btConnect(2, "2-DaRWIn");
  wait1Msec(7000);
  PlaySound(soundBlip);
  btConnect(3, "3-DaRWIn");
  wait1Msec(7000);
  PlaySound(soundBlip);
}
