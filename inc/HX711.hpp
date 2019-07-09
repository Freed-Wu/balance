#ifndef HX711_HPP
#define HX711_HPP

#include <Arduino.h>

#define HX711_SCK hxPins[0]
#define HX711_DT hxPins[1]
#define GAP_VALUE 430

extern byte hxPins[2];

static long drift;

void hxReport(float mass)
{
	Serial.print("HX711 reports:\n");
	Serial.print("--The mass is ");
	Serial.print(mass, 4);
	Serial.print("kg.\n");
}

long getCount()
{
	long count = 0;
	digitalWrite(HX711_DT, HIGH);	
	digitalWrite(HX711_SCK, LOW);	
	while (digitalRead(HX711_DT));
	for (byte i = 0; i<24; i++)
	{
		digitalWrite(HX711_SCK, HIGH);		
		count <<= 1;
		digitalWrite(HX711_SCK, LOW);		
		if (digitalRead(HX711_DT))
			count++;
	}
	digitalWrite(HX711_SCK, HIGH);
	count ^= 0x800000;	
	digitalWrite(HX711_SCK, LOW);	
	return(count);
}

float getMass(bool report = true)
{
	float mass = (getCount() - drift) / GAP_VALUE;
	mass /= 1000;
	if (report)
	{
		hxReport(mass);
	}
	return mass;
}

void hxInit()
{
	pinMode(HX711_SCK, OUTPUT);
	pinMode(HX711_DT, INPUT);
	delay(1000);
	drift = getCount();
	Serial.print("HX711 reports:\n");
	Serial.print("--I am OK!\n");
}

#endif
