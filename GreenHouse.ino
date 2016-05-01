#include "Lcd.hpp"

void setup () {
	pinMode(RELAI_1, OUTPUT);
	pinMode(RELAI_2, OUTPUT);
	Lcd lcd;

	
}


void loop () {
	lcd->lcdInfo(now);

	if (lcd->getHour() < 6) {
		//Relai OFF
		digitalWrite(RELAI_1,HIGH);
		digitalWrite(RELAI_2,HIGH);
	}
	else {
		//Relai ON
		digitalWrite(RELAI_1, LOW);
		digitalWrite(RELAI_2, LOW);
	}
}
