/**************************************************
 * Sinus Generator
 * For Distance Measurement
 * Created: 14-6-2016 11:01:46
 * Author: Zwermen 2
**************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "clk.h"
#include "UART.c"

#define F_CPU 32000000UL

uint16_t sin4kHz[50] = {4,36,100,195,319,470,646,844,1061,1294,1538,1791,
2048,2304,2557,2801,3034,3251,3449,3625,3776,3900,
3995,4059,4091,4091,4059,3995,3900,3776,3625,3449,
3251,3034,2801,2557,2304,2048,1791,1538,1294,1061,
844,646,470,319,195,100,36,4};

int SEND_COUNT = 0;
int MAX_IDX = 50;
volatile int count = 0;
uint8_t idxsin = 0;

ISR (TCC0_CCC_vect)
{													// Timer overflow, put next sample into DAC
	PORTB_OUTSET = PIN0_bm;
	MAX_IDX = 50;
	DACB.CH0DATA = sin4kHz[idxsin];
	idxsin++;
	if (idxsin >= MAX_IDX) { idxsin = 0; }

}

ISR (TCD1_CCA_vect)									// period timer
{
	if (count <= 250 && SEND_COUNT < 10){
		PORTB_OUTSET = PIN0_bm;
		count++;
		SEND = 1;
	}
	
	if (250 < count && count <= 1000 && SEND_COUNT < 10){
		PORTB_OUTCLR = PIN0_bm;
		count++;
		SEND = 0;
	}
	
	if (count > 4000 && SEND_COUNT < 10){
		count = 0;
		SEND_COUNT++;
		DACB.CH0DATA = 0;
	}
	
	if (SEND_COUNT == 10){
		DACB.CH0DATA = 0;		
	}
}

int main(void)
{
	SystemClock_init();
	TCC0.CNT = 0; 									//Reset timer 0
	TCC0.PER = 160; 								//188235Hz
	TCC0.CTRLA = TC_CLKSEL_DIV1_gc; 				//Prescaler
	TCC0.INTCTRLB = TC_CCCINTLVL_LO_gc; 			//TCC0_CCC_vect, Compare Match
	
	TCD1.CNT = 0; 									//Reset timer
	TCD1.PER = 0x2134; 								//3764Hz
	TCD1.CTRLA = TC_CLKSEL_DIV1_gc; 				//Prescaler
	TCD1.INTCTRLB = TC_CCAINTLVL_LO_gc; 			//TCD0_CCA_VECT, Compare Match

	PMIC.CTRL = PMIC_LOLVLEN_bm;
	sei();

	DACB.CTRLB = 0x00; 								//Single channel operation PB2 only
	DACB.CTRLC = 0x08; 								//Vref = Analog Supply Voltage
	DACB.CTRLA = 0x04; 								//CH0EN = Enable Channel 0
	DACB.CTRLA |= 0x01; 							//ENABLE = Start the DAC

	uart_init();
	stdout = &mystdout;
	
	PORTB_DIRSET = PIN0_bm;
	
	while(1)
	{
		asm volatile ("nop");
	}
}