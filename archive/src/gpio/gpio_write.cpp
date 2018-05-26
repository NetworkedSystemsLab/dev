// exampleApp.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include "gpio_jetson_library.h"
using namespace std;



int main(int argc, char *argv[]){

    cout << "Testing the GPIO Pins" << endl;

    
    jetsonTX1GPIONumber redLED = gpio398 ;     // Ouput

    gpioExport(redLED) ;
    
    gpioSetDirection(redLED, 1) ;
	
    unsigned short int num = 10;
    bool rem = 0 ;

    // Flash the LED 5 times
    for(int i=0; i<30; i++){

	rem = num % 2;
	num /= 2;

        cout << "Setting the LED on" << endl;
        gpioSetValue(redLED, rem);
        usleep(1000000);         // on for 200ms
   //     cout << "Setting the LED off" << endl;
   //     gpioSetValue(redLED, off);
   //     usleep(200000);         // off for 200ms
    }

    cout << "GPIO example finished." << endl;
    gpioUnexport(redLED);     // unexport the LED
    return 0;
}


