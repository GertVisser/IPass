#ifndef FREQUENCY_HPP
#define FREQUENCY_HPP
#include "hwlib.hpp"
#define ARRAY_SIZE 10
/// @file


///Class for calculating frequency, average and maybe more.
//
///This class is used to store data received from an Arduino Due ADC
///this class should only be used for soundwaves, succes is not assured if
///it is used for any other kind of wave


/// All characteristics of this class are private
/// and are only made visible by the class's functions.
/// All function definitions can be found in the Frequency_pin.cpp file.
 

class frequency {
private:
	int (&a)[ARRAY_SIZE];
	int total;
	int deviation;
	int crossover;
	int found_freq;
	int average;
public:
	/// Constructor
	//
    ///The constructor builds the class using an array
    ///Characteristics are set to 0 to prevent errors
	frequency( int (&arr)[ARRAY_SIZE], int total = 0, int deviation = 0, int crossover = 0, int found_freq = 0, int average = 0);
	
	/// Calculate the average value
	//
    ///This function calculates the average found value, it then returns it to be used in other functions.
	int calc_average();
	
	/// Calculate frequency
	//
    ///This function calculates the frequency of an input to a value in Hz and return it.
    ///It starts by calling the calc_average() function,
    ///it then compares how many times it passed the average value, 
    ///the resulting value is then multiplied by a calibration value
    ///if this function returns absurd or incorrect values, try to calibrate with
    ///a frequency of 400hz, you will have to change the calibration value until
    ///this function returns the right values
	int calc_frequency();

};

#endif // FREQUENCY_HPP
