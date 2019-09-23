/*******************************************************************************
 * Copyright:		BUPT
 * File Name:		simplelib.c
 * Author:			ZeroVoid
 * Description:		None
 * Bug:				None
 * Version:			0.1
 * Data:			2019/09/19 Thu 19:35
 * Todo:			None
 *******************************************************************************/

#include "simplelib.h"
#include "simplelib_config.h"

/**
 * @brief	初始化配置
 * @param	cmd_usart   指令通信usart句柄
 * @param   hcan        CAN通信句柄
 * @return	None
 */
void simplelib_init(UART_HandleTypeDef *cmd_usart, CAN_HandleTypeDef *hcan) {
    usart_DMA_init(cmd_usart);
    can_init(hcan);
    uprintf("simplelib init done\r\n");
}
