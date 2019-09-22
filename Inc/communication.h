#ifndef __COMMUNICATION_H
#define __COMMUNICATION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"
#include "team_conf.h"

#define DMA_BUFFER_SIZE 99

typedef union{
        char ch[8];
        uint8_t ui8[8];
        uint16_t ui16[4];
        int16_t i16[4];
        int in[2];
        float fl[2];
        double df;
} can_msg;

//can
extern uint8_t TxData[8];
extern uint8_t RxData[8];
extern CAN_TxHeaderTypeDef TxHeader;
extern CAN_RxHeaderTypeDef RxHeader;
extern uint32_t TxMailbokx;
extern can_msg can_rx_data;
extern can_msg can_tx_data;

extern CAN_HandleTypeDef HCAN;
extern UART_HandleTypeDef CMD_USART;

void communication_init(UART_HandleTypeDef *cmd_usart, CAN_HandleTypeDef *hcan);

// can
void can_init(CAN_HandleTypeDef *hcan);
void can_configure_filter(void);
int can_send_msg(uint16_t id, can_msg *msg);
void can_send_test(void);
void can_send(uint16_t std_id, can_msg *msg);

#ifdef CMD
void usart_DMA_init();
void usart_exc_DMA();
void HAL_UART_IDLECallback(UART_HandleTypeDef *huart);
#endif //CMD

#if defined(USART_OUTPUT) || defined(CMD)
#define PRINT_BUFFER_SIZE 101
void send_wave(float arg1, float arg2, float arg3, float arg4);
void uprintf(char *fmt, ...);
void uprintf_to(UART_HandleTypeDef *huart, char *fmt, ...);
#endif

#ifdef __cplusplus
}
#endif

#endif /* __COMMUNICATION_H */