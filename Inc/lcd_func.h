#ifndef __lcd_func_H
#define __lcd_func_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"
#include "main.h"

#include "ILI93xx.h"
     
void lcd_show_exc_func();
void lcd_robot_init_func();

extern int mode;

#ifdef __cplusplus
}
#endif
#endif /*__lcd_func_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/