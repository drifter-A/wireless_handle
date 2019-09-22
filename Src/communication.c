/*******************************************************************************
 * Copyright:		BUPT
 * File Name:		communication.c
 * Author:			ZeroVoid
 * Description:		None
 * Bug:				None
 * Version:			0.1
 * Data:			2019/09/19 Thu 19:35
 * Todo:			None
 *******************************************************************************/

#include "communication.h"

#ifdef CMD
#include "cmd.h"
#endif  //CMD

#if defined(CMD) || defined(USART_OUTPUT)
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#endif  //CMD || USART_OUTPUT

uint8_t DMAaRxBuffer[DMA_BUFFER_SIZE];
char DMAUSART_RX_BUF[DMA_BUFFER_SIZE];

CAN_HandleTypeDef HCAN;
UART_HandleTypeDef CMD_USART;

#ifdef CMD
int DMA_RxOK_Flag = 0;
#endif  //CMD

uint8_t TxData[8];
uint8_t RxData[8];
CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;
uint32_t TxMailbox;
can_msg can_rx_data;
can_msg can_tx_data;

static void CAN_config(CAN_HandleTypeDef *hcan);

void usart_DMA_init(UART_HandleTypeDef *cmd_usart) {
    #ifdef CMD
    CMD_USART = *cmd_usart;
    HAL_UART_Receive_DMA(&CMD_USART, (uint8_t *)&DMAaRxBuffer, DMA_BUFFER_SIZE);
    #endif  //CMD
}

void can_init(CAN_HandleTypeDef *hcan) {
    HCAN = *hcan;
    CAN_config(&HCAN);
}

void communication_init(UART_HandleTypeDef *cmd_usart, CAN_HandleTypeDef *hcan) {
#ifdef CMD
    usart_DMA_init(cmd_usart);
#endif  //CMD
    can_init(hcan);
}

// can
void CAN_config(CAN_HandleTypeDef *hcan) {
    CAN_FilterTypeDef sFilterConfig;

    /* Configure the CAN Filter 
     bxCAN提供28个位宽可变/可配置的标识符过滤器组
     通过设置CAN_FMR的FBMx位 设置过滤器类型 0: mask mode; 1: list mode
  */
    sFilterConfig.FilterBank = 0;
    sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;
    sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;
    /* CAN_FILTERSCALE_32BIT
     FilterIdHight = StdId << 5 
     FilterIdHight = (ExtId << 3)>>16 & 0xFFFF
     FIlterIdLow   = ((uint16_t)(ExtId <<3)) | CAN_ID_EXT;*/
    sFilterConfig.FilterIdHigh = 0x0000;
    sFilterConfig.FilterIdLow = 0x0000;
    sFilterConfig.FilterMaskIdHigh = 0x0000;
    sFilterConfig.FilterMaskIdLow = 0x0000;
    sFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;
    sFilterConfig.FilterActivation = ENABLE;
    sFilterConfig.SlaveStartFilterBank = 14;

    if (HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK) {
        /* Filter configuration Error */
        Error_Handler();
    }

    /* Start the CAN peripheral */
    if (HAL_CAN_Start(hcan) != HAL_OK) {
        /* Start Error */
        Error_Handler();
    }

    /* Activate CAN RX notification */
    if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_MSG_PENDING) != HAL_OK) {
        /* Notification Error */
        Error_Handler();
    }

    if (HAL_CAN_ActivateNotification(hcan, CAN_IT_RX_FIFO0_FULL) != HAL_OK) {
        /* Notification Error */
        Error_Handler();
    }

    /* Configure Transmission provess */
    TxHeader.RTR = CAN_RTR_DATA;
    TxHeader.IDE = CAN_ID_STD;
    TxHeader.DLC = 8;
    TxHeader.TransmitGlobalTime = DISABLE;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    //can_callback();
    //if (HAL_CAN_GetRxMessage(&hcan, CAN_RX_FIFO0, &RxHeader, can_msg.ui8) != HAL_OK) {
    //  Error_Handler();
    //}
    //uprintf("in can msg call back\r\n");
    //if ((RxHeader.StdId == 0x321) && (RxHeader.IDE == CAN_ID_STD) && (RxHeader.DLC == 2)) {
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, can_rx_data.ui8);
    uprintf("can rx data %d %d\r\n", can_rx_data.in[0], can_rx_data.in[1]);
    //}
}

void HAL_CAN_RxFifo0FullCallback(CAN_HandleTypeDef *hcan) {
    return ;
}

void can_send_test(void) {
    TxData[0] = 0x1;
    TxData[1] = 0xAD;
    uprintf("send data\r\n");
    HAL_CAN_AddTxMessage(&HCAN, &TxHeader, TxData, &TxMailbox);
}

/* @Brief can 发送数据
 * @Description 发现F1与F4 HAL库封装的发送函数名称以及调用方式不同。
 * @param	id: 发送数据id
 *          msg: can数据封装结构体
 *          len: 数据长度
 * @return	0: 正常发送
 *          1: 发送失败
 */
int can_send_msg(uint16_t std_id, can_msg *msg) {
  TxHeader.StdId = std_id;
  //uprintf("%d %d %d\r\n", std_id, msg->in[0], msg->in[1]);
  if (HAL_CAN_AddTxMessage(&HCAN, &TxHeader, msg->ui8, &TxMailbox) != HAL_OK) {
    //uprintf("Error: CAN can't send msg.\r\n");
    return 1;
  }
  return 0;
}

void HAL_UART_IDLECallback(UART_HandleTypeDef *huart) {
#ifdef CMD
    if (huart->Instance == CMD_USART.Instance) {
        uint8_t temp;
        __HAL_UART_CLEAR_IDLEFLAG(huart);  //清除函数空闲标志
        temp = huart->Instance->SR;
        temp = huart->Instance->DR;  //读出串口的数据，防止在关闭DMA期间有数据进来，造成ORE错误
        UNUSED(temp);
        // temp = hdma_usart3_rx.Instance->CNDTR;
        // huart->hdmarx->XferCpltCallback(huart->hdmarx);
        // //调用DMA接受完毕后的回调函数，最主要的目的是要将串口的状态设置为Ready，否则无法开启下一次DMA
        HAL_UART_DMAStop(&huart3);  //停止本次DMA

        strcpy((char *)DMAUSART_RX_BUF, (char *)DMAaRxBuffer);
        if (DMAUSART_RX_BUF[0] != '\0') DMA_RxOK_Flag = 1;

        memset(DMAaRxBuffer, 0, 98);
        HAL_UART_Receive_DMA(&CMD_USART, (uint8_t *)&DMAaRxBuffer, DMA_BUFFER_SIZE);
    }
#endif  //CMD
}

#ifdef CMD
void usart_exc_DMA() {
    int cmd_argc;
    int erro_n;
    if (DMA_RxOK_Flag) {
        erro_n = cmd_parse((char *)DMAUSART_RX_BUF, &cmd_argc, cmd_argv);  //解析命令
        erro_n = cmd_exec(cmd_argc, cmd_argv);                             //执行命令
        UNUSED(erro_n);
        memset(DMAUSART_RX_BUF, 0, 98);
        DMA_RxOK_Flag = 0;
    }
}
#endif

#if defined(SHOW) || defined(CMD)
char print_buffer[PRINT_BUFFER_SIZE];
void uprintf(char *fmt, ...) {
    int size;
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    size = vsnprintf(print_buffer, PRINT_BUFFER_SIZE, fmt, arg_ptr);
    va_end(arg_ptr);

    HAL_UART_Transmit_DMA(&CMD_USART, (uint8_t *)print_buffer, size);
}

void uprintf_to(UART_HandleTypeDef *huart, char *fmt, ...) {
    int size;
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    size = vsnprintf(print_buffer, PRINT_BUFFER_SIZE, fmt, arg_ptr);
    va_end(arg_ptr);

    HAL_UART_Transmit_DMA(huart, (uint8_t *)print_buffer, size);
    // HAL_UART_Transmit(huart,(uint8_t *)uart_buffer,size,1000);
}

char s[22] = {'b', 'y', 16, 6};
void send_wave(float arg1, float arg2, float arg3, float arg4) {
    //s[2] = 16;  // length
    //s[3] = 6;   // type
    s[20] = '\r';
    s[21] = '\n';
    memcpy(s + 4, &arg1, sizeof(arg1));
    memcpy(s + 8, &arg2, sizeof(arg1));
    memcpy(s + 12, &arg3, sizeof(arg1));
    memcpy(s + 16, &arg4, sizeof(arg1));
    HAL_UART_Transmit_DMA(&CMD_USART, (uint8_t *)s, 22);
}
#endif