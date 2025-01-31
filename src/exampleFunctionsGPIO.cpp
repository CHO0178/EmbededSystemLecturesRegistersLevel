#include "exampleFunctionsGPIO.hpp"
#include "littleHelper.h"
#include <soc/io_mux_reg.h>

#define RGB_RED_PIN 25
#define RGB_GREEN_PIN 26
#define RGB_BLUE_PIN 27
#define BUTTON_PIN 19
#define BUTTON_MUX_REG REG(IO_MUX_GPIO19_REG)


void initDiode(int pin){
    // Set the GPIO pin of diode as output
    GPIO.enable |= (1 << pin);
}

void blinkDiode(int pin, int delay){
    // Set the GPIO pin of diode to high
    GPIO.out |= (1 << pin);
    for(int i = 0; i < delay; i++);
    // Set the GPIO pin of diode to low
    GPIO.out &= ~(1 << pin);
    for(int i = 0; i < delay; i++);
}

void initRGB(int R, int G, int B){
    // Set the GPIO pin of RGB diode as output
    GPIO.enable |= ((1 << R) | (1 << G) | (1 << B));
}

void setRGB(int R_pin, int G_pin, int B_pin, int R_val, int G_val, int B_val){
    // Set the GPIO pin of RGB diode to high
    int REG = GPIO.out;
    int DATA = (R_val << R_pin) | (G_val << G_pin) | (B_val << B_pin);
    int MASK = (1 << R_pin) | (1 << G_pin) | (1 << B_pin);
    GPIO.out = (REG & (~(MASK))) | (DATA & MASK);
}





/***************************************************************************************************************/
/***************************************************************************************************************/
/*                                           code examples                                                     */
/***************************************************************************************************************/
/***************************************************************************************************************/


/**
 * @brief example of blinking RGB diode. Blinking only Red then Green then Blue but nothing else
 */
void example00BlinkingRGBDiode(){
    initRGB(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);
    while(1){
        setRGB(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN,1,0,0);
        for(int i = 0; i < 10000000; i++);
        setRGB(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN,0,0,1);
        for(int i = 0; i < 10000000; i++);
        setRGB(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN,0,1,0);
        for(int i = 0; i < 10000000; i++);
    }

    
}



void example01DiodeWithButton(){
    // set input pullup for button pin
    initRGB(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);
    GPIO.enable &= ~(1 << BUTTON_PIN);
    //GPIO.func_in_sel_cfg[BUTTON_MUX_REG].sig_in_sel = BUTTON_MUX_REG;

    BUTTON_MUX_REG |= (1 << 8)|(1 << 9);
    

    while (1){

        if((GPIO.in & (1 << BUTTON_PIN))){
            GPIO.out |= (1 << RGB_RED_PIN)|(1 << RGB_GREEN_PIN)|(1 << RGB_BLUE_PIN);
        }
        else{
            GPIO.out &= ~((1 << RGB_RED_PIN)|(1 << RGB_GREEN_PIN)|(1 << RGB_BLUE_PIN));
        }
        blinkDiode(RGB_RED_PIN);
        // CZ: najděte chybu co by mohl být problém, které chování se vám nelíbí
        // EN: find the bug that could be a problem, what behavior do you not like
        // solution: the button does not react immediately, it is necessary to wait for the end of the blinking
    }
}

void example00DiodeWithButton(){
    initRGB(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);
    // CZ: nastavte pullup na tlačítku
    // EN: set input pullup for button pin
    GPIO.enable &= ~(1 << BUTTON_PIN);
    //GPIO.func_in_sel_cfg[BUTTON_MUX_REG].sig_in_sel = BUTTON_MUX_REG;
    BUTTON_MUX_REG |= (1 << 8)|(1 << 9);

    while (1){

        if((GPIO.in & (1 << BUTTON_PIN))){
            GPIO.out |= (1 << RGB_RED_PIN)|(1 << RGB_GREEN_PIN)|(1 << RGB_BLUE_PIN);
        }
        else{
            GPIO.out &= ~((1 << RGB_RED_PIN)|(1 << RGB_GREEN_PIN)|(1 << RGB_BLUE_PIN));
        }
    }
}