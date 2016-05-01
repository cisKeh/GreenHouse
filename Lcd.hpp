#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h>
#include "RTClib.h"
#include "Arduino.h"


#define DS18B20 0x28	// Adresse 1-Wire du DS18B20
#define TEMP1 9 		// Broche utilisée pour le bus 1-Wire
#define TEMP2 10
#define RELAI_1 6
#define RELAI_2 7

class Lcd {
	private:
		OneWire _temp1(TEMP1);
		OneWire _temp2(TEMP2);
		LiquidCrystal _lcd(12,11,5,4,3,2);


	public:
		bool getTemperature(float* temp, OneWire ds);
		void lcdInfo(DateTime now);



};