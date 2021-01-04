/*
A simple remote for tuning the PID coeffients via bluetooth.
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

    delay(50);
}