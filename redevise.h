#ifndef __REDEVISE_H_
#define __REDEVISE_H_
#include <stdio.h>
#include "redevise.h"
#include <stdlib.h>

void delay_MS(unsigned int x);                                         //延时子程序
unsigned int button_com(int x);                                        //通用按钮程序
unsigned char SEG_codeCC(unsigned int x);                              //七段数码管段码表  
void tdd(unsigned char dat);                                           //串口发送子程序
unsigned char rdd(void);                                               //串口接收子程序         

void delay_MS(unsigned int x)
  {
    unsigned int i;
    while(x)
    {
      for(i=0;i<=100;i++)
      {
    
      }
	  x--;
    }
  }

  unsigned int button_com(int x)
  {
	unsigned int i=0;
	if(x==0)
	{
		delay_MS(20);
		if(x==0)
		{
			while(x==0)
			{
				
			}
			i=1;
		}
	}
	return i;
  }
  
  unsigned char SEG_codeCC(unsigned int x)
  {
	  unsigned char segment_code[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x39,0x5e,0x79,0x71};
	  return segment_code[x];
  }
  
  void tdd(unsigned char dat)
  {
	  TI=0;
	  SBUF=dat;
	  while(!TI)
	  {
		  
	  }
	  TI=0;
  }
  
  unsigned char rdd(void)
  {
	  RI=0;
	  while(!RI)
	  {
		  
	  }
	  RI=0;
	  return SBUF;
  }
  
 #endif