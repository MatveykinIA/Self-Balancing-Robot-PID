/*
code for using the MPU6050 to find the roll angle (x-axis)
complementary filter used to improve output
MPU6050 must be calibrated prior to use by finding the approriate offset values. This was done using IMU_Zero.ino from Jeff Rowberg's library: https://github.com/jrowberg/i2cdevlib
*/

#include "Wire.h"
#include "MPU6050.h"
#include "I2Cdev.h"
#include "math.h"

MPU6050 mpu;
int16_t accY, accZ, gyroX;
volatile int gyroRate, Speed;
volatile float accAngle, gyroAngle;
volatile float currentAngle, prevAngle=0;

float tau = 0.75;               
float sampleFreq = 200;
float dT = 1/sampleFreq;
float alpha = tau/(tau+dT);

void init_Timer(){                                                        
  // initialize Timer1 for a ISR every 5ms
  cli();                  // disable global interrupts
  TCCR1A = 0;             // set entire TCCR1A register to 0
  TCCR1B = 0;             // same for TCCR1B    
  TCNT1  = 0;             // initialize counter value to 0
                          // set compare match register to set sample time 5ms (200Hz increments)
  OCR1A = 9999;           // compare match register = [16MHz/(prescaler*sampleFreq)]-1 = [16Mhz/(8*200Hz)]-1 
  TCCR1B |= (1 << WGM12); // turn on CTC mode
                          // set CS11 bit for prescaling of 8  
  TCCR1B |= (1 << CS11);  // prescaler can be equal to 1, 8, 64, 256, 1024 (lookup table for codes online)
  TIMSK1 |= (1 << OCIE1A);// enable timer compare interrupt
  sei();                  // enable global interrupts
}

void setup() {
  Serial.begin(9600);
  mpu.initialize();
  // following offsets found using IMU_Zero.ino
  mpu.setYAccelOffset(1545);
  mpu.setZAccelOffset(947);
  mpu.setXGyroOffset(21);
  init_Timer();                                                         
}

void loop() {
  accY = mpu.getAccelerationY();
  accZ = mpu.getAccelerationZ();  
  gyroX = mpu.getRotationX();
  Serial.println(currentAngle);
}

ISR(TIMER1_COMPA_vect){
  accAngle = atan2(accY, accZ)*RAD_TO_DEG;
  gyroRate = map(gyroX, -32768, 32767, -250, 250);
  gyroAngle = prevAngle + (float)gyroRate*dT;  
  currentAngle = (alpha)*(gyroAngle) + (1-alpha)*(accAngle);
  prevAngle = currentAngle;
}