#ifndef __CMD_H
#define __CMD_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f4xx_hal.h"
#include "main.h"
#include "cmd_func.h"
#include "usart.h"
#include "stdlib.h"
#include "team_conf.h"

#ifdef CMD
/*
*定义添加指令的宏函数
*/
#define CMD_ADD(cmd_name,cmd_usage,cmd_func) \
    { \
        cmd_name, \
        cmd_usage, \
        cmd_func \
    } \

#define CMD_REG(cmd_name, cmd_usage, cmd_func) \
    do { \
        static struct cmd_val newcmd = {0}; \
        _cmd_register(&newcmd, cmd_name, cmd_usage, cmd_func); \
    } while(0)
   
#define MAX_CMD_ARG_LENGTH 16
#define MAX_CMD_INFO_LENGTH 64
#define MAX_CMD_LINE_LENGTH 128
#define MAX_ARGC 12   //参数数量

extern char cmd_line[MAX_CMD_LINE_LENGTH + 1];
extern char *cmd_argv[MAX_ARGC];
typedef struct {
    char cmd_name[MAX_CMD_ARG_LENGTH];   //命令的名字
    char cmd_usage[MAX_CMD_INFO_LENGTH];   //命令的信息
    void (*cmd_func)(int acgc,char *argv[]); //命令执行函数
} cmd_struct;

struct cmd_val {
    void (*cmd_func)(int argc, char *argv[]);
    char *cmd_usage;
};
   
void cmd_help_func(int argc,char *argv[]);   
int cmd_parse(char *cmd_line,int *argc,char *argv[]);
int cmd_exec(int argc,char *argv[]);
void cmd_init(void);
void _cmd_register(struct cmd_val *val, char *cmd_name, char *cmd_usage, void (*cmd_func)(int argc, char *argv[]));
#endif
   
#ifdef __cplusplus
}
#endif
#endif /*__CMD_H */