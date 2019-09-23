# STM32 部分工具整理

目前仅整理出了串口、CAN总线中断使用。

两者均采用将中断回调的实际执行函数分别注册在相关hash表中。中断中仅作相关flag转换

TODO: flag管理,i2c以及一些其他通信,内存管理,小型os

## 不同开发平台目录配置

### IAR

- `git clone https://github.com/ZeroVoid10/simplelib`到Src,Inc同级目录下

- 右击项目->选项/options->C/C++ Compiler->Preprocessor 添加新include路径
  - 或copy`Inc`下文件到IAR的'Inc`中
- 添加文件`Src`下所有文件

### cmake

不怎么用cmake可能说明有问题

- 编译时`-I./simpleib/Inc`添加路径

### vscode platformio 环境

- `platformio.ini`中添加`build_flags = -I 路径`
- `.c`文件放到`Src`或`src`路径下

## 使用需添加代码说明

- 串口及CAN配置使用STM32Cube配置
- 使用时在main的Cube相关初始化都结束之后调用初始化函数

``` c
/**
 * @brief	初始化配置
 * @param	cmd_usart   指令通信usart句柄
 * @param   hcan        CAN通信句柄
 * @return	None
 */
void simplelib_init(UART_HandleTypeDef *cmd_usart, CAN_HandleTypeDef *hcan);

// 示例 main.c
/* USER CODE BEGIN 2 */
simplelib_init(&huart3, &hcan1);
/* USER CODE END 2 */

```

- 在`main.c`的`while(1)`中添加代码

``` c
    while (1)
  {
    usart_exc_DMA();
    if (can_exe_callback_flag) {
      can_exe_callback();
    }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
```

- 在`stm32f1xx_it.c`或`stm32f4xx_it.c`配置的中断的USART下加上代码。

``` c
/** 示例 stm32f4xx_it.c
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  // 添加的代码
  if(__HAL_UART_GET_FLAG(&CMD_USART, UART_FLAG_IDLE) != RESET){
    HAL_UART_IDLECallback(&CMD_USART);
    return ;
  }

  /* USER CODE END USART3_IRQn 1 */
}

```

- 建议将cmd相关函数放到`cmd_func.c`中，将can回调函数放到`can_func.c`中