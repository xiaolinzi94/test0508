#include<reg52.h>			  //包含特殊功能寄存器定义的头文件
sbit LED0=P2^0;				 //位地址声明
sbit LED1=P2^1;
sbit LED2=P2^2;
sbit LED3=P2^3;
sbit LED4=P2^4;
sbit LED5=P2^5;
sbit LED6=P2^6;
sbit LED7=P2^7;
#define NIXIE_PORT P0
#define LED_PORT P2

void LampFalshing(void);
void GroupLampFalshing(void);
void FlowingWaterLamp(void);
void delay(int temptime);
void NixieLight(void);

void main(void)
{
//以下3个功能函数均是LED亮灭 的功能，不可同时使用	
//	LampFalshing();			//第一个LED小灯闪烁功能
//	GroupLampFalshing();	//整组LED小灯闪烁功能
//	FlowingWaterLamp();	    //流水灯功能
	NixieLight();	   //数码管循环显示数字1~8功能
}	

//第一个LED小灯闪烁功能
void LampFalshing(void)
{
	while(1)
	{  
		LED0^=1;
   		delay(50000);
	}
}

//整组LED小灯闪烁功能
void GroupLampFalshing(void)
{
	LED_PORT =0x0;
	while(1)
	{  
		LED_PORT=~LED_PORT;
   		delay(50000);
	}
}

//流水灯功能
void FlowingWaterLamp(void)
{
 	int i=0;
	LED_PORT =~0x01;
	while(1)
	{  //使用位移+循环实现流水灯
		for(i=0;i<8;i++)
		{
			LED_PORT =~(0x01<<i);
   			delay(50000);
		}
	}
}


//数码管循环显示数字1~8功能
void NixieLight(void)
{	
	int arrNixie[10]={0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x7,0x7F,0x80};	 //显示数字0~8，点·
 	int i,j=0;
#if 0
//方法一，不足点：只需控制P2^2,P2^3,P2^4 3个引脚即可，实际控制了P2整组8个引脚才实现效果
	while(1)
	{  
		LED_PORT =0x20;		//38译码器3个输入引脚 CBA为111时，输出引脚Y7=0，即LED_PORT最大为0x1C,初始值设为0x1C+4;  CBA为110时，输出引脚Y6=0，即LED_PORT为0x1C-4;
		for (j=0;j<8;j++)
		{
			LED_PORT =LED_PORT-0x4;
   			delay(50000);

			for (i=0;i<10;i++)
			{
	
				NIXIE_PORT =arrNixie[i];
	   			delay(50000);
			}
			NIXIE_PORT =0x0;   //清除上次for循环的数组最后一位值 数码管db位
		}	
	}
#endif
//方法二 控制P2^2,P2^3,P2^4 3个引脚即可实现效果
	while(1)
	{  
		for (j=0;j<8;j++)
		{
			switch(j)
			{
			 case 0:LED4=1;LED3=1;LED2=1;break;		 //Y7亮
			 case 1:LED4=1;LED3=1;LED2=0;break;		 //Y6亮
			 case 2:LED4=1;LED3=0;LED2=1;break;		 //Y5亮
			 case 3:LED4=1;LED3=0;LED2=0;break;		 //Y4亮
			 case 4:LED4=0;LED3=1;LED2=1;break;		 //Y3亮
			 case 5:LED4=0;LED3=1;LED2=0;break;		 //Y2亮
			 case 6:LED4=0;LED3=0;LED2=1;break;		 //Y1亮
			 case 7:LED4=0;LED3=0;LED2=0;break;		 //Y0亮
			}
			for (i=0;i<10;i++)
			{
	
				NIXIE_PORT =arrNixie[i];
	   			delay(50000);
			}
			NIXIE_PORT =0x0;   //清除上次for循环的数组最后一位值 数码管db位
		}	
	}
}

	 
//延时函数
void delay(int temptime)
{
	while(temptime--);
}
						