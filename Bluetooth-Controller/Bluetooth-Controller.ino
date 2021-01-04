/*
A simple remote for tuning the PID coeffients via bluetooth.

Prior to use the two bluetooth modules must be confirgured
Controller should be main and robot secondary
Ensure baudrate of modules match (38400)
For tutorial on how to calibrate and pair bluetooth modules refer to: http://howtomechatronics.com/tutorials/arduino/how-to-configure-pair-two-hc-05-bluetooth-module-master-slave-commands/
*/

#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3); //TxD, RxD

#define pot1 A0
#define pot2 A1
#define pot3 A2
#define button 13

uint16_t pVal1, pVal2, pVal3;
int bVal;

void setup() {
    BTserial.begin(38400);
    pinMode(pot1, INPUT);
    pinMode(pot2, INPUT);
    pinMode(pot3, INPUT);
    pinMode(button, INPUT);
    Serial.begin(9600);
}

void loop(){
    pVal1 =  analogRead(pot1);
    pVal2 =  analogRead(pot2);
    pVal3 =  analogRead(pot3);
    bVal =  digitalRead(button);

    
    BTserial.print(pVal1);
    BTserial.print(',');
    BTserial.print(pVal2);
    BTserial.print(',');
    BTserial.print(pVal3);
    BTserial.print(',');
    BTserial.print(bVal);
    BTserial.print('\n');


    Serial.print(pVal1);
    Serial.print('\t');
    Serial.print(pVal2);
    Serial.print('\t');
    Serial.print(pVal3);
    Serial.print('\t');
    Serial.print(bVal);
    Serial.print('\n');
    delay(50);
}