#ifndef MAIN_HPP
#define MAIN_HPP

#include <Arduino.h>
#include "keypad.hpp"
#include "HX711.hpp"
#include "LCD1602.hpp"

#define LENGTH_OF(array) sizeof(array)/sizeof(array[0])
#define OK '*'
#define CANCEL '#'
#define ADD_MONEY 'A'
#define BALANCE_CALIBRATE 'B'
#define CLEAR_DATA 'C'
#define DOT 'D'

byte rowPins[KEYPAD_ROWS] = { 11,10,9,8 };
byte colPins[KEYPAD_COLS] = { 7,6,5,4 };
byte hxPins[2] = { 3,2 };
byte lcdPins[6] = { A0,A1,A2,A3,A4,A5 };

unsigned long time = 0;
byte cycle = 0;

float tare = 0;
char massChar[LCD1602_COLS] = "";
String massStr = "";

float money = 0;
char moneyChar[LCD1602_COLS] = "";
String moneyStr = "";

String input = "";

float price = 0;
char priceChar[LCD1602_COLS] = "";
String priceStr = "";

char key = NULL;

void mcuReport()
{
	cycle++;
	Serial.print("MCU reports:\n");
	Serial.print("--Time past ");
	Serial.print(millis());
	Serial.print(" ms.\n");
	Serial.print("--Last loop cost ");
	Serial.print(millis()-time);
	time = millis();
	Serial.print(" ms.\n");
	Serial.print("--Loop ");
	Serial.print(cycle);
	Serial.print(" starts!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
}

void showMass(bool reportMass = true, bool reportDisp = true)
{
	dtostrf(getMass(reportMass) - tare, 2, 3, massChar);
	massStr = massChar;
	massStr += "kg";
	show(massStr, 0, 0, LCD1602_COLS / 2, true, reportDisp);
}

void showMoney(bool report = true)
{
	dtostrf(money, 3, 1, moneyChar);
	moneyStr = moneyChar;
	moneyStr += "RMB";
	show(moneyStr, 0, LCD1602_COLS / 2, LCD1602_COLS / 2, true, report);
}

void showInput(bool report = true)
{
	show(input, 1, 0, LCD1602_COLS / 2, true, report);
}

void showPrice(bool report = true)
{
	dtostrf(price, 2, 2, priceChar);
	priceStr = priceChar;
	priceStr += "RPK";
	show(priceStr, 1, LCD1602_COLS / 2, LCD1602_COLS / 2, true, report);
}

void setup()
{
	Serial.begin(9600);
	Serial.print("Serial reports:\n");
	Serial.print("--I am OK!\n");
	lcdInit();
	hxInit();
	keypadInit();
	showMoney();
	showPrice();
}

#endif
