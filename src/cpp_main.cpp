#include "cpp_main.hpp"
#include "exampleFunctionsGPIO.hpp"
#include <soc/gpio_struct.h>
#include <soc/io_mux_reg.h>
#include "littleHelper.h"
#include <driver/uart.h>
#include <string.h>

#include "edubox_01.hpp"


void cpp_main(){
    example00BlinkingRGBDiode();
}
