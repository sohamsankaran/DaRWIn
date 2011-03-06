byte CMDNunchukInit[] = {0x03, 0xA4, 0x40, 0x00};
byte CMDNunchukWrite[] = {0x02, 0xA4, 0x00};
byte CMDNunchukRead[] = {0x01, 0xA4};

byte outbuf[6];
int outbuf1[6];   //ubyte workaround for ROBOTC

//  This function allows conversion of an unsigned byte to a signed int
//  This is a workaround for ROBOTC
int ubyteToInt(ubyte _byte) {
  int _ret = 0;
_ret = (_byte & 0x80) ? (_byte & 0x7F) + 0x80 : _byte;
  return _ret;
}

// port is the NXT port, i2c_cmd is the nunchuk internal address register
// at i2c_cmd=0...5 are 6 Byte of sensor values
// at i2c_cmd=0x20 ... 0x2F  you get 16 Byte of calibration data

sub NunchukGetParamter(tSensors port, byte i2c_cmd)
{
  // Initialize the Nunchuk
  SensorType[port] = sensorI2CCustom;

  //Ask for 0 bytes
  sendI2CMsg(port, CMDNunchukInit[0], 0);

  while (nI2CStatus[port] == STAT_COMM_PENDING) ; // ROBOTC Wait for I2C bus to be ready

  //Write at 0x00: 6 Bytes of sensor values
  CMDNunchukWrite[2] =i2c_cmd;

  //Write Nunchuk register address
  sendI2CMsg(port, CMDNunchukWrite[0], 0);

  while (nI2CStatus[port] == STAT_COMM_PENDING) ; // ROBOTC Wait for I2C bus to be ready

  byte count = 6;
  //Ask for count bytes
  sendI2CMsg(port, CMDNunchukRead[0], count);

  while (nI2CStatus[port] == STAT_COMM_PENDING) ; // Wait for I2C bus to be ready

  if(nI2CBytesReady[port] == count){

    //Read data from buffer
    readI2CReply(port, outbuf[0], 6);

    for(int i=0; i<count; i++ ){
      outbuf1[i]=ubyteToInt(outbuf[i]);   //ubyte workaround for ROBOTC
      outbuf1[i]=(outbuf1[i]^0x17) + 0x17;
    }
  }
  else {
    // error
    memset(outbuf, 0, 0);
  }
}


task main()

{
  while (true)
  {
    NunchukGetParamter(S1, 0x00);          //see comment for i2c_cmd

    if (sizeof(outbuf)==6)    {

      // analog stick
      eraseDisplay();
      nxtDrawCircle((outbuf1[0]-0x1E)/2, (outbuf1[1]-0x1E)/3, 3);

      //{motor[motorA] = ((outbuf1[0])-0x80);}   //Set Motor A & Adjust the Subtract 0x80 Value to Suite Joystick controller
      //{motor[motorB] = ((outbuf1[1])-0x80);}   //Set Motor B & Adjust the Subtract 0x80 Value to Suite Joystick controller

      if((outbuf1 [5] & 0x01) == 0){
      motor[motorA] = ((outbuf1[2])-0x80);   //Set Motor A & Adjust the Subtract 0x80 Value to Suite Accelaratoin Sensor controller
      motor[motorB] = ((outbuf1[3])-0x80);   //Set Motor B & Adjust the Subtract 0x80 Value to Suite Accelaratoin Sensor controller

}

else{
  motor[motorA] = 0;
      motor[motorB] = 0;
}

    }
  }
}
