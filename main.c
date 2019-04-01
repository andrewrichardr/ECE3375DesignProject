#include "address_map_arm.h"
#include <stdio.h>
#include <time.h>

//All the DE-10 Components needed
volatile int* buttons = (int*)KEY_BASE;
volatile int* switches = (int*)SW_BASE;
volatile char* left7Display = (int*)HEX5_HEX4_BASE;
volatile char* right7Display = (int*)HEX3_HEX0_BASE;
volatile int* hpsTimer = (int*)HPS_TIMER0_BASE;

void StaticDisplay() {
	
	//Testing bitwise shift operations
	*(right7Display + 1)= 0x30;

}

void TabDisplay(int value, int place) {
	//The table only has A, D, G line values
	unsigned char table[] = { 0x01, 0x40, 0x08 };
	unsigned char specialTable[] = { 0x31, 0x70, 0x38 };

	//Clear all the displays
	*left7Display = 0x00;
	*(left7Display + 1) = 0x00;
	*(right7Display + 3) = 0x00;
	*(right7Display + 2) = 0x00;

	//Set the static Display
	StaticDisplay();
	//Testing value of place
	printf("%d \n", place);


	if (place > 5) {
		place = place - 5;
		*(left7Display + place) = table[value];
	}
	else if (place == 5) {
		*left7Display = table[value];
		*(left7Display + 1) = 0x00;
		*(right7Display) = 0x00;
		*(right7Display + 1)= 0x30;

	}
	else if (place > 2 && place < 5) {
		place = place - 1;
		*(right7Display + place) = table[value];
	}
	else if (place == 2){
		place = place - 1;
		*(right7Display + place) = specialTable[value];
	}
	else{
		place = place - 1;
		*(right7Display + place) = table[value];
	}
}

//Aimmate tab through the 7-seg display at pace defined by speed
void buttonPress(int button) {
	unsigned char table[] = { 0x31, 0x70, 0x38 };

	*(right7Display + 1) = table[button];
	
	*(right7Display + 1) = 0x30;
}

void animateTab(int tab, int speed) {

	int DELAY_LENGTH = speed;
	int delay_count;
	int i;
	for (i = 6; i > 0; i--) {
		TabDisplay(tab, i);
		
		for (delay_count = DELAY_LENGTH; delay_count != 0; --delay_count){
			if (*buttons & 8) {
			buttonPress(2);
		}
		else if (*buttons & 4) {
			buttonPress(1);
		}
		else if (*buttons & 3) {
			buttonPress(0);
		}

		}
	}

}



int main(){
	//Different Levels
	int counter = 5;
	int level = 1;
	
	srand(time(NULL));
	
	
	//If stage is completed, counter is decremented. Once counter == 0, new level
	//The difference in levels is the speed of the game and the number of gametabs generated
	
	
	
	while(1){
		int i = 6;
		int gameTab = rand() % 3;
		animateTab(gameTab, 700000);	
	}

	switch(level){
	case 1 : //this is level 1
		while (1) {
			//game starts

			//Initialize the timer
			*(hpsTimer + 2) = 0b010;
			*(hpsTimer) = 10000000; //approx 1/10 second

			//Get the gametab randomly generated
			int gameTab = rand() % 3;

			//Pass it to hex and start the timer
			
			
		}
		break;
	case 2:
		break;
	case 3:
		break;
	default: //Anything higher than level 3 increases pace at each counter rather than each level progression
		break;
	}
	
	DisplayHex(0);
	
	return 0;
}
	
