#include "lcd_func.h"
int mode = 0;
void lcd_robot_init_func()
{
  static int x;
  u8 lcd_id[12];				//存放LCD ID字符串
  POINT_COLOR=RED;     			//画笔颜色：红色
	sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。
	while(x<=12)
	{
		switch(x)
		{
			case 0:LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break; 
			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		POINT_COLOR=RED;
                LCD_ShowString_New(12,0,24,0,(uint8_t *)"BELIEVE");
                LCD_ShowString_New(12,24,24,0,(uint8_t *)"UNIQUE");
                LCD_ShowString_New(12,48,24,0,(uint8_t *)"PASSION");
                LCD_ShowString_New(12,72,24,0,(uint8_t *)"TEAM");	
                LCD_ShowString_New(12,96,24,0,(uint8_t *)"2018/12/03");	
		if(x==12)
		{	
			  LCD_Clear(WHITE);
                          LCD_ShowString(12,100,200,12,24,(uint8_t *)"system ok!!!");
                          LCD_Clear(WHITE);			  
		}
		x++; 
		//HAL_Delay(1000);
	}
}

void lcd_show_exc_func()
{
    LCD_ShowString_New(12,0,24,0,  (uint8_t *)"POINTX :");
    LCD_ShowString_New(234,0,12,0, (uint8_t *)"%");
    LCD_ShowString_New(12,24,24,0, (uint8_t *)"POINTY :"); 
    LCD_ShowString_New(12,48,24,0, (uint8_t *)"ANGLE  :");
    LCD_ShowString_New(12,72,24,0, (uint8_t *)"CCD    :"); 
    POINT_COLOR=BLUE;
    LCD_Draw_Circle(20,90,30);
    LCD_Draw_Circle(80,90,30);
    LCD_Draw_Circle(50,40,30);
    LCD_Draw_Circle(50,140,30);
    
    LCD_Draw_Circle(150,90,30);
    LCD_Draw_Circle(210,90,30);
    LCD_Draw_Circle(180,40,30);
    LCD_Draw_Circle(180,140,30);
    
    POINT_COLOR=RED;
    if(mode == 0)
    {
        int error = 130;
        LCD_ShowString_New(42,175,12,0, (uint8_t *)"Start1"); 
        LCD_ShowString_New(42,275,12,0, (uint8_t *)"Throw/Y"); 
        LCD_ShowString_New(12,225,12,0, (uint8_t *)"Start2"); 
        LCD_ShowString_New(75,225,12,0, (uint8_t *)"Start3"); 
        LCD_ShowString_New(42 + error,175,12,0, (uint8_t *)"Manual"); 
        LCD_ShowString_New(42 + error,275,12,0, (uint8_t *)"None"); 
        LCD_ShowString_New(12 + error,225,12,0, (uint8_t *)"Catch"); 
        LCD_ShowString_New(75 + error,225,12,0, (uint8_t *)"Loosen"); 
    }else if(mode == 1)
    {
        int error = 130;
        LCD_ShowString_New(42,175,12,0, (uint8_t *)"Change1"); 
        LCD_ShowString_New(42,275,12,0, (uint8_t *)"Throw/Y"); 
        LCD_ShowString_New(12,225,12,0, (uint8_t *)"Connect"); 
        LCD_ShowString_New(75,225,12,0, (uint8_t *)"Change2"); 
        LCD_ShowString_New(42 + error,175,12,0, (uint8_t *)"Manual"); 
        LCD_ShowString_New(42 + error,275,12,0, (uint8_t *)"Throw/N"); 
        LCD_ShowString_New(12 + error,225,12,0, (uint8_t *)"Catch"); 
        LCD_ShowString_New(75 + error,225,12,0, (uint8_t *)"Loosen"); 
    }
}