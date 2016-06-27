/**************************************************
 * Simple Correlation.c
 * Created: 14-6-2016 11:01:46
 * Author: Zwermen 2
 **************************************************/

#include <avr/io.h>
#include <stdio.h>
#include "correlation.h"

uint16_t correlation (int16_t adc_arraylength, int16_t raw_arraylength, const uint16_t rawdata[], volatile int16_t Filtereddata[]){
	volatile int i = 0, k = 0, timeshift = 0;; 
	volatile int32_t sum = 0, sum_old = 0, sum_1 = 0, sum_2 = 0;

	for(i = 0; i < adc_arraylength-1; i++){
		sum = 0;
		for(k = 0; k < raw_arraylength; k++){		
			sum_1 = rawdata[k];
				
			if((k+i) > adc_arraylength){
				sum_2 = 0;
			}
			else{
				sum_2 = Filtereddata[k+i];
			}
				
			sum += (sum_1)*(sum_2);
		}
		
		if (sum >= sum_old){
			timeshift = i;
			sum_old = sum;
		}
	}
	if(i >= adc_arraylength-1){
		return timeshift;	
		for(int j = 0; j >= adc_arraylength; j++){
			adc_arraylength[j] = 0;
		}
	}
	return 0;
}
	