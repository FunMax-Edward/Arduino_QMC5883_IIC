Updated July 18, 2024

Round Robin

Advantages: The data refresh rate of the serial port output is more accurate

Among them QMC5883.ino can change the output frequency by modifying timeSlice

You can burn QMC5883.ino and then view the actual number of refreshes in one second in the serial port

Tested, 250Hz is the best, 500Hz and above is not allowed.

Also note that the pins specified in my code are SDA and SCL, if your microcontroller has the above pins by default

Delete the following two lines

Wire.setPins(6, 7);

Wire.begin();

At the same time, you need to scan the IIC address of your device with the IIC scanner I2C_Scan.ino

Whether the pins are specified or removed is the same as above

Replace the address DFRobot_QMC5883 compass(&Wire, 0x0D); 0x0D

