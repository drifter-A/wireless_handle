#ifndef __SIMPLELIB_H
#define __SIMPLELIB_H

#ifdef __cplusplus
extern "C" {
#endif

#include "usart.h"

#include "cmd.h"
#include "can_utils.h"

void simplelib_init(UART_HandleTypeDef *cmd_usart, CAN_HandleTypeDef *hcan);

#ifdef __cplusplus
}
#endif

#endif /* __SIMPLELIB_H */