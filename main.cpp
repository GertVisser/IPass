#include "hwlib.hpp"
#include "frequency.hpp"
#define ARRAY_SIZE 10

//function to set the output for the led's based on found frequency
int ledset(int freq, int found){
    if (found <=freq+4 and found >= freq-4) {
        return 4;
    }
    else if(found <=freq+10 and found >= freq+4) {
        return 2;
    }
    else if(found >= freq+10) {
        return 1;
    }
    else if(found <=freq-10 and found >= freq-4) {
        return 8;
    }
    else if(found <=freq-10) {
        return 16;
    }
    return 0;
}

int main( void ){
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    //set namespace
	namespace target = hwlib::target; 
    // set GPIO pins as output
	auto led0 = target::pin_out(target::pins::d8);
    auto led1 = target::pin_out(target::pins::d9);
    auto led2 = target::pin_out(target::pins::d10);
    auto led3 = target::pin_out(target::pins::d11);
    auto led4 = target::pin_out(target::pins::d12);
    auto leds = hwlib::port_out_from_pins(led0,led1,led2,led3,led4);
    
    //set GPIO pins as input
    auto but1 = target::pin_in(target::pins::d2);
    auto adc0 = target::pin_adc( target::ad_pins::a0 );
    
    //set up the Oled display
    auto scl     = target::pin_oc( target::pins::scl );
    auto sda     = target::pin_oc( target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto oled    = hwlib::glcd_oled( i2c_bus, 0x3c ); 
    auto font    = hwlib::font_default_8x8();
    auto display = hwlib::window_ostream( oled, font );
    
    //values for string selection
    char note[] = {'E','A','D','G','B','e'};
    int freqs[] = {82,110,146,196,247,326};
    int i=0;
    
    for(;;){
        //set values for note and wanted frequency
        char x = note[i];
        int y = freqs[i];
        
        //declare array for measurements and wait
        int a[ARRAY_SIZE];
        hwlib::wait_ms(500);
        
        //fill the array with measurements and calculate frequency
        for(int i = 0; i < ARRAY_SIZE; i++){ 
            a[i] = adc0.get();
            hwlib::wait_us( 10 );
        }
        frequency sig((&a)[0]);
        int freq = sig.calc_frequency();
        
        //upon button press, change string to be tuned
        if(but1.get()==0){
            hwlib::wait_ms( 500 );
            i++;
            if(i>5){
                i=0;
            }
        }
        //update the tuner's led's
        leds.set(ledset(y,freq));
        
        //update the tuner's display
        display 
            << "\f" << "InTune" 
            << "\t0302" << "string "<<x 
            << "\t0303" << y <<"Hz"
            << "\t0305" << freq << "Hz Found"
            << hwlib::flush;
   }
}