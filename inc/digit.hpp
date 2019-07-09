#define LENGTH 4
#define A 10
#define B 11
#define C 12
#define D 13
#define E 14
#define F 15
#define G 16
#define U 17
#define MINUS 18
#define EMPTY 19
byte number[LENGTH];
const byte digits[20][8] =
{
	{ 0,1,1,1,1,1,1,0 },
{ 0,0,1,1,0,0,0,0 },
{ 0,1,1,0,1,1,0,1 },
{ 0,1,1,1,1,0,0,1 },
{ 0,0,1,1,0,0,1,1 },
{ 0,1,0,1,1,0,1,1 },
{ 0,1,0,1,1,1,1,1 },
{ 0,1,1,1,0,0,0,0 },
{ 0,1,1,1,1,1,1,1 },
{ 0,1,1,1,1,0,1,1 },
{ 0,1,1,1,0,1,1,1 },
{ 0,0,0,1,1,1,1,1 },
{ 0,1,0,0,1,1,1,0 },
{ 0,0,1,1,1,1,0,1 },
{ 0,1,0,0,1,1,1,1 },
{ 0,1,0,0,0,1,1,1 },
{ 0,1,0,1,1,1,1,0 },
{ 0,0,1,1,1,1,1,0 },
{ 0,0,0,0,0,0,0,1 },
{ 0,0,0,0,0,0,0,0 },
};
extern byte digitPins[8];
extern byte numberPins[LENGTH];
void disp(byte i, byte j)
{
	digitalWrite(numberPins[i], 0);
	for (byte k = 0; k<8; k++)
		digitalWrite(digitPins[k], digits[j][k]);
	delay(5);
	digitalWrite(numberPins[i], HIGH);
}
void bug()
{
	disp(3, EMPTY);
	disp(2, B);
	disp(1, U);
	disp(0, G);
}
void show(int i)
{
	if (i < -999 | i > 9999)
		bug();
	else
	{
		if (i < 0)
		{
			show(-i);
			disp(MINUS, 3);
		}
		else
		{
			for (byte k = 0; k<LENGTH; k++)
			{
				number[k] = i % 10;
				i /= 10;
			};
			for (byte k = LENGTH; k; k--)
			{
				byte j = 0;
				if (k=0|number[k])
				{
					j = 1;
					disp(k, number[k]);
				}
				else
					disp(k, EMPTY);
			}
		}
	}
}
