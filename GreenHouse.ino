// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"



#define RELAI_1 6
#define RELAI_2 7



RTC_DS1307 rtc;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);






void lcdInfo(DateTime now) {
	// set the cursor to column 0, line 1
	// (note: line 1 is the second row, since counting begins with 0):
	lcd.setCursor(3,0);
	lcd.print("GreenHouse");
	lcd.setCursor(0, 1);
	lcd.print(now.hour(),DEC);
	lcd.print(':');
	lcd.print(now.minute(), DEC);

	lcd.setCursor(11,1);
	if (digitalRead(RELAI_1) == LOW) lcd.print("led:Y");
	else lcd.print("led:N");
}





void setup () {
	pinMode(RELAI_1, OUTPUT);
	pinMode(RELAI_2, OUTPUT);
	lcd.begin(16,2);

	Serial.begin(57600);
	if (! rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (1);
	}

	if (! rtc.isrunning()) {
		Serial.println("RTC is NOT running!");
		rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
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

	lcdInfo(now);
	delay(1000);
}
