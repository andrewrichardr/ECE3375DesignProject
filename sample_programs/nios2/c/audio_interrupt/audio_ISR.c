#include "address_map_nios2.h"
#include "globals.h"

/* globals used for audio record/playback */
extern volatile int record, play, buffer_index;
extern volatile int left_buffer[];
extern volatile int right_buffer[];

/*******************************************************************************
 * Audio - Interrupt Service Routine                                
 *                                                                          
 * This routine either records or playback audio data
 ******************************************************************************/
void audio_ISR( void )
{
	volatile int * audio_ptr = (int *) AUDIO_BASE;		// audio port address
  	volatile int * red_LED_ptr = (int *) LED_BASE;		// red LED address
	
	int fifospace, leftdata, rightdata;

	if (*(audio_ptr) & 0x100)							// check bit RI of the Control register
	{
		if (buffer_index == 0)
			*(red_LED_ptr) = 0x1;						// turn on LEDR[0]

		fifospace = *(audio_ptr + 1);					// read the audio port fifospace register
		// store data until the the audio-in FIFO is empty or the buffer is full
		while ( (fifospace & 0x000000FF) && (buffer_index < BUF_SIZE) )
		{
			left_buffer[buffer_index] = *(audio_ptr + 2); 		
			right_buffer[buffer_index] = *(audio_ptr + 3); 		
			++buffer_index;

			if (buffer_index == BUF_SIZE)
			{
				// done recording
				record = 0;
				*(red_LED_ptr) = 0x0;					// turn off LEDR
				*(audio_ptr) = 0x0; 					// turn off interrupts
			}
			fifospace = *(audio_ptr + 1);				// read the audio port fifospace register
		}
	}
	if (*(audio_ptr) & 0x200)							// check bit WI of the Control register
	{
		if (buffer_index == 0)
			*(red_LED_ptr) = 0x2;						// turn on LEDR[1]
		fifospace = *(audio_ptr + 1);					// read the audio port fifospace register
		// output data until the buffer is empty or the audio-out FIFO is full
		while ( (fifospace & 0x00FF0000) && (buffer_index < BUF_SIZE) )
		{
			*(audio_ptr + 2) = left_buffer[buffer_index];
			*(audio_ptr + 3) = right_buffer[buffer_index];
			++buffer_index;
	
			if (buffer_index == BUF_SIZE)
			{
				// done playback
				play = 0;
				*(red_LED_ptr) = 0x0;					// turn off LEDR
				*(audio_ptr) = 0x0; 					// turn off interrupts
			}
			fifospace = *(audio_ptr + 1);				// read the audio port fifospace register
		}
	}
	return;
}
