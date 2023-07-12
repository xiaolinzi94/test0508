#include<reg52.h>			  //�������⹦�ܼĴ��������ͷ�ļ�
sbit LED0=P2^0;				 //λ��ַ����
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
//����3�����ܺ�������LED���� �Ĺ��ܣ�����ͬʱʹ��	
//	LampFalshing();			//��һ��LEDС����˸����
//	GroupLampFalshing();	//����LEDС����˸����
//	FlowingWaterLamp();	    //��ˮ�ƹ���
	NixieLight();	   //�����ѭ����ʾ����1~8����
}	

//��һ��LEDС����˸����
void LampFalshing(void)
{
	while(1)
	{  
		LED0^=1;
   		delay(50000);
	}
}

//����LEDС����˸����
void GroupLampFalshing(void)
{
	LED_PORT =0x0;
	while(1)
	{  
		LED_PORT=~LED_PORT;
   		delay(50000);
	}
}

//��ˮ�ƹ���
void FlowingWaterLamp(void)
{
 	int i=0;
	LED_PORT =~0x01;
	while(1)
	{  //ʹ��λ��+ѭ��ʵ����ˮ��
		for(i=0;i<8;i++)
		{
			LED_PORT =~(0x01<<i);
   			delay(50000);
		}
	}
}


//�����ѭ����ʾ����1~8����
void NixieLight(void)
{	
	int arrNixie[10]={0x3F,0x6,0x5B,0x4F,0x66,0x6D,0x7D,0x7,0x7F,0x80};	 //��ʾ����0~8���㡤
 	int i,j=0;
#if 0
//����һ������㣺ֻ�����P2^2,P2^3,P2^4 3�����ż��ɣ�ʵ�ʿ�����P2����8�����Ų�ʵ��Ч��
	while(1)
	{  
		LED_PORT =0x20;		//38������3���������� CBAΪ111ʱ���������Y7=0����LED_PORT���Ϊ0x1C,��ʼֵ��Ϊ0x1C+4;  CBAΪ110ʱ���������Y6=0����LED_PORTΪ0x1C-4;
		for (j=0;j<8;j++)
		{
			LED_PORT =LED_PORT-0x4;
   			delay(50000);

			for (i=0;i<10;i++)
			{
	
				NIXIE_PORT =arrNixie[i];
	   			delay(50000);
			}
			NIXIE_PORT =0x0;   //����ϴ�forѭ�����������һλֵ �����dbλ
		}	
	}
#endif
//������ ����P2^2,P2^3,P2^4 3�����ż���ʵ��Ч��
	while(1)
	{  
		for (j=0;j<8;j++)
		{
			switch(j)
			{
			 case 0:LED4=1;LED3=1;LED2=1;break;		 //Y7��
			 case 1:LED4=1;LED3=1;LED2=0;break;		 //Y6��
			 case 2:LED4=1;LED3=0;LED2=1;break;		 //Y5��
			 case 3:LED4=1;LED3=0;LED2=0;break;		 //Y4��
			 case 4:LED4=0;LED3=1;LED2=1;break;		 //Y3��
			 case 5:LED4=0;LED3=1;LED2=0;break;		 //Y2��
			 case 6:LED4=0;LED3=0;LED2=1;break;		 //Y1��
			 case 7:LED4=0;LED3=0;LED2=0;break;		 //Y0��
			}
			for (i=0;i<10;i++)
			{
	
				NIXIE_PORT =arrNixie[i];
	   			delay(50000);
			}
			NIXIE_PORT =0x0;   //����ϴ�forѭ�����������һλֵ �����dbλ
		}	
	}
}

	 
//��ʱ����
void delay(int temptime)
{
	while(temptime--);
}
						