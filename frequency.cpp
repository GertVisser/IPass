#include "frequency.hpp"
#include "hwlib.hpp"

frequency::frequency(int (&arr)[ARRAY_SIZE], int total, int deviation, int crossover, int found_freq, int average) :
	a( arr ),
	total(total),
	deviation(deviation),
	crossover(crossover),
	found_freq(found_freq),
	average(average)
{}

int frequency::calc_average() {
	total = 0;
    //iterate through array and add each value to total
	for (int i = 0; i < ARRAY_SIZE; i++) {
		total = total + a[i];
	}
	//calculate average by dividing with array size
	average = total / ARRAY_SIZE;
	return average;
}

int frequency::calc_frequency() {
	crossover = 0;
	average = calc_average();
    //iterate throught array and check for average crossovers
	for (int i = 0; i < ARRAY_SIZE-1; i++) {
		if ((a[i] > average) && (a[i+1] < average)) {
			crossover++;
		}
		
		else if ((a[i] < average) && (a[i+1] > average)) {
			crossover++;
		}
	}
	//calculate frequency by multiplying with a calibrated value
	found_freq = crossover * 29;
	return found_freq;
}

