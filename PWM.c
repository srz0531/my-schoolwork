/*

该程序为适配仿真图所使用的89C52驱动程序
在实际应用系统中单片机通过L298驱动电机运行，在P1.0和P1.1两个端口输出驱动信号
在P0.0-P0.2端口通过74LS138三-八译码器控制一排LED灯指示电机运行状态，
初始时停转为红色，正转或反转随速度增加依次为黄色、绿色、蓝色，状态指示从后退3、2、1依次到前进1、2、3
仿真图中有两个按钮上面的为加速，下面的按钮为减速

*/

#include <reg52.h>
#include <intrins.h>

sbit out1=P1^0;							 //这两个为电机控制信号输出端口
sbit out2=P1^1;							 //

										 //3-8译码器输出端口
sbit w2=P0^2;
sbit w1=P0^1;
sbit w0=P0^0;																   


unsigned char PWM = 0;					  //PWM参数
unsigned int key_num=3;					  //定时器计数变量
unsigned char flag=0;

unsigned int num=0;						  //电机运行状态计数


sbit up=P2^0;							   //加速按钮
sbit down=P2^1;							   //减速按钮

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

void key_scan(void)							 //按键扫描
{
	if(up==0)
	{
		delayMS(2);								   //延时消抖              
		if(up==0)
		{
			while(up==0)
			{
			}
			if(PWM<90 && key_num<6 && key_num>=3)	   //正转时按加速按钮电机速度增加
			{
				key_num=key_num+1;
				PWM=PWM+30;
			}
			if(key_num>=0 && key_num<3 && PWM<=90)	   //反转时按加速按钮电机转速减小
			{
				key_num=key_num+1;
				PWM=PWM-30;
			}
		}
	}

	if(down==0)
	{
		delayMS(2);							 //延时消抖
		if(down==0)
		{
			while(down==0)
			{
			}
			if(PWM<90 && key_num>0 && key_num<=3)		 //反转时按减速按钮电机转速增加
			{
				key_num=key_num-1;
				PWM=PWM+30;
			}
			if(PWM<=90 && key_num<=6 && key_num>3)		   //正转时按减速按钮电机转速减小
			{
				key_num=key_num-1;
				PWM=PWM-30;
			}
		}
	}
} 

void poin(unsigned int x)					  //此函数用于控制3-8译码器输出
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
	TH1=0xfc;							  //每一个脉冲周期为100毫秒
	TL1=0x18;
	num++;
	
	if(key_num>3)						   //电机正转情况
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
	else									//电机反转情况
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