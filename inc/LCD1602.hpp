#ifndef LCD1602_HPP
#define LCD1602_HPP

#include <Arduino.h>
#include <LiquidCrystal.h>

#define LCD1602_ROWS 2
#define LCD1602_COLS 16

extern byte lcdPins[6];

extern LiquidCrystal lcd(lcdPins[0], lcdPins[1], lcdPins[2], lcdPins[3], lcdPins[4], lcdPins[5]);

void lcdReport(String display)
{
	Serial.print("LCD1602 reports:\n");
	Serial.print("--The display is \"");
	Serial.print(display);
	Serial.print("\".\n");
}

void show(String display, int x = 0, int y = 0, int length = LCD1602_COLS / 2, bool rightline = true, bool report = true)
{
	lcd.setCursor(y, x);
	String str = "";
	if (rightline && length > display.length())
	{
		for (byte k = 0; k < length - display.length(); k++)
		{
			str += " ";
		}
	}
	str += display.substring(0, length);
	lcd.print(str);
	if (report)
	{
		lcdReport(str);
	}
}

void lcdInit()
{
	lcd.begin(16, 2);
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Welcome to use!");
	delay(1000);
	lcd.clear();
	Serial.print("LCD1602 reports:\n");
	Serial.print("--I am OK!\n");
}

#endif
