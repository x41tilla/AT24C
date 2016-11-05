/**
 *
 *   EEPROM AT24C class library
 *
 *   Tested with Teensy + AT24C256B
 *
 *   Author:    Atilla "x41tilla" Özkan
 *   Date:                   2016-11-02
 */

#ifndef AT24C_HPP
#define	AT24C_HPP

#include <Arduino.h>
#include <Wire.h>

#define	AT24C_DEFAULT_ADDRESS	         0x50
#define	AT24C_SEQ_WRITE	                   64
#define	AT24C_SEQ_READ	                  128
#define	AT24C_WRITE_CYCLE_DELAY_MS	        5

class AT24C{

public:

    /**
     * Constructors
     */
    AT24C();
    AT24C(const uint8_t chipAddress);


    /**
     * Retrieve a single byte from address
     * @method    read
     * @param     address    the address to read from
     * @return               byte read
     */
    uint8_t read(const ushort address);

    /**
     * Retrieve a sequence of bytes
     * @method    read
     * @param     address    the address to start reading from
     * @param     buffer     buffer to be filled with retreived data
     * @param     length     number of bytes to read
     */
    void read(const ushort address, uint8_t* buffer, const ushort length);


    /**
     * Write a single byte
     * @method    write
     * @param     address    the address to write to
     * @param     data       byte to be written
     */
    void write(const ushort address, uint8_t data);

    /**
     * Write a sequence of bytes
     * @method    write
     * @param     address    the address to start from
     * @param     data       data to be written
     * @param     size       size of the data
     */
    void write(const ushort address, uint8_t data[], const ushort size);

private:

    const uint8_t _chipAddress;

};

#endif
