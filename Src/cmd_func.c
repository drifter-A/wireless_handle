/*******************************************************************************
Copyright:      2018/12/18
File name:      cmd_func.c
Description:    存放串口命令函数，用户自己添加，要求设成外部可以调用
Author:         徐铭远
Version：       1.0
Data:           2018/12/18 22:36
History:        无
Bug:            无
*******************************************************************************/
#include "cmd_func.h"
#include "can_utils.h"

void cmd_func_init(void) {
  cmd_add("hello", "just", cmd_hello_func);
  cmd_add("can_test", "test can", cmd_can_test);
}

void cmd_hello_func(int argc,char *argv[]) {
  uprintf("hello world\r\n");
}

void cmd_can_test(int argc, char *argv[]) {
  uprintf("can send test\r\n");
  can_send_test();
}