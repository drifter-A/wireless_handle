#ifndef __can_func_H
#define __can_func_H
#ifdef __cplusplus
extern "C" {
#endif
#include "can_utils.h"
#include "can.h"

extern int can_data_show_flag;
    
void can_func_init();
void can_suc_rx(can_msg *data);
void can_show_button(can_msg *data);
void can_show_rocker(can_msg *data);
    
#ifdef __cplusplus
}
#endif
#endif /*__ can_func_H */