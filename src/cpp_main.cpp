#include "cpp_main.hpp"
#include "exampleFunctionsGPIO.hpp"
#include <soc/gpio_struct.h>
#include <soc/io_mux_reg.h>
#include "littleHelper.h"
#include <driver/uart.h>
#include <string.h>

#define RGB_RED_PIN 25
#define RGB_GREEN_PIN 26
#define RGB_BLUE_PIN 27

#define DIODE_UNDER_TEST 18
#define BUTTON_PIN 19

const uart_port_t uart_num = UART_NUM_2;

// přerušení strana 35 
// bit přerušení z GPIO
#define INTERRUPT_GPIO_SOURCE 22
// registr s flagy přerušení
#define DPORT_PRO_INTR_STATUS_REG_0_REG REG(0x3FF000EC)
// registr s nastavením úrovně přerušení
#define DPORT_PRO_GPIO_INTERRUPT_MAP_REG REG(0x3FF0015C)
// registr s adresou obsluhy přerušení
#define PIDCTRL_INTERRUPT_ADDR_3_REG REG(0x3FF1F00C)
// povolení generování přerušení pro úroveň
#define PIDCTRL_INTERRUPT_ENABLE_REG REG(0x3FF1F000)

#define GPIO_INTERRUPT_PRO 
#define BUTTON_MUX_REG REG(IO_MUX_GPIO19_REG)


void example00BlinkingRGBDiode();
void example00DiodeWithButton();
void example01DiodeWithButton();
void interruptHandler();
void initSerialCom();

void cpp_main(){
    initSerialCom();
    /*
    // CZ: vyberte typ přerušení a povolte jeho generování
    // EN: select the type of interrupt and enable its generation
    GPIO.pin[BUTTON_PIN].int_type = 1<<2; // falling edge trigger
    GPIO.pin[BUTTON_PIN].int_ena = 1<<2; // enable interrupt for PRO CPU
    
    // CZ: nastavte prioritu přerušení a její vektor (str. 623)
    // EN: set the interrupt priority and its vector (page 623)
    PIDCTRL_INTERRUPT_ADDR_3_REG = (uint32_t)interruptHandler;
    


    PIDCTRL_INTERRUPT_ENABLE_REG = ~0; // enable all interrupts
    // CZ: povolte vstup singálu na pin
    // EN: enable signal input on pin
    BUTTON_MUX_REG |= (1 << 8)|(1 << 9);   // input nad pullup resistor
    */
}

void interruptHandler(){
    // CZ: vymazání příznaku přerušení
    // EN: clear the interrupt flag    
    
    // CZ: zde můžete zpracovat přerušení
    // EN: you can process the interrupt here



    //PIDCTRL_INTERRUPT_ADDR_1_REG = 1;
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

void initSerialCom()
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
        .rx_flow_ctrl_thresh = 122,
    };
    // Configure UART parameters
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    // Set UART pins(TX: IO4, RX: IO5, RTS: IO18, CTS: IO19)
    
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, 4, 5, 18, 19));

    // Setup UART buffered IO with event queue
    const int uart_buffer_size = (1024 * 2);
    QueueHandle_t uart_queue;
    // Install UART driver using an event queue here
    ESP_ERROR_CHECK(uart_driver_install(UART_NUM_2, uart_buffer_size, \
                                            uart_buffer_size, 10, &uart_queue, 0));
}

void sendDataToSerialPort(const char * data){
    uart_write_bytes(UART_NUM_2, data, strlen(data));
}











