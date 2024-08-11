#include "exampleFunctionsGPIO.hpp"



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