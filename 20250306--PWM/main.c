#include "stc15f2k60s2.h"
#include <intrins.h>

#define LED(X) {P0=X;P2 = (P2&0x1F | 0x80);P2 &=0x1F;}	//LED�豸ѡ��
#define SEG(X) {P0=X;P2 = (P2&0x1F | 0xE0);P2 &=0x1F;}	//����ܶ�ѡ
#define COM(X) {P0=X;P2 = (P2&0x1F | 0xC0);P2 &=0x1F;}	//�����λѡ
#define BUZ(X) {P0=X;P2 = (P2&0x1F | 0xA0);P2 &=0x1F;}	//������/�̵������豸ѡ��

bit dire = 1;

void INT0_init(void)
{
	IT0 = 1;
	EX0 = 1;
	EA  = 1;
}
void isr_Int0(void) interrupt 0
{
	dire = ~dire;
}	


void Delay100us()		//@12.000MHz
{
	unsigned char i, j;

	i = 2;
	j = 39;
	do
	{
		while (--j);
	} while (--i);
}


void taskPWM(unsigned char pwm)
{
	static unsigned char buz = 0x00;
	static unsigned char index = 0;
	
	if(pwm)
	{
		if(++index < pwm)
		{
			buz |= (1<<5);
			Delay100us();
		}else{
			buz &= ~(1<<5);
			Delay100us();
		}
		
		
	}
	if(index == 10)
	{
		index = 0;
	}
	BUZ(buz);
}	

void taskLed(void)
{
	if(dire==1)
	{
		taskPWM(9);
	}else{
		taskPWM(2);
	}
	
		
}

void main(void)
{	
	
	BUZ(0X00);//�رշ�����
	COM(0xFF);//�ر�λѡ
	SEG(0xFF);//�رն�ѡ
	LED(0xFF);//�ر�LED
	INT0_init();
	
	while(1)
	{
		taskLed();
	}
}