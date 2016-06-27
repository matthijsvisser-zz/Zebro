/**************************************************
Histogram Filter Function
Cross Correlation
For distance measurements
Created: 20-06-2016
Author: Zwermen 2
**************************************************/

#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stddef.h>
#include <stdio.h>

#include "quicksort.h"


void swap(volatile int16_t a[], uint16_t i, uint16_t j){
	uint16_t tmp;

	tmp  = a[i];
	a[i] = a[j];
	a[j] = tmp;
}
void quickSort(volatile int16_t a[], int16_t left, int16_t right) {
	int16_t i;
	int16_t j;
	int16_t v;

	if(right > left) {
		v = a[right];
		i = left -1;
		j = right;
		while(1){
			while (a[++i] < v);
			while (a[--j] > v);
			if ( i >= j)
			{
				break;
			}
			swap(a,i,j);
		}
		swap(a,i,right);
		quickSort(a,left,i-1);
		quickSort(a, i+1, right);
	}
}

uint16_t filter(volatile int16_t nums[], uint16_t size) {
	uint16_t k, samples = 0;
	uint32_t sum = 0;

	for(k = (size / 10); k < (size - (size / 5)); k++) {
		sum += nums[k];
		samples++;
	}

	return (uint16_t)(sum / (uint32_t)samples);
}