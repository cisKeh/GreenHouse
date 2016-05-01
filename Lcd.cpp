#include "Lcd.hpp"

bool Lcd::getTemperature(float* temp, OneWire ds) {
	byte data[9], addr[8];
		//data: log from scratchpad
		//addr: temp sensor module address

	if (!ds.search(addr)) {	// if module not found
		ds.reset_search();	// --> reset the research and return error
		return false;
	}

	if(OneWire::crc8(addr,7) != addr[7])	//check the address &
		return false; 						// return error if broken message

	if (addr[0] != DS18B20) return false; //check if it is a DS18B20

	ds.reset();
	ds.select(addr);
	ds.write(0x44, 1);	//start a temperature measure
	delay(800);			//waiting for measure

	ds.reset();
	ds.select(addr);
	ds.write(0xBE);		//send a read request from scratchpad

	for (byte i =0; i < 9; i++)
		data[i] = ds.read()		//put scratchpad bytes into data

	*temp = ((data[1] << 8) | data[0]) * 0.0625; //reinterpret into Celsius

	return true;
}

void Lcd::lcdInfo(DateTime now) {
	float temp1, temp2;
	getTemperature(&temp1, _temp1);
	getTemperature(&temp2, _temp2);

	_lcd.clear();
	_lcd.setCursor(0,0);
	_lcd.print("GreenHouse");

	_lcd.setCursor(11,0);
	_lcd.print(temp1, 1);
	_lcd.write(223);
	_lcd.setCursor(11,1);
	_lcd.print(temp2, 1);
	_lcd.write(223);
	_lcd.setCursor(0, 1);
	_lcd.print(now.hour(),DEC);
	_lcd.print(':');
	_lcd.print(now.minute(), DEC);
	delay(58400);

}