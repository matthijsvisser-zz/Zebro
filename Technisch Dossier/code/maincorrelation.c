/**************************************************
Implementation
Simplified Cross Correlation
For distance measurements
Created: 20-06-2016
Author: Zwermen 2
**************************************************/

#include "main.h"

void Config32MHzClock(void);

int main(void) {
	
	PORTB.INT0MASK = PIN0_bm;
	PORTB.PIN0CTRL = PORT_ISC_RISING_gc;
	PORTB.INTCTRL  = PORT_INT0LVL_HI_gc;
	
	PORTC_DIRSET = PIN0_bm; //Blue LED
	PORTF_DIRSET = PIN0_bm; //Green LED
	PORTF_DIRSET = PIN1_bm; //Red LED
	
	SystemClock_init();		// init 32MHz clock
	ADC_init();				// init ADC
	uart_init();			// init uart
	adc_timer_init();		// ADC timer init
	stdout = &mystdout;

	PMIC.CTRL |= PMIC_LOLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
	
while(1){
		if(measured >= MEASURES){
			measured = 0;
			quickSort(time_delay, 0, MEASURES - 1);
			time_shift = filter(time_delay, MEASURES);
			result = factor * (float) time_shift;
			int z = result*100;
	
			printf("Measured Distance:%dcm\n", z);
			
			for(int y = 0; y <= MEASURES; y++){
				time_delay[y] = 0;
			}
		}
	}
}
	
ISR(PORTB_INT0_vect)
{
	if(measure == 0){
		ADCdata[0] = ADC_read();
		samples = 1;
		PORTC_OUTTGL = PIN0_bm;
		TCD0.CNT = 0;
		measure = 1;
	}
}

ISR(TCD0_OVF_vect)
{
	if(measure == 1){
		ADCdata[samples] = ADC_read();
		samples++;
		
		if(samples > ADCLENGTH){
			cli();
			time_delay[measured] = correlation (ADCLENGTH, lenraw, rawdata, ADCdata);
			measured++;
			measure = 0;
			
			for(int i = 0; i <= ADCLENGTH; i++){
				ADCdata[i] = 0;
			}
			sei();
		}
	}
}