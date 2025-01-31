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


/*


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

 */