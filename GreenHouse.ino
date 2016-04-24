// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"



#define RELAI_1 6
#define RELAI_2 7

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
	#define Serial SerialUSB
#endif

RTC_DS1307 rtc;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () {
	pinMode(RELAI_1, OUTPUT);
	pinMode(RELAI_2, OUTPUT);
	lcd.begin(16,2);
	lcd.setCursor(3,0);
	lcd.print("GreenHouse");

	#ifndef ESP8266
		while (!Serial); // for Leonardo/Micro/Zero
	#endif

	Serial.begin(57600);
	if (! rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (1);
	}

	if (! rtc.isrunning()) {
		Serial.println("RTC is NOT running!");
		// following line sets the RTC to the date & time this sketch was compiled
		Serial.println(__DATE__);
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
		// This line sets the RTC with an explicit date & time, for example to set
		// January 21, 2014 at 3am you would call:
		// rtc.adjust(DateTime(2016, 4, 23, 14, 57, 0));
	}
}

void loop () {
	DateTime now = rtc.now();

	if (now.hour() < 6)
	{
		digitalWrite(RELAI_1,HIGH);
		digitalWrite(RELAI_2,HIGH);
	}
	else
	{
		digitalWrite(RELAI_1, LOW);
		digitalWrite(RELAI_2, LOW);
	}

	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(0, 1);
	lcd.print(now.hour(),DEC);
	lcd.print(':');
	lcd.print(now.minute(), DEC);
	lcd.setCursor(9,1);
	if (digitalRead(RELAI_1) == LOW) lcd.print("led:ON");
	else lcd.print("led:OFF");
	
	//Serial.print(now.year(), DEC);
	//Serial.print('/');
	//Serial.print(now.month(), DEC);
	//Serial.print('/');
	//Serial.print(now.day(), DEC);
	//Serial.print(" (");
	//Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
	//Serial.print(") ");
	//Serial.print(now.hour(), DEC);
	//Serial.print(':');
	//Serial.print(now.minute(), DEC);
	//Serial.print(':');
	//Serial.print(now.second(), DEC);
	//Serial.println();	
	//Serial.println();
	delay(1000);
}
