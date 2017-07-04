//-------------------------------------------------------------------------*
//文件名: PWM.c                                                        	   *
//说  明: PWM脉冲输出文件                                         		     *
//初始时间：  2015年12月02日              			                           *
//修订记录：  2017年4月10日 重新配置多路输出     		              			                                   *
//备注：      适用于MC9S12XET256               			                       *
//-------------------------------------------------------------------------*
#include "PWM.h"

//-------------------------------------------------------------------------* 
//函数名: PWM_Init                                                         *
//功  能: PWM初始化                                                        *
//参  数：无                                                               * 
//返  回: 无                                                               * 
//说  明: 无                                                               *
//-------------------------------------------------------------------------*  
void PWMInit(void){
    //PWM启动寄存器
    PWME = 0b00000000;  
    PWMPRCLK = 0b00100010; //总线40M ClockA = 10M ClockB = 10MHZ                         
    PWMSCLA = 250;         //ClockSA=ClockA/(2xPWMSCLA)                       
    PWMSCLB = 250;         //ClockSB=ClockB/(2xPWMSCLB)    
    PWMCLK = 0b11111111;                                    
    PWMPOL = 0x00;         
    PWMCAE = 0x00;          
    PWMCTL = 0b00000000;                                      
    PWMPER0  = 250;   //通道0的周期为0.04ms*250=10ms 
    PWMPER1  = 250;   //通道1的周期为0.005ms*2000=10ms
    PWMPER2  = 250;   //通道2的周期为0.005ms*2000=10ms
    PWMPER3  = 250;   //通道3的周期为0.005ms*2000=10ms

    PWME = 0xff;                          
}

//-------------------------------------------------------------------------* 
//函数名: PWMOutput                                                        *
//功  能: 启动PWM模块                                                      *
//参  数: 无                                                               *
//返  回: 无                                                               * 
//说  明: 无                                                               *
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
    //使能相应的PWM控制位
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
