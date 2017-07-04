//-------------------------------------------------------------------------*
//�ļ���: PWM.c                                                        	   *
//˵  ��: PWM��������ļ�                                         		     *
//��ʼʱ�䣺  2015��12��02��              			                           *
//�޶���¼��  2017��4��10�� �������ö�·���     		              			                                   *
//��ע��      ������MC9S12XET256               			                       *
//-------------------------------------------------------------------------*
#include "PWM.h"

//-------------------------------------------------------------------------* 
//������: PWM_Init                                                         *
//��  ��: PWM��ʼ��                                                        *
//��  ������                                                               * 
//��  ��: ��                                                               * 
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*  
void PWMInit(void){
    //PWM�����Ĵ���
    PWME = 0b00000000;  
    PWMPRCLK = 0b00100010; //����40M ClockA = 10M ClockB = 10MHZ                         
    PWMSCLA = 250;         //ClockSA=ClockA/(2xPWMSCLA)                       
    PWMSCLB = 250;         //ClockSB=ClockB/(2xPWMSCLB)    
    PWMCLK = 0b11111111;                                    
    PWMPOL = 0x00;         
    PWMCAE = 0x00;          
    PWMCTL = 0b00000000;                                      
    PWMPER0  = 250;   //ͨ��0������Ϊ0.04ms*250=10ms 
    PWMPER1  = 250;   //ͨ��1������Ϊ0.005ms*2000=10ms
    PWMPER2  = 250;   //ͨ��2������Ϊ0.005ms*2000=10ms
    PWMPER3  = 250;   //ͨ��3������Ϊ0.005ms*2000=10ms

    PWME = 0xff;                          
}

//-------------------------------------------------------------------------* 
//������: PWMOutput                                                        *
//��  ��: ����PWMģ��                                                      *
//��  ��: ��                                                               *
//��  ��: ��                                                               * 
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
//static uint8 *pPWMPERn[8] = {&PWMPER01,&PWMPER01,&PWMPER2,&PWMPER3,&PWMPER4,&PWMPER5,&PWMPER6,&PWMPER7};
uint8 *pPWMDTYn[8] = {&PWMDTY0,&PWMDTY1,&PWMDTY2,&PWMDTY3,&PWMDTY4,&PWMDTY5,&PWMDTY6,&PWMDTY7};
//uint8 pPWMDTYn[8] = {PWMDTY0,PWMDTY01,PWMDTY2,PWMDTY3,PWMDTY4,PWMDTY5,PWMDTY6,PWMDTY7};  
/*void PWMOutput(uint8 nCh,uint8 nCycle,uint8 nWide){
    if(nCh > 7)
      return;
    if(nCycle == 0 || nWide == 0) {
      PWME &= 0xff^(0x01 << nCh);
      return;
    }
    *pPWMPERn[nCh] = nCycle; 
    *pPWMDTYn[nCh] = nWide;
    //ʹ����Ӧ��PWM����λ
    PWME |= (0x01 << nCh);   
}      */

void PWMOutput(uint8 nCh,uint8 status)
{
    if(status == ON) {
      
      PWME = 0xff;
      *pPWMDTYn[nCh] = 125;
    }
    else if (status == OFF) {
      
      PWME = 0x00;
    }
}
