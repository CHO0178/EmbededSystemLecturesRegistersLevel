#include "SerialCom.h"
#include <driver/uart.h>

void SerialCom::init()
{
    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));
    ESP_ERROR_CHECK(uart_set_pin(UART_NUM_2, 4, 5, 18, 19));
    const int uart_buffer_size = (1024 * 2);

}

void SerialCom::sendString(char *string)
{
    uart_write_bytes(uart_num, string, strlen(string));
}

void SerialCom::changeSettings(uart_config_t new_uart_config)
{
    uart_config = new_uart_config;
}
