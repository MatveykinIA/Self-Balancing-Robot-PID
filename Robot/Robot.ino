#include <SoftwareSerial.h>

SoftwareSerial BTserial(2, 3);   //TxD, RxD
String userCommands;    // stores data sent from remote control

void setup() {
    BTserial.begin(38400);
    Serial.begin(9600);
}

void parseString(String data){
    int prevCommaIndex = -1;
    int numCommands = 4;
    for(int i=0; i<numCommands; i++){
        int commaIndex = data.indexOf(',', prevCommaIndex+1);
        int cmd = data.substring(prevCommaIndex+1, commaIndex).toInt();
        prevCommaIndex = commaIndex;
        Serial.print(cmd);
        Serial.print('\t');
    }
}

void loop() {
    if (BTserial.available() > 0) { // Check if data is incomming
        userCommands = BTserial.readStringUntil('\n'); 
    }
    parseString(userCommands);
    Serial.print('\n');
}
