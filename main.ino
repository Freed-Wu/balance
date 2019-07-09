/*
  Name:		main.ino
  Created:	2018/6/6 0:33:39
  Author:	Wu Zhenyu
*/
#include "inc/main.hpp"
void loop()
{
	//mcuReport();
	showMass(false, false);

	key = keypad.getKey();
    if (key != NO_KEY)
    {
		keypadReport(key);
		switch (key)
		{
		case OK:
			price = atof(input.c_str());
			showPrice();

		case CANCEL:
			input = "";
			showInput();
			break;

		case ADD_MONEY:
			money += price * (getMass() - tare);
			showMoney();
			break;

		case BALANCE_CALIBRATE:
			tare = getMass();
			break;

		case CLEAR_DATA:
			tare = 0;
			money = 0;
			showMoney();
			break;

		case DOT:
			key = '.';

		default:
			input += key;
			showInput();
		}
    }
}
