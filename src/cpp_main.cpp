#include "cpp_main.hpp"
#include "exampleFunctionsGPIO.hpp"
#include <soc/gpio_struct.h>
#include <soc/io_mux_reg.h>

#define RGB_RED_PIN 25
#define RGB_GREEN_PIN 26
#define RGB_BLUE_PIN 27

#define REG(x) (*(volatile uint32_t *)(x))
#define DIODE_UNDER_TEST 18
#define BUTTON_PIN 19

#define BUTTON_MUX_REG REG(IO_MUX_GPIO19_REG)
void example00BlinkingRGBDiode();

void cpp_main(){
    // set input pullup for button pin
    initRGB(RGB_RED_PIN, RGB_GREEN_PIN, RGB_BLUE_PIN);
    GPIO.enable &= (1 << BUTTON_PIN);
    BUTTON_MUX_REG |= (1 << 8)|(1 << 9);

    while (1){

        if((GPIO.in & (1 << BUTTON_PIN))){
            GPIO.out |= (1 << RGB_RED_PIN);
        }
        else{
            GPIO.out &= ~(1 << RGB_RED_PIN);
        }
        blinkDiode(RGB_GREEN_PIN);
    }
}



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