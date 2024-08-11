#ifndef SerialCom_h
#define SerialCom_h

#include <driver/uart.h>
#include <string.h>

const uart_port_t uart_num = UART_NUM_2;

class SerialCom
{
  public:
    SerialCom();
    void init();
    void sendString(char* string);
    void changeSettings(uart_config_t new_uart_config);
  private:
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_CTS_RTS,
        .rx_flow_ctrl_thresh = 122,
    };
};
#endif