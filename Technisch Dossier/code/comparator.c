#include "main.h"

int measure2 = 0;

ISR(PORTB_INT0_vect)
{
	PORTC_OUTTGL = PIN2_bm;
	TCD0.CNT = 0;
	overflow = 0;
	start_measure = 1;
	period = 0;
	measure2 = 0;
	measure = 0;
}

ISR(TCD0_OVF_vect)
{
	overflow = overflow+1;
}

ISR(ACA_AC0_vect)
{
	if (ACA.STATUS & AC_AC0STATE_bm){
		count++;
		if (count == 0){
			TCC0.CNT = 0;
		}
		else if (count == 1){
			period = TCC0.CNT;
			count = 0;
			TCC0.CNT = 0;
			measure2++;
			if ( period < 1000 && period > 900){
				measure++;
			}
		}
	}
}

int main(void)
{
	SystemClock_init();								// initialize 32MHz clock
	uart_init();									// initialize UART
	init_ac();
	stdout = &mystdout;
	
	//timer TBV het meten van de frequentie
	TCC0.CTRLA = TC_CLKSEL_DIV8_gc;					// prescaling 8
	TCC0.PER = 0XFFFF;								// maximal value
	
	//timer TBV het meten van de overdrachtstijd
	TCD0.CNT = 0;									// Timer/counter D0 value is 0
	TCD0.CTRLA = TC_CLKSEL_DIV1_gc;					// prescaling 1
	TCD0.PER = 0xffff;								// maximal value
	TCD0.INTCTRLA = TC_OVFINTLVL_HI_gc;				// high level overflow interrupt

	//interrupt TBV het resetten van de timers bij startup
	PORTB.INT0MASK = PIN0_bm | PIN1_bm;
	PORTB.PIN0CTRL = PORT_ISC_RISING_gc;
	PORTB.INTCTRL = PORT_INT0LVL_HI_gc;
	
	PMIC.CTRL |= PMIC_LOLVLEN_bm | PMIC_HILVLEN_bm;
	sei();
	
	PORTC_DIRSET = PIN0_bm;
	while (1) {
		if (period > 5000 && measure >= 1000  && start_measure == 1 /*&& period > 850*/){
			start_measure = 0;
			time = TCD0.CNT+(overflow*0xffff);
			PORTC_OUTTGL = PIN0_bm;
			printf("Time: %lu\n measure: %d\nmeasure2: %d\n", time, measure, measure2);
			cli();
			measure = 0;
			measure2 = 0;
			sei();
		}
	}
}