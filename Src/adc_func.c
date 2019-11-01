#include "adc_func.h"
#include "nrf24l01.h"
#include "string.h"
uint32_t ADC_Value[150];
int adc_flag = 0;
float adc_num = 0;
float adc_power = 0;
int adc_power_off_flag = 0;
struct adc_rocker adc_rocker_value;

Handle chassis_handle = {0,0,0,0};
int16_t handle_rocker[4];

int k = 0;
int16_t sum[4] = {0};
#define N 10;

void adc_exe()
{
    if(adc_flag == 0) return;
    //uint32_t ad[5] = {0};
    /*
    for(int i = 0; i < 150;)
            {//yzx
            ad[0] += ADC_Value[i++];
            ad[1] += ADC_Value[i++];
            ad[2] += ADC_Value[i++];
            ad[3] += ADC_Value[i++];
            ad[4] += ADC_Value[i++];
            }
    adc_power = ad[0]/30/2.98-2205/2.98;//2503  2205
    if(adc_power<=0)
    {
        adc_power = 0;
        //adc_power_off_flag = 1;
    }
    Lcd_Show_Int(215,0,12,0,(int)adc_power);
    */
        //data��0��5�ֱ���ad1��λ��λ��ad2��λ��λ��ad3��λ��λ
        uint16_t adc_data[4];
        uint8_t temp[10] = {0};
        for(int i = 0; i < 4; i++)
        {
            /*
            ad[i+1] /= 30;
           // uprintf("ad %d = %d\r\n",i,ad[i]);
            ad[i+1] /= 16;
            if(ad[i+1] > 255) ad[i+1] = 255;
            adc_data[i] = (uint8_t)ad[i+1];
            */
           adc_data[i] = (*((uint16_t *)&adc_rocker_value+1+i)-2048)*256/4096;
           //adc_data[i] = (uint16_t)(((*(ADC_Value+1+i))-2048)*256/4096);
        }
        //can_send_msg(324,adc_data,8);//ҡ��id324
        memcpy(temp,(uint16_t *)&adc_data,8);
       /* memcpy(handle_rocker,(uint16_t *)&adc_data,8);
        
        
        //常数修改零偏
        chassis_handle.ry = handle_rocker[0] - 14;
        chassis_handle.rx = -(handle_rocker[1] - 4);
        chassis_handle.ly = handle_rocker[2] - 4;
        chassis_handle.lx = -(handle_rocker[3] - 5);
        
        if(k == 0)
        {
          sum[0] = sum[0] + handle_rocker[0] - 16;
          sum[1] = sum[1] + (-(handle_rocker[1] - 4));
          sum[2] = sum[2] + handle_rocker[2] - 1;
          sum[3] = sum[3] + (-(handle_rocker[3] - 5));
          
          sum[0] = sum[0] / N;
          sum[1] = sum[1] / N;
          sum[2] = sum[2] / N;
          sum[3] = sum[3] / N;
           
          memcpy(temp,(uint16_t *)&sum,8);
          nrf_send_data(temp, 10);
          
          sum[0] = 0;
          sum[1] = 0;
          sum[2] = 0;
          sum[3] = 0;
          
          k = (k + 1) % N;
        }
        else
        {
          sum[0] = sum[0] + handle_rocker[0] - 16;
          sum[1] = sum[1] + (-(handle_rocker[1] - 4));
          sum[2] = sum[2] + handle_rocker[2] - 1;
          sum[3] = sum[3] + (-(handle_rocker[3] - 5));
          
          k = (k + 1) % N;
        }*/
        
        //uprintf("%d,%d,%d,%d",chassis_handle.ly ,chassis_handle.lx,chassis_handle.ry,chassis_handle.rx);
        nrf_send_data(temp, 10);
        
        //NRF_Install_TX_Data(temp, 10);
        //nrf_send(adc_data,7);//nrf��һλ��R
    adc_flag = 0;
}