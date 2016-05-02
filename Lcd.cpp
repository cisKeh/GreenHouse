#include "Arduino.h"
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

	if (addr[0] != DS18B20()) return false; //check if it is a DS18B20

	ds.reset();
	ds.select(addr);
	ds.write(0x44, 1);	//start a temperature measure
	delay(800);			//waiting for measure

	ds.reset();
	ds.select(addr);
	ds.write(0xBE);		//send a read request from scratchpad

	for (byte i =0; i < 9; i++)
		data[i] = ds.read();		//put scratchpad bytes into data
	uint16_t tempUra; //just a gateway
	tempUra = ((data[1] << 8) | data[0]);
	*temp = static_cast<float>(tempUra) * 0.0625; //reinterpret into Celsius

	return true;
}

void Lcd::showTemp(unsigned column1, unsigned line1, unsigned column2, unsigned line2) {
	float temp1, temp2;
	getTemperature(&temp1, *_temp1);
	getTemperature(&temp2, *_temp2);
	_lcd->setCursor(column1,line1);
	_lcd->print(temp1, 1);
	_lcd->write(223);	// symbol °
	_lcd->setCursor(column2,line2);
	_lcd->print(temp2, 1);
	_lcd->write(223);	// symbol °
}

void Lcd::showTime(unsigned column, unsigned line) {
	DateTime now = _rtc->now();
	_lcd->setCursor(column, line);
	_lcd->print(now.hour(),DEC);
	_lcd->print(':');
	_lcd->print(now.minute(), DEC);
}

void Lcd::lcdInfo() {

	_lcd->clear();
	_lcd->setCursor(0,0);
	_lcd->print("GreenHouse");

	Lcd::showTime(0,1);
	Lcd::showTemp(11, 0, 11, 1);
	delay(58400);

}

Lcd::Lcd() {
	_temp1 = new OneWire(TEMP_1());
	_temp2 = new OneWire(TEMP_2());
	_rtc = new RTC_DS1307();
	_lcd = new LiquidCrystal(RS,ENABLE,D0,D1,D2,D3);



	_lcd->begin(16,2);
	Serial.begin(57600);
	if (! _rtc->begin()) {
		_lcd->setCursor(0,0);
		_lcd->println("Couldn't find RTC");
		while (1);
	}

	if (! _rtc->isrunning()) {
		_lcd->setCursor(0,0);
		_lcd->println("RTC is NOT running!");
		_rtc->adjust(DateTime(F(__DATE__), F(__TIME__)));
	}
	
}

Lcd::~Lcd() {
	delete _temp1; delete _temp2; delete _rtc; delete _lcd;
	_temp1 = nullptr; _temp2 = nullptr; _rtc = nullptr; _lcd = nullptr;

}



uint8_t Lcd::getHour() {
	// DateTime now = _rtc->now();
	// returnt now.hour();
	return _rtc->now().hour();
}

uint8_t Lcd::getMin() {
	// DateTime now = _rtc->now();
	// return now.minute();
	return _rtc->now().minute();
}