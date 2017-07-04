//-------------------------------------------------------------------------*
//�ļ���:EUP Injector.c      					                             	     *
//˵  ��:���䷧�ߵ�ѹ��ʱ���������ļ�											                               *
//��ʼʱ�䣺  2017��07��04��
//���ߣ������              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XET256                          	                 *
//-------------------------------------------------------------------------*
#include "EUPInjector.h"

//-------------------------------------------------------------------------*
//������: EUPInjector                                                   	     *
//��  ��: ��ʼ�����䷧                                                 * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*


void EUPInjectorInit(void)
{
   //if(G_un16SysMode = SYS_DURAL)
   ECT_TFLG1_C7F = 1;
   ECT_TC7 = ECT_TCNT + 1000;         //��������Ƚ�ʱ��Ϊ0.4ms
          
}

void EUPInjector(uint16 nWide) //����ʱ��
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
    ECT_TC7 = ECT_TCNT + 1000;         //��������Ƚ�ʱ��Ϊ0.4ms
    
}
#pragma CODE_SEG __NEAR_SEG NON_BANKED        
interrupt VectorNumber_Vectch7 void ECT_OC7(void) 
{
  if(ECT_TFLG1_C7F == 1)
  {
    ECT_TFLG1_C7F = 1;
    ECT_TC6 = ECT_TCNT + 1250;         //��������Ƚ�ʱ��Ϊ0.25s
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
    ECT_TC5 = ECT_TCNT + G_un16InjWide/4;         //��������Ƚ�ʱ��Ϊ0.25s
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
    //ECT_TC5 = ECT_TCNT + G_un16InjWide/4;         //��������Ƚ�ʱ��Ϊ0.25s
  }
  PWMOutput(1,OFF);
    
}
#pragma CODE_SEG DEFAULT
