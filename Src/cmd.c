/*******************************************************************************
 * Copyright:		BUPT
 * File Name:		cmd.c
 * Author:			ZeroVoid
 * Description:		None
 * Bug:				None
 * Version:			0.1
 * Data:			2019/09/19 Thu 19:50
 * Todo:			None
 *******************************************************************************/

#include "cmd.h"
#include "communication.h"
#include "hash.h"

#ifdef CMD
#include <string.h>

/* 变量定义 -----------------------------------------------------*/
/*
static cmd_struct cmd_tbl[] = {
    /*
     * 存放命令的结构体
     * 最后一条CMD_ADD不需要,
     */
    /*
    CMD_ADD("help", "", cmd_help_func),
    CMD_ADD("hello", "", cmd_hello_func)
}; */
static const char *delim = ", \0";

HashTable cmd_table;
/*
char cmd_line[MAX_CMD_LINE_LENGTH + 1];
char *cmd_argv[MAX_ARGC]; 
*/

/* private function -----------------------------------------------------*/
static int str_cmp(const void *a, const void *b) {
    return strcmp((char*)a, (char*)b) != 0;
}
static void _cmd_help(const void *key, void **value, void *c1);

/* cmd code -----------------------------------------------------*/
void cmd_init(void)
{
    cmd_table = HashTable_create(str_cmp, hashStr, NULL);
}


void _cmd_register(struct cmd_val * val, char *cmd_name, char *cmd_usage, void (*cmd_func)(int argc, char *argv[])) {
    val->cmd_usage = cmd_usage;
    val->cmd_func = cmd_func;
    HashTable_insert(cmd_table, cmd_name, val);
}

int cmd_parse(char *cmd_line,int *argc,char *argv[]){
    char *token = strtok(cmd_line, delim);
    int arg_index = 0;

    while(token && arg_index <= MAX_ARGC) {
        argv[arg_index++] = token;
        token = strtok(NULL, delim);
    }
    *argc = arg_index;
    return 0;
}

int cmd_exec(int argc,char *argv[]){
    /*
    int cmd_index = 0;
    uint32_t cmd_num;
 
    cmd_num = sizeof(cmd_tbl)/sizeof(cmd_tbl[0]);

    if(argc == 0){  //��������ǿյģ��򷵻�
        return -1;
    }
    for(cmd_index = 0;cmd_index < cmd_num;cmd_index++){   //��������
        if(strcmp((char *)(cmd_tbl[cmd_index].cmd_name),(char *)argv[0]) == 0){  //����ҵ��������ִ���������Ӧ�ĺ���
            cmd_tbl[cmd_index].cmd_func(argc,argv);
            //memset(USART_RX_BUF,0,MAX_CMD_LINE_LENGTH + 1);
            return 0;
        }
    }
    return -2;
    */
    struct cmd_val *val = HashTable_get(cmd_table, argv[0]);
    if (val != NULL) {
        val->cmd_func(argc, argv);
        return 0;
    }
    return 1;
}

void cmd_help_func(int argc,char *argv[]){
    /*
    int i;
    uint32_t cmd_num;
    cmd_num = sizeof(cmd_tbl)/sizeof(cmd_tbl[0]);
    uprintf("help:\n");
    if(argc > 1){
        //uprintf(CMD_USART,"msg:\n help\n\n");      
        return;         
    }
    for(i = 0;i < cmd_num;i++){
        uprintf("cmd:%s\nusage:%s\n\n",cmd_tbl[i].cmd_name,cmd_tbl[i].cmd_usage);
    }*/
    uprintf("help:\r\n");
    HashTable_map(cmd_table, _cmd_help, NULL);
}
static void _cmd_help(const void *key, void **value, void *c1) {
    UNUSED(c1);
    uprintf("%s: %s\r\n", key, ((struct cmd_val*)(*value))->cmd_usage);
}
#endif