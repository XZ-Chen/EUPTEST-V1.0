//-------------------------------------------------------------------------*
//文件名:EUP Injector.c      					                             	     *
//说  明:喷射阀高低压分时驱动测试文件											                               *
//初始时间：  2017年07月04日
//作者：陈祥榛              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                          	                 *
//-------------------------------------------------------------------------*
#include "EUPInjector.h"

//-------------------------------------------------------------------------*
//函数名: EUPInjector                                                   	     *
//功  能: 初始化喷射阀                                                 * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*


void EUPInjectorInit(void)
{
   //if(G_un16SysMode = SYS_DURAL)
   ECT_TFLG1_C7F = 1;
   ECT_TC7 = ECT_TCNT + 1000;         //设置输出比较时间为0.4ms
          
}

void EUPInjector(uint16 nWide) //喷射时间
{
    if(nWide == 0) { 
       DOOutput(INJECTOR_PIN1,OFF);
       DOOutput(INJECTOR_PIN2,OFF);
       DOOutput(INJECTOR_PIN3,OFF);
       DOOutput(INJECTOR_PIN4,OFF);
    
    }
    DOOutput(Cylinder_1,ON);
    //_nop_();
    DOOutput(DIESELINJ_HV,ON);
    ECT_TFLG1_C7F = 1;
    ECT_TC7 = ECT_TCNT + 1000;         //设置输出比较时间为0.4ms
    
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED        
interrupt VectorNumber_Vectch7 void ECT_OC7(void) 
{
  if(ECT_TFLG1_C7F == 1)
  {
    ECT_TFLG1_C7F = 1;
    ECT_TC6 = ECT_TCNT + 1250;         //设置输出比较时间为0.25s
  }
  DOOutput(DIESELINJ_HV,OFF);
    
}
#pragma CODE_SEG DEFAULT

extern G_un16InjWide; 
#pragma CODE_SEG __NEAR_SEG NON_BANKED        
interrupt VectorNumber_Vectch6 void ECT_OC6(void) 
{
  if(ECT_TFLG1_C6F == 1)
  {
    ECT_TFLG1_C6F = 1;
    ECT_TC5 = ECT_TCNT + G_un16InjWide/4;         //设置输出比较时间为0.25s
  }
  PWMOutput(1,ON);  //#define DIESELINJ_LV  1
    
}
#pragma CODE_SEG DEFAULT

#pragma CODE_SEG __NEAR_SEG NON_BANKED        
interrupt VectorNumber_Vectch5 void ECT_OC5(void) 
{
  if(ECT_TFLG1_C5F == 1)
  {
    ECT_TFLG1_C5F = 1;
    //ECT_TC5 = ECT_TCNT + G_un16InjWide/4;         //设置输出比较时间为0.25s
  }
  PWMOutput(1,OFF);
    
}
#pragma CODE_SEG DEFAULT
