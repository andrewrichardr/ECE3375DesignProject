#include "address_map_arm.h"
#include <stdio.h>
#include <time.h>

//All the DE-10 Components needed
volatile int* buttons = (int*)KEY_BASE;
volatile int* switches = (int*)SW_BASE;
volatile char* left7Display = (int*)HEX5_HEX4_BASE;
volatile char* right7Display = (int*)HEX3_HEX0_BASE;
volatile int* hpsTimer = (int*)HPS_TIMER0_BASE;

int setHit = 0;
int score = 0;
int combo = 0;
int lives = 10000;

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
		if(setHit == 0){
			place = place - 1;
			*(right7Display + place) = table[value];
		}
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
		
		if(!(*(switches)&2)) {
			return;
		}
		
		for (delay_count = DELAY_LENGTH; delay_count != 0; --delay_count){
			//Top Button
			if (*buttons & 8) {
				buttonPress(2);
				if(i == 1 && tab == 2){
					setHit = 1;
					score += 5;
				}
				else{
					score -= 2;
				}
			}
			if (*buttons & 4) {
				buttonPress(1);
				if(i == 1 && tab == 1){
					setHit = 1;
					score += 5;
				}
				else{
					score -= 2;
				}
			}
			if (*buttons & 3) {
				buttonPress(0);
				if(i == 1 && tab == 0){
					setHit = 1;
					score += 5;
				}
				else{
					score -= 2;
				}
			}
		}
		
		if(i==1 && setHit == 0){
			lives--;
		}
		
		TabDisplay(tab, i);
	}

}



int main(){
	//Different Levels
	int level = 1;
	int counter;
	int repeat = 1;
	srand(time(NULL));
	
	//If stage is completed, counter is decremented. Once counter == 0, new level
	//The difference in levels is the speed of the game and the number of gametabs generated

	while(1){
	if(*(switches)&2){
		switch(level){
			case 1 : //this is level 1
				counter = 5;
				while(counter){
					int gameTab = rand() % 3;
					setHit = 0;
					animateTab(gameTab, 700000);	
					counter--;
					if(!(*(switches)&2)) {
						break;
					}
					if(lives == 0){
						break;
					}
					
					printf("%i \n", score);
					printf("%i \n", lives);
				}
				level = 2;
				break;
			case 2:
				counter = 5;
				while(counter){
					int gameTab = rand() % 3;
					setHit = 0;
					animateTab(gameTab, 350000);	
					counter--;
					if(!(*(switches)&2)) {
						break;
					}
					if(lives == 0){
						break;
					}
					
					printf("%i \n", score);
					printf("%i \n", lives);
				}
				level = 3;
				break;
			case 3:
				counter = 10;
				while(counter){
					int gameTab = rand() % 3;
					setHit = 0;
					animateTab(gameTab, 170000);	
					counter--;
					if(!(*(switches)&2)) {
						break;
					}
					if(lives == 0){
						break;
					}
					
					printf("%d \n", score);
					printf("%d \n", lives);
				}
				level = 4;
				break;
			case 4:
				counter = 15;
				while(counter){
					int gameTab = rand() % 3;
					setHit = 0;
					animateTab(gameTab, 10000);	
					counter--;
					if(!(*(switches)&2)) {
						break;
					}
					if(lives == 0){
						break;
					}
					
					printf("%d \n", score);
					printf("%d \n", lives);
				}
				level = 1;
				break;		
	}
	}
	}
	
	return 0;
}
