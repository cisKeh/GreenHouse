#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include "RTClib.h"
#include "Arduino.h"

#ifndef LCD_H
#define LCD_H

//Temperature Sensor
constexpr uint8_t DS18B20() {return 0x28;}
// constexpr uint8_t TEMP_1() {return 9;}
// #define DS18B20 0x28	// Adresse 1-Wire du DS18B20
// #define TEMP_1 9 		// Broche utilisée pour le bus 1-Wire
#define TEMP_2 10

//Relay
#define RELAY_1 6
#define RELAY_2 7

//Lcd
#define RS 12
#define ENABLE 11
#define D0 5
#define D1 4
#define D2 3
#define D3 2


class Lcd {
	private:
		// uint8_t TEMP_1 = 9;
		OneWire _temp1(9);
		OneWire _temp2(TEMP_2);
		RTC_DS1307 _rtc;
		// initialize the library with the numbers of the interface pins
		LiquidCrystal _lcd(RS,ENABLE,D0,D1,D2,D3);


	public:
		bool getTemperature(float* temp, OneWire ds);
		void lcdInfo();
		uint8_t getHour();
		uint8_t getMinute();
		void showTemp(unsigned column1, unsigned line1, unsigned column2, unsigned line2);
		void showTime(unsigned column, unsigned line);
		Lcd();

};

#endif