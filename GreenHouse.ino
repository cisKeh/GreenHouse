#include "Lcd.hpp"

Lcd lcd;

void setup () {
	pinMode(RELAY_1, OUTPUT);
	pinMode(RELAY_2, OUTPUT);

	
}


void loop () {
	lcd.lcdInfo();

	if (lcd.getHour() < 6) {
		//Relay OFF
		digitalWrite(RELAY_1,HIGH);
		digitalWrite(RELAY_2,HIGH);
	}
	else {
		//Relay ON
		digitalWrite(RELAY_1, LOW);
		digitalWrite(RELAY_2, LOW);
	}
}
