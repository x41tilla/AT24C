#include "AT24C.hpp"

AT24C::AT24C():
    AT24C(AT24C_DEFAULT_ADDRESS){

}

AT24C::AT24C(const byte chipAddress):
    _chipAddress(chipAddress){

}

uint8_t AT24C::read(const ushort address){


    Wire.beginTransmission(_chipAddress);
    Wire.send(address >>   8); // MSB
    Wire.send(address & 0xFF); // LSB
    Wire.endTransmission();

    Wire.requestFrom(_chipAddress,1);

    uint8_t data = 0xFF;
    if (Wire.available())
        data = Wire.receive();

    return data;
}

void AT24C::read(const ushort address, uint8_t* buffer, const ushort length){

    Wire.beginTransmission(_chipAddress);
    Wire.send(address >>   8); // MSB
    Wire.send(address & 0xFF); // LSB
    Wire.endTransmission();

    Wire.requestFrom(_chipAddress, length);

    int c = 0;
    for ( c = 0; c < length; c++ )
        if (Wire.available())
            buffer[c] = Wire.receive();

}

void AT24C::write(const ushort address, uint8_t data){

    Wire.beginTransmission(_chipAddress);
    Wire.send(address >>   8); // MSB
    Wire.send(address & 0xFF); // LSB

    Wire.send(data);

    Wire.endTransmission();

    delay(AT24C_WRITE_CYCLE_DELAY_MS);
}

void AT24C::write(const ushort address, uint8_t data[], const ushort size){

    int i = 0;
    ushort currPos = address;
    ushort dataDue = size;
	while( dataDue - AT24C_SEQ_WRITE > 0 ){

        Wire.beginTransmission(_chipAddress);
        Wire.write(currPos >>   8);    // MSB
		Wire.write(currPos & 0xFF); // LSB

        Wire.write(data + i * AT24C_SEQ_WRITE, AT24C_SEQ_WRITE);

        Wire.endTransmission();

        delay(AT24C_WRITE_CYCLE_DELAY_MS);

        i++;
        dataDue -= AT24C_SEQ_WRITE;
        currPos += AT24C_SEQ_WRITE;
	}

	if( dataDue > 0 ){

    	Wire.beginTransmission(_chipAddress);
        Wire.write(address >>   8);   // MSB
		Wire.write(address & 0xFF); // LSB

        Wire.write(data + i * AT24C_SEQ_WRITE, dataDue);

        Wire.endTransmission();

        delay(AT24C_WRITE_CYCLE_DELAY_MS);
	}
}
