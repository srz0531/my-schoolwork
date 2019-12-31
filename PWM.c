/*

�ó���Ϊ�������ͼ��ʹ�õ�89C52��������
��ʵ��Ӧ��ϵͳ�е�Ƭ��ͨ��L298����������У���P1.0��P1.1�����˿���������ź�
��P0.0-P0.2�˿�ͨ��74LS138��-������������һ��LED��ָʾ�������״̬��
��ʼʱͣתΪ��ɫ����ת��ת���ٶ���������Ϊ��ɫ����ɫ����ɫ��״ָ̬ʾ�Ӻ���3��2��1���ε�ǰ��1��2��3
����ͼ����������ť�����Ϊ���٣�����İ�ťΪ����

*/

#include <reg52.h>
#include <intrins.h>

sbit out1=P1^0;							 //������Ϊ��������ź�����˿�
sbit out2=P1^1;							 //

										 //3-8����������˿�
sbit w2=P0^2;
sbit w1=P0^1;
sbit w0=P0^0;																   


unsigned char PWM = 0;					  //PWM����
unsigned int key_num=3;					  //��ʱ����������
unsigned char flag=0;

unsigned int num=0;						  //�������״̬����


sbit up=P2^0;							   //���ٰ�ť
sbit down=P2^1;							   //���ٰ�ť

void delayMS(unsigned int x)																							 
{																														  
	unsigned int y;
	while(x)
	{
		for(y=0;y<=200;y++)
		{

		}
		x--;
	}
}

void key_scan(void)							 //����ɨ��
{
	if(up==0)
	{
		delayMS(2);								   //��ʱ����              
		if(up==0)
		{
			while(up==0)
			{
			}
			if(PWM<90 && key_num<6 && key_num>=3)	   //��תʱ�����ٰ�ť����ٶ�����
			{
				key_num=key_num+1;
				PWM=PWM+30;
			}
			if(key_num>=0 && key_num<3 && PWM<=90)	   //��תʱ�����ٰ�ť���ת�ټ�С
			{
				key_num=key_num+1;
				PWM=PWM-30;
			}
		}
	}

	if(down==0)
	{
		delayMS(2);							 //��ʱ����
		if(down==0)
		{
			while(down==0)
			{
			}
			if(PWM<90 && key_num>0 && key_num<=3)		 //��תʱ�����ٰ�ť���ת������
			{
				key_num=key_num-1;
				PWM=PWM+30;
			}
			if(PWM<=90 && key_num<=6 && key_num>3)		   //��תʱ�����ٰ�ť���ת�ټ�С
			{
				key_num=key_num-1;
				PWM=PWM-30;
			}
		}
	}
} 

void poin(unsigned int x)					  //�˺������ڿ���3-8���������
{
	switch(x)
	{
		case 6 : w2=1; w1=1; w0=0; break;	   
		case 5 : w2=1; w1=0; w0=1; break;  
		case 4 : w2=1; w1=0; w0=0; break;   
		case 3 : w2=0; w1=1; w0=1; break;	
		case 2 : w2=0; w1=1; w0=0; break;	 
		case 1 : w2=0; w1=0; w0=1; break;	  
		case 0 : w2=0; w1=0; w0=0; break;  
	}
}

void timer1_ini(void)
{
	TMOD=0x10;
	TH1=(65536-20000)/256;
	TL1=(65536-20000)%256;

	EA=1;
	ET1=1;
	TR1=1;
}

void main()
{
	timer1_ini();
	flag=1;
	out1=0;
	out2=0;
	P0=0x00;

	while(1)
	{
		key_scan();
		poin(key_num);
	}
}

void t1_int() interrupt 3
{
	TH1=0xfc;							  //ÿһ����������Ϊ100����
	TL1=0x18;
	num++;
	
	if(key_num>3)						   //�����ת���
	{
		out2=0;
		if(num<=PWM)
		{
			out1=1;
		}

		if((num>PWM) && (num<=100))
		{
			out1=0;
		}

		if(num>100)
		{
			out1=1;
			num=0;
		}
	}
	else									//�����ת���
	{
		out1=0;
		if(num<=PWM)
		{
			out2=1;
		}

		if((num>PWM) && (num<=100))
		{
			out2=0;
		}

		if(num>100)
		{
			out2=1;
			num=0;
		}
	}


}