CMDNunchukInit byte [] = (0x03, 0xA4, 0x40, 0x00);
CMDNunchukWrite byte [] = (0x02, 0xA4, 0x00);
CMDNunchukRead byte [] = (0x01, 0xA4);

/ / Byte nbytes; / / NXC
byte outbuf [6];
int outbuf1 [6] / / ubyte workaround for RobotC

/ / This function Allows conversion of an unsigned byte to a signed int
/ / This is a work around for RobotC
int ubyteToInt (ubyte _byte) (
   _ret int = 0;
   _ret = (_byte & 0x80)? (_byte & 0x7F) + 0x80: _byte;
   _ret return;
)

/ / Port port is the NXT, i2c_cmd nunchuk is the internal address register
/ / At i2c_cmd = 0 .. 5 are 6 bytes of sensor values
/ / At i2c_cmd = 0x20 ... 0x2F you get 16 bytes of calibration data

/ / Sub NunchukGetParamter (byte port, byte i2c_cmd) / / NXC
sub NunchukGetParamter (Tsensor port, byte i2c_cmd) / / RobotC
(
  / / Initialize the Nunchuk
  / / SetSensorLowspeed (port) / / NQC
   sensor type [port] = sensorI2CCustom / / RobotC

  / / LowspeedWrite (port, 0, CMDNunchukInit) / / NXC ask for 0 bytes
   sendI2CMsg (port, CMDNunchukInit [0], 0) / / RobotC

  / / While (LowspeedStatus (port, nbytes)> 0) / / NQC
  while (nI2CStatus [port] == STAT_COMM_PENDING) / / Wait for I2C bus RobotC to be ready

  / / CMDNunchukWrite [1] = i2c_cmd / / NXC at 0x00 6 bytes of sensor values
  CMDNunchukWrite [2] = i2c_cmd / / RobotC

  / / LowspeedWrite (port, 0, CMDNunchukWrite) / / NXC Nunchuk write register address
   sendI2CMsg (port, CMDNunchukWrite [0], 0) / / RobotC

  / / While (LowspeedStatus (port, nbytes)> 0) / / NXC
  while (nI2CStatus [port] == STAT_COMM_PENDING) / / Wait for I2C bus RobotC to be ready

  byte count = 6;
  / / LowspeedWrite (port count, CMDNunchukRead) / / NXC: ask for count bytes
   sendI2CMsg (port, CMDNunchukRead [0], count); / / RobotC

  / / While (LowspeedStatus (port, nbytes)> 0) / / NXC
  while (nI2CStatus [port] == STAT_COMM_PENDING) / / Wait for I2C bus to be ready

  / / If (nbytes == count) (/ / NXC
  if (nI2CBytesReady [port] == count) (/ / RobotC

    / / LowspeedRead (port, count, outbuf) / / NXC read data from buffer
      readI2CReply (port, outbuf [0], 6) / / RobotC

    for (int i = 0; i <count; i + +) (
       outbuf1 [i] = ubyteToInt (outbuf [i]) / / ubyte workaround for RobotC
      outbuf1 [i] = (outbuf1 [i] ^ 0x17) + 0x17;
    )
  )
  else (
    / / Array init (outbuf, 0,0) / / NXC: error
     memset (outbuf, 0, 0) / / RobotC
  )
)

task main ()
(
  while (true)
  (
    NunchukGetParamter (S1, 0x00) / / see comment for i2c_cmd

    / / If (outbuf ArrayLen () == 6) (/ / NXC
    if (sizeof (outbuf) == 6) (/ / RobotC

       / / String Nunchuk = "aXaYgXgYgZCZ" / / NXC
       char Nunchuk [16] / / RobotC
       strcpy (Nunchuk, "aXaYgXgYgZCZ") / / RobotC

       if ((outbuf1 [5] & 0x01) = 0) (Nunchuk [11] = 122;) / / Z-Button Show
       if ((outbuf1 [5] & 0x02) = 0) (Nunchuk [10] = 99;) / / Show C-Button

       / / Clear screen () / / NXC
       eraseDisplay () / / RobotC

       / / For (int i = 0; i <ArrayLen (outbuf); i + +) (/ / NXC
       for (int i = 0; i <6; i + +) (/ / RobotC

         / / TextOut (15 * i, LCD_LINE3, substr (Nunchuk, 2 * i, 2)) / / NXC
         nxtDisplayStringAt (15 * i, 50, "% c", Nunchuk [2 * i]) / / RobotC
         nxtDisplayStringAt (15 +5.50 * i, "% c", Nunchuk [2 * i +1]) / / RobotC

         / / TextOut (15 * i, LCD_LINE5, FormatNum ("% 02X", outbuf [i])) / / NXC
         nxtDisplayStringAt (15 * i, 40, "% 02X", outbuf1 [i]) / / RobotC
       )

       / / CircleOut ((outbuf [0] 0x1E) / 2, (outbuf [1]-0x1E) / 3, 3) / / NXC analog stick
       nxtDrawCircle ((outbuf1 [0] 0x1E) / 2, (outbuf1 [1]-0x1E) / 3, 3) / / RobotC

       / / RectOut ((outbuf [2]-0x46), (outbuf [3]-0x46) / 2, 6, 6) / / NXC acceleration value
       nxtDrawCircle ((outbuf1 [2]-0x46), (outbuf1 [3]-0x46) / 2, 6);
    )
    / / Wait (100) / / NXC
    wait1Msec (100); / / RobotC
  )
)
