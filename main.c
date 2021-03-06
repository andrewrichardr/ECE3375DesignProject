#include "address_map_arm.h"
#include <stdio.h>
#include <time.h>
#include "lcd_driver.h"
#include "lcd_graphic.h"
#include <string.h>

//All the DE-10 Components needed
volatile int* buttons = (int*)KEY_BASE;
volatile int* switches = (int*)SW_BASE;
volatile char* left7Display = (int*)HEX5_HEX4_BASE;
volatile char* right7Display = (int*)HEX3_HEX0_BASE;
volatile int* hpsTimer = (int*)HPS_TIMER0_BASE;

int setHit = 0;
int score = 0;
int combo = 0;
int misHit = 0;
int lives = 20;
char liveFeedback[17]; //Miss, Perfect 
int breakBool = 0;

void StaticDisplay() {

	//Testing bitwise shift operations
	*(right7Display + 1) = 0x30;

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
		*(right7Display + 1) = 0x30;

	}
	else if (place > 2 && place < 5) {
		place = place - 1;
		*(right7Display + place) = table[value];
	}
	else if (place == 2) {
		place = place - 1;
		*(right7Display + place) = specialTable[value];
	}
	else {
		if (setHit == 0) {
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
	int button_delay;
	int i;
	misHit = 0;

	for (i = 6; i > 0; i--) {

		if (!(*(switches) & 2)) {
			return;
		}
		DELAY_LENGTH = speed;

		if (i == 6) {
			DELAY_LENGTH = speed / 10000;
		}

		for (delay_count = DELAY_LENGTH; delay_count != 0; --delay_count) {
			//Top Button


			if (*buttons & 8) {
				buttonPress(2);
				if (i == 1 && tab == 2) {
					setHit = 1;
					liveFeedback[17] = "   PERFECT \0";
				}
				else {
					misHit = 1;
					liveFeedback[17] = "    MISS \0";

				}
			}
			if (*buttons & 4) {
				buttonPress(1);
				if (i == 1 && tab == 1) {
					setHit = 1;
					liveFeedback[17] = "   PERFECT \0";
				}
				else {
					misHit = 1;
					liveFeedback[17] = "    MISS \0";

				}
			}
			if (*buttons & 3) {
				buttonPress(0);
				if (i == 1 && tab == 0) {
					setHit = 1;
					liveFeedback[17] = "    PERFECT \0";
				}
				else {
					misHit = 1;
					liveFeedback[17] = "    MISS \0";

				}
			}
		}

		if (misHit) {
			lives--;
			combo = 0;
		}

		if (setHit == 1) {
			score += 5;
			combo++;
		}
		//FIGURE OUT COMBO LOGIC AND THE LOGIC TO SWITCH LCD TEXT

		if (i == 1 && setHit == 0) {
			lives = lives - 2;
		}

		TabDisplay(tab, i);
	}

}

void lcdGameInformation(int level) {
	char levelChar[17] = "    LEVEL:  \0";
	char scoreChar[17] = "Score: \0";
	char livesChar[17] = "Lives: \0";

	sprintf(levelChar, "    Level: %i \0", level);
	sprintf(scoreChar, "Score: %i \0", score);
	sprintf(livesChar, "Lives: %i \0", lives);
	LCD_text(levelChar, 1);
	LCD_text(scoreChar, 3);
	LCD_text(livesChar, 5);
	refresh_buffer();
}

void lcdGameFeedback() {
	char comboChar[17];
	sprintf(comboChar, "Combo: %i \0", combo);
	if (*(switches) & 1) {
		clear_screen();
		LCD_text(liveFeedback, 3);
		LCD_text(comboChar, 4);
		refresh_buffer();
	}
	else {
		return;
	}
}

void gamePlayer(int speed) {
	int gameTab = rand() % 3;
	setHit = 0;
	animateTab(gameTab, speed);
	if (!(*(switches) & 2)) {
		breakBool = 1;
	}
	if (lives <= 0) {
		breakBool = 1;
		char endGame[17] = "    Y0U L0SE   \0";
		clear_screen();
		LCD_text(endGame, 4);
		refresh_buffer();
	}
}

int main() {
	//Different Levels
	int level = 1;
	int repeat = 1;
	srand(time(NULL));

	char text_top_lcd[17] = "   Welcome To   \0";
	char text_bottom_lcd[17] = "  GEETAR Her0   \0";
	char text_instruc_top[17] = " Instructions: \0";
	char text_instruc_1[17] = "Flip 2nd switch \0";
	char text_instruc_2[17] = "   20 Lives \0";
	char text_instruc_3[17] = "Don't spam btns\0";


	init_spim0();
	init_lcd();
	clear_screen();
	refresh_buffer();


	//If stage is completed, counter is decremented. Once counter == 0, new level
	//The difference in levels is the speed of the game and the number of gametabs generated

	while (lives > 0) {
		int counter = 0;
		LCD_text(text_top_lcd, 0);
		LCD_text(text_bottom_lcd, 1);
		LCD_text(text_instruc_top, 3);
		LCD_text(text_instruc_1, 4);
		LCD_text(text_instruc_2, 5);
		LCD_text(text_instruc_3, 6);
		refresh_buffer();

		if (*(switches) & 2) {
			clear_screen();

			switch (level) {
			case 1: //this is level 1
				counter = 5;
				while (counter) {
					lcdGameInformation(1);
					lcdGameFeedback();

					gamePlayer(700000);
					counter--;
					if(breakBool){
						break;
					}
					printf("counter: %i", counter);
				}
				level = 2;
				break;
			case 2:
				counter = 5;
				while (counter) {
					lcdGameInformation(2);
					lcdGameFeedback();

					gamePlayer(350000);
					counter--;
					if(breakBool){
						break;
					}
				}
				level = 3;
				break;
			case 3:
				counter = 10;
				while (counter) {
					lcdGameInformation(3);

					lcdGameFeedback();

					gamePlayer(170000);
					counter--;
					if(breakBool){
						break;
					}

				}
				level = 4;
				break;
			case 4:
				counter = 15;
				while (counter) {
					lcdGameInformation(4);
					lcdGameFeedback();
					gamePlayer(15000);
					counter--;
					if(breakBool){
						break;
					}
				}
				break;
			}
		}
		//Does user want to restart the game?
		int restart_delay;
		if (*(switches) & 4 && lives <= 0) {
			for (restart_delay = 10000000000; restart_delay != 0; --restart_delay);
			score = 0;
			lives = 20;
			level = 1;
			breakBool = 0;
		}
		refresh_buffer();
	}

	return 0;
}
