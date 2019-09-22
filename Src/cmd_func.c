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
#include "communication.h"


void cmd_hello_func(int argc,char *argv[])
{
  uprintf("hello world");
  //ChassisSignal.m_CtrlFlag._handle_flag = 0;
  //modify_x = ORIGIN_X - (chassis.pos_x - modify_x);//修改全场定位初始值
  //modify_y = ORIGIN_Y - (chassis.pos_y - modify_y);
  //chassis.g_fturn = 0;//防止方向环突变 
  //chassis_update();
  //chassis_modify_pos(chassis_xpos,chassis_ypos,ORIGIN_X,ORIGIN_Y);
  //chassis_poscnt = 0;
  //Chassis_State = atoi(argv[1]);
}