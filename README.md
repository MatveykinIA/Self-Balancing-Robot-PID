# Self Balancing Robot using PID Controller

2 wheeled balancing robot controlled via a bluetooth remote

## Setup
Prior to use, the two bluetooth modules must be confirgured:

Controller should be main and robot secondary

Ensure baudrate of modules match (38400)

For tutorial on how to calibrate and pair bluetooth modules refer to: http://howtomechatronics.com/tutorials/arduino/how-to-configure-pair-two-hc-05-bluetooth-module-master-slave-commands/

MPU6050 must be calibrated prior to use by finding the approriate offset values. This was done using IMU_Zero.ino from Jeff Rowberg's library: https://github.com/jrowberg/i2cdevlib