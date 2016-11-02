#include <Arduino.h>
#include <Wire.h>
#include <AT24C.hpp>

AT24C chippy;

void setup(){

    Wire.begin();

    Serial.begin(115200);
    while(!Serial){
        delay(10);
    }

    char dataVec[] = "Valuable data stored on EEPROM.";
    chippy.write(0, (byte*)dataVec, sizeof(dataVec));

    int length = sizeof(dataVec)/sizeof(char);

    char* dataBuffer = new char[length];

    chippy.read(0, (byte*) dataBuffer, length);

    Serial.println(dataBuffer);
}

void loop(){
    yield();
}
