#include "SCI.h"
#include "derivative.h"
#define BUS_CLOCK	  32000000	   //����Ƶ��

#define BAUD 9600
unsigned char putstring[]="#5 P1600 T500";
unsigned char *send=0x00;

/*************************************************************/
/*                        ��ʼ��SCI                          */
/*************************************************************/
void INIT_SCI(void) 
{
  //SCI1BD = BUS_CLOCK/20/BAUD;   //����SCI1������Ϊ9600
  SCI1BD = BUS_CLOCK/16/BAUD;   //����SCI1������Ϊ9600
  SCI1CR1 = 0x00;        //����SCI1Ϊ����ģʽ����λ����λ������żУ��
  SCI1CR2 = 0x88;        //���������ݣ��������жϹ��� 
  send = putstring;
}                                                            
/*************************************************************/
/*                       ���ڷ��ͺ���                        */
/*************************************************************/
void SCI_send(unsigned char data) 
{
  while(!SCI1SR1_TDRE);         //�ȴ��������ݼĴ�������������Ϊ��
  SCI1DRL = data;
}
void TERMIO_PutChar(char C)
{ 
   while(!(SCI1SR1&0x80)) ;         //keep waiting when not empty  
   SCI1DRL=C;
}


/*************************************************************/
/*                   �����жϷ����ַ�������                  */
/*************************************************************/
#pragma CODE_SEG __NEAR_SEG NON_BANKED
interrupt 21 void send_string(void) 
{
  
  if(*send!=0x00)         //�ж��ַ����Ƿ������
  {
     SCI_send(*send++);     
  }
 else 
  {
     send = putstring;
  }  
}
#pragma CODE_SEG DEFAULT   


