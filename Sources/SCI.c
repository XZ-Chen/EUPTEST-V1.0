#include "SCI.h"
#include "derivative.h"
#define BUS_CLOCK	  32000000	   //总线频率

#define BAUD 9600
unsigned char putstring[]="#5 P1600 T500";
unsigned char *send=0x00;

/*************************************************************/
/*                        初始化SCI                          */
/*************************************************************/
void INIT_SCI(void) 
{
  //SCI1BD = BUS_CLOCK/20/BAUD;   //设置SCI1波特率为9600
  SCI1BD = BUS_CLOCK/16/BAUD;   //设置SCI1波特率为9600
  SCI1CR1 = 0x00;        //设置SCI1为正常模式，八位数据位，无奇偶校验
  SCI1CR2 = 0x88;        //允许发送数据，允许发送中断功能 
  send = putstring;
}                                                            
/*************************************************************/
/*                       串口发送函数                        */
/*************************************************************/
void SCI_send(unsigned char data) 
{
  while(!SCI1SR1_TDRE);         //等待发送数据寄存器（缓冲器）为空
  SCI1DRL = data;
}
void TERMIO_PutChar(char C)
{ 
   while(!(SCI1SR1&0x80)) ;         //keep waiting when not empty  
   SCI1DRL=C;
}


/*************************************************************/
/*                   串口中断发送字符串函数                  */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt 21 void send_string(void) 
{
  
  if(*send!=0x00)         //判断字符串是否发送完毕
  {
     SCI_send(*send++);     
  }
 else 
  {
     send = putstring;
  }  
}
#pragma CODE_SEG DEFAULT   


