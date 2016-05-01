// Date and time functions using a DS1307 RTC connected via I2C and Wire lib
#include <Wire.h>
#include <LiquidCrystal.h>
#include <OneWire.h> // Inclusion de la librairie OneWire
#include "RTClib.h"

#define DS18B20 0x28     // Adresse 1-Wire du DS18B20
#define TEMP1 9 // Broche utilisée pour le bus 1-Wire
#define TEMP2 10
#define RELAI_1 6
#define RELAI_2 7

OneWire _temp1(TEMP1); // Création de l'objet OneWire ds
OneWire _temp2(TEMP2); // Création de l'objet OneWire ds


RTC_DS1307 _rtc;

// initialize the library with the numbers of the interface pins
LiquidCrystal _lcd(12, 11, 5, 4, 3, 2);




// Fonction récupérant la température depuis le DS18B20
// Retourne true si tout va bien, ou false en cas d'erreur
boolean getTemperature(float *temp, OneWire ds){
  byte data[9], addr[8];
  // data : Données lues depuis le scratchpad
  // addr : adresse du module 1-Wire détecté
 
  if (!ds.search(addr)) { // Recherche un module 1-Wire
    ds.reset_search();    // Réinitialise la recherche de module
    return false;         // Retourne une erreur
  }
   
  if (OneWire::crc8(addr, 7) != addr[7]) // Vérifie que l'adresse a été correctement reçue
    return false;                        // Si le message est corrompu on retourne une erreur
 
  if (addr[0] != DS18B20) // Vérifie qu'il s'agit bien d'un DS18B20
    return false;         // Si ce n'est pas le cas on retourne une erreur
 
  ds.reset();             // On reset le bus 1-Wire
  ds.select(addr);        // On sélectionne le DS18B20
   
  ds.write(0x44, 1);      // On lance une prise de mesure de température
  delay(800);             // Et on attend la fin de la mesure
   
  ds.reset();             // On reset le bus 1-Wire
  ds.select(addr);        // On sélectionne le DS18B20
  ds.write(0xBE);         // On envoie une demande de lecture du scratchpad
 
  for (byte i = 0; i < 9; i++) // On lit le scratchpad
    data[i] = ds.read();       // Et on stock les octets reçus
   
  // Calcul de la température en degré Celsius
  *temp = ((data[1] << 8) | data[0]) * 0.0625; 
   
  // Pas d'erreur
  return true;
}




void lcdInfo(DateTime now) {
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
	Serial.print("T1:");
	Serial.println(temp1, 1);
	Serial.print("T2:");
	Serial.println(temp2, 1);
	_lcd.setCursor(0, 1);
	_lcd.print(now.hour(),DEC);
	_lcd.print(':');
	_lcd.print(now.minute(), DEC);
	
}





void setup () {
	pinMode(RELAI_1, OUTPUT);
	pinMode(RELAI_2, OUTPUT);
	_lcd.begin(16,2);

	Serial.begin(57600);
	if (! _rtc.begin()) {
		Serial.println("Couldn't find RTC");
		while (1);
	}

	if (! _rtc.isrunning()) {
		Serial.println("RTC is NOT running!");
		_rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
	}
}


void loop () {
	DateTime now = _rtc.now();

	lcdInfo(now);



	if (now.hour() < 6)
	{
		Serial.print("Relai OFF");
		digitalWrite(RELAI_1,HIGH);
		digitalWrite(RELAI_2,HIGH);
	}
	else
	{
		//Serial.print("Relai ON");
		digitalWrite(RELAI_1, LOW);
		digitalWrite(RELAI_2, LOW);
	}
	
	delay(58400);
}
