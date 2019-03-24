#include "address_map_arm.h"
#include <stdio.h>
#include <time.h>

//All the DE-10 Components needed
volatile int* buttons = (int*)KEY_BASE;
volatile int* switches = (int*)SW_BASE;
volatile int* left7Display = (int*)HEX5_HEX4_BASE;
volatile int* right7Display = (int*)HEX3_HEX0_BASE;
volatile int* hpsTimer = (int*)HPS_TIMER0_BASE;

void DisplayHex(int value) {
	//The table only has A, D, G line values
	unsigned char table[] = { 0x01, 0x40, 0x08 };

	//Different Levels
	int counter = 5;
	int level = 1;

	//If stage is completed, counter is decremented. Once counter == 0, new level
	//The difference in levels is the speed of the game and the number of gametabs generated
	srand(time(NULL));

	switch(level){
	case 1 : //this is level 1
		break;
	case 2:
		break;
	case 3:
		break;
	default: //Anything higher than level 3 increases pace at each counter rather than each level progression
		break;
	}
	int gameTab = rand() % 3;

	//clock operates at 100MHZ
	//60 seconds in a minute
	//thus to trigger every minute, its value / 6000 x 10^6
	unsigned int minutes = value / 6000000000;
	value = value - minutes * 6000000000;
	unsigned int seconds = value / 100000000;
	value = value - seconds * 100000000;
	unsigned int msec = value / 1000000;

	//minutes
	firstDigit = minutes % 10;
	secondDigit = (minutes - firstDigit) / 10;
	*((int*)HEX5_HEX4_BASE + 1) = table[firstDigit];
	*((int*)HEX5_HEX4_BASE + 0) = table[secondDigit];

	//seconds
	firstDigit = seconds % 10;
	secondDigit = (seconds - firstDigit) / 10;
	*((int*)HEX3_HEX0_BASE + 3) = table[firstDigit];
	*((int*)HEX3_HEX0_BASE + 2) = table[secondDigit];

	//hundredths
	firstDigit = hundreths % 10;
	secondDigit = (hundreths - firstDigit) / 10;
	*((int*)HEX3_HEX0_BASE + 1) = table[firstDigit];
	*((int*)HEX3_HEX0_BASE + 0) = table[secondDigit];
}


int main(void) {

	//timer setup
	*((int*)(HPS_TIMER0_BASE + 0)) = UINT_MAX;
	*((int*)(HPS_TIMER0_BASE + 2)) = 0b011;

	while (1) {
		//Start
		if ((buttons & (1 << 0)) >> 0) { //on push
			*((int*)(HPS_TIMER0_BASE + 2)) = 0b011; //enable
		}
		//Stop
		else if ((buttons & (1 << 1)) >> 1) {
			*((int*)(HPS_TIMER0_BASE + 2)) = 0b010; //disable
		}
		else {
			DisplayHex(UINT_MAX - *((int*)(HPS_TIMER0_BASE + 1)));
		}
	}

