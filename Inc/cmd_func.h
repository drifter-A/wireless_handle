#ifndef __cmd_func_H
#define __cmd_func_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "cmd.h"
   
void cmd_func_init(void);
void cmd_hello_func(int argc,char *argv[]);  
void cmd_can_test(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif
#endif /*__ cmd_func_H */