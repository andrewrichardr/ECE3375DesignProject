#include "address_map_arm.h"
#include <stdio.h>
#include <time.h>

//All the DE-10 Components needed
volatile int* buttons = (int*)KEY_BASE;
volatile int* switches = (int*)SW_BASE;
volatile char* left7Display = (char*)HEX5_HEX4_BASE;
volatile char* right7Display = (char*)HEX3_HEX0_BASE;
volatile int* hpsTimer = (int*)HPS_TIMER0_BASE;

void StaticDisplay() {
	//The table only has A, D, G line values
	
	*(right7Display) = 0x00;
	*(right7Display+1) = 0x30;

}

void TabDisplay(int value, int place){
	unsigned char table[] = { 0x01, 0x40, 0x08 };
	*(left7Display) = 0x00;
	*(left7Display+1) = 0x00;
	*(right7Display+3) = 0x00;
	*(right7Display+2) = 0x00;
	
	StaticDisplay();
	
	if(place >=5 ){
	place = place - 5;
	*(left7Display + place) = table[value];
	}
	else{
		place = place - 1;	
	*(right7Display + place) = table[value];
	}
	
}

int main(){
	//Different Levels
	int counter = 5;
	int level = 1;
	
	
	
	//TESTING
	int DELAY_LENGTH = 7000000;
	int delay_count;

	//If stage is completed, counter is decremented. Once counter == 0, new level
	//The difference in levels is the speed of the game and the number of gametabs generated
	srand(time(NULL));
	
	
	while(1){
		int i = 6;
		for(i = 6; i > 2; i--){
			TabDisplay(1, i);
			
			for(delay_count = DELAY_LENGTH; delay_count != 0; --delay_count)
			;
		}
		
		
		
	}
	StaticDisplay();
	TabDisplay(0, 4);

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
	

