//-------------------------------------------------------------------------*
//�ļ���: SysTask.c                                                    	   *
//˵  ��: ϵͳ�����ļ�                                          		       *
//��ʼʱ�䣺  2012��10��20��              			                           *
//�޶���¼��     		              			                                   *
//��ע��      ������MC9S12XS128               			                       *
//-------------------------------------------------------------------------*
#include "SysTask.h"
#include "MAP.h"
#include "Includes.h"
#include "DFlashModule.h"
#include "Diagnostic.h" 
#include "PWM.h"
SYS_PARA sys_para;
                           
#define G_SysParaBgn       sys_para.data
#define G_un16SysMode      sys_para.item.mem_var.un16SysMode       //0ϵͳ��ģʽ
#define G_un16DuralMode    sys_para.item.mem_var.un16DuralMode     //1˫ȼ��ģʽ
#define G_un16InjWide      sys_para.item.mem_var.un16InjWide       //2����ʱ��
#define G_un16StepperPos   sys_para.item.mem_var.un16StepperPos    //3���λ��

#define G_un16Pedal        sys_para.item.mem_var.un16Pedal         //4
#define G_bSensorScan      sys_para.item.mem_var.bSensorScan       //
#define G_bIOScan          sys_para.item.mem_var.bIOScan           //
#define G_bModeJudge       sys_para.item.mem_var.bModeJudge        //
#define G_bOutput          sys_para.item.mem_var.bOutput           //
#define G_SensorAddrBgn    sys_para.item.un16Sensor                //
#define G_un16RPM          sys_para.item.un16Sensor[0]             //ת��ADֵ
#define G_un16PedalPosAD   sys_para.item.un16Sensor[1]             //����λ��ADֵ
#define G_un16StepperPosAD sys_para.item.un16Sensor[2]             //�������λ��ADֵ
#define G_un16ExhasutTemp  sys_para.item.un16Sensor[3]          //
#define G_DIAddrBgn        sys_para.item.un16DI                 //
#define G_DIIGSwitch       sys_para.item.un16DI[0]              //
#define G_DILNGSwitch      sys_para.item.un16DI[1]              //

#define G_DOLNGRVRelay     sys_para.item.un16DO[0]       //LNG��ѹ��
#define G_DOMainRelay      sys_para.item.un16DO[1]       //���̵���

#define G_un16HighSpeed    sys_para.item.const_var.un16HighSpeed  //
#define G_un16HSK1         sys_para.item.const_var.un16HSK1       //
#define G_un16LSK2         sys_para.item.const_var.un16LSK2       //
#define G_un16StpP1        sys_para.item.const_var.un16StpP1      //
#define G_un16StpP2        sys_para.item.const_var.un16StpP2      //

#define G_PedalAdBgn       sys_para.item.un16PedalAd
#define G_bErrJudge        sys_para.item.un16bErrJudge
#define G_un16bErrCount    sys_para.item.un16bErrCount
#define G_un16Inject1Err   sys_para.item.un16Inject1Err
////////////////////////////////////////////////////////
//ȫ�ֱ�����ʼ��                                      //
////////////////////////////////////////////////////////
void SysVarInit(void)
{
    uint8 i;
    for(i=0;i<255;i++) {
       *(G_SysParaBgn + i) = 0;
    }
    //for test/////////////////////////////////
    G_un16StepperPos = 0;        //���Ը���ͬ��ֵ
    G_un16HSK1 = LNG_HSK1;
    G_un16LSK2 = LNG_LSK2;
    G_un16StpP1 = STEPPER_P1;
    G_un16StpP2 = STEPPER_P2;
    G_un16HighSpeed = LNG_HIGHSPEED;
    G_un16InjWide = 0;
    //for test/////////////////////////////////
    G_un16SysMode = SYS_SINGLE;
    G_un16DuralMode = DURAL_MODE_STOP;
    G_DOLNGRVRelay = OFF;
    G_DOMainRelay = OFF;
    G_bSensorScan = FALSE;
    G_bIOScan = FALSE;
    G_bModeJudge = FALSE;
    G_bOutput = FALSE;  
    G_bErrJudge = FALSE; 
    G_un16Inject1Err = FALSE; 
    MainRelayOff();
    LNGRVRelayOff();
    InjectorOff();  
}

///////////////////////////////////////////////////////
//��ȼ��ģʽ����                                     //
///////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//��ʼ����ϣ��������ģʽ                            //
//����ģʽ����                                        //
//��IG��𿪹عر�                                    //
//1.��ʱ2s�ر����̵���                                //
//2.���̵����رպ󣬲����������ʼλ��                //
//3.���������λ��LNG��ѹ���Ŵ򿪣�2S��ر�         //
////////////////////////////////////////////////////////
void SysSingleProcess(void){
   static uint16 nTicks = 0;
   static uint16 nSeq = 0;
   if(G_DILNGSwitch != ON)
   {
       nSeq = 0;
       if(G_un16StepperPos != 0)
          // G_un16StepperPos = 0;
       if(G_DOLNGRVRelay == ON) 
       {
           nTicks ++;
           if(nTicks == 10) 
           {  
              G_DOLNGRVRelay = OFF;
              nTicks = 0;
           }
       }
       if(G_un16InjWide != 0)
           G_un16InjWide = 0;
       return;
   }
   if(nSeq == 0)   //10*0.2s = 2s    �̵����պ�
   { 
      nTicks++;
      if(nTicks == 10) {   
        G_DOMainRelay = ON;
        nSeq = 1;
        nTicks = 0; 
      }
   } else if(nSeq == 1) {
      ////////////////////////////////// for test
      G_un16StepperPos = 150;         //���������λֵ ����ֵ
      //////////////////////////////////
      G_DOLNGRVRelay = ON;
      nTicks = 0;
      nSeq = 2;
   }else if(nSeq == 2) {
      nTicks++;
      if(nTicks == 10) { //200ms*10 = 2s
        nTicks = 0;
        nSeq = 0;
        G_un16StepperPos = 0;
        G_DOLNGRVRelay = OFF;
        G_un16SysMode = SYS_DURAL;
      }
   }
}


///////////////////////////////////////////////////////
//˫ȼ��ģʽ����                                     //
///////////////////////////////////////////////////////
void SysDuralProcess(void) 
{
   DuralModeJudge();
   DuralAppExcute();
}
///////////////////////////////////////////////////////
//ϵͳ����ģʽ����                                   //
///////////////////////////////////////////////////////
void SysErrProcess(void) {
  
}

//////////////////////////////////////////////////////
//ִ�����������                                    //
//////////////////////////////////////////////////////
void SysOutputProcess(void)
{
   static uint16 nStepperPre = 1; //��1����Ϊ0�ĳ�ʼֵ
   static uint16 nInjWidePre = 1;
   static uint16 nDesPosAD = STEPPER_AD_MIN;
   static uint8 nStepperStatus = STEPPER_RUN;
   static uint16 nCycle;
   uint32 nTemp; 
   if(G_DOMainRelay == ON)    
      MainRelayOn();
   else {
      MainRelayOff();
      return;
   }
   if(G_DOLNGRVRelay == ON)
      LNGRVRelayOn();
   else
      LNGRVRelayOff();
   if(G_un16StepperPos != nStepperPre) {
      nStepperStatus = STEPPER_RUN;
      nStepperPre = G_un16StepperPos;
      nDesPosAD = look1D_U16_U16(G_un16StepperPos,un16TabStepperCnt,13,un16TabStepperAD);   
   }
   nStepperStatus = StepperRun(G_un16StepperPos,nDesPosAD,G_un16StepperPosAD);
   if(G_un16InjWide != nInjWidePre){ 
      if(G_un16InjWide != 0) {
        // nTemp = 120000000/G_un16RPM/CRANK_CYLINDER_NUM;
         nTemp = 20000;
         nCycle = nTemp&0xffff;
      }
      else
         nCycle = 0;
      InjectorWide(nCycle,G_un16InjWide);
      EUPInjector(G_un16InjWide);
      //PWMOutput(3,218);
      //PWMOutput(2,77);
      //PWMOutput(1,111);
      nInjWidePre = G_un16InjWide;
   }
}
///////////////////////////////////////////////////////
//ϵͳ��ģʽ����                                     //
///////////////////////////////////////////////////////

void SysTaskProcess(void)
{
    if(G_bIOScan){ 
      DIScan(G_DIAddrBgn);       //����ɨ��  ��𿪹� LNG��ѹ������
      G_bIOScan = FALSE;
    }
    if(G_bSensorScan){
      SensorScan(G_SensorAddrBgn);   //������ɨ��    
      CheckSave();
      PedalRead(G_PedalAdBgn);
      G_bSensorScan = FALSE;
    }
    if(G_bErrJudge) {
      InjectDigProcess();
    }
    if(G_bModeJudge) {  
      switch(G_un16SysMode) {
        case SYS_SINGLE:
          SysSingleProcess();    //��ȼ��ģʽ����          
          break;
        case SYS_DURAL:
          SysDuralProcess();     //˫ȼ��ģʽ����
          break;                 
        case SYS_ERR:
          SysErrProcess();
          break;  
      }
      G_bModeJudge = FALSE;
    }
    if(G_bOutput) { 
      SysOutputProcess();
      G_bOutput = FALSE;
    }
}
///////////////////////////////////////////////////////
//ϵͳ����ģʽ����                                   //
///////////////////////////////////////////////////////
void SysDigProcess(void)
{
    if(G_un16bErrCount == 3) {
      SysSingleProcess();  
    }
}
///////////////////////////////////////////////////////
//ϵͳ˫ȼ��ģʽ����                                 //
///////////////////////////////////////////////////////

void DuralModeJudge(void)
{

	static uint16 nPedalADPre = PEDAL_AD_MIN; //for test  PEDAL_AD_MIN = 25
	uint16 nPedalRatio = 0;
	if(G_DILNGSwitch == OFF) {
	   G_un16SysMode = SYS_SINGLE;
	   return;
	}
  G_un16DuralMode = DURAL_MODE_STOP; //    DURAL_MODE_STOP = 0
  G_un16Pedal = look1D_U16_U16(G_un16PedalPosAD,un16TabPedalAD,10,un16TabPedalPercent);  //��������̤��MAP	
  nPedalRatio = 1000 + 2*G_un16PedalPosAD - 2*nPedalADPre;  
  //********************���ٹ���****************************//
  if(G_un16RPM>2800)  
	{
			//ת��>2800rpm
			G_un16DuralMode = DURAL_MODE_SPEEDLIMIT;    //  DURAL_MODE_SPEEDLIMIT = 6
			goto RETURN;
	}
	//****************�����ٹ���**************// 
  if(nPedalRatio > PEDAL_RATIO_MAX &&G_un16RPM >= 750)  //  PEDAL_RATIO_MAX=1200 
	{		
		 G_un16DuralMode = DURAL_MODE_OVERACC;   //  DURAL_MODE_OVERACC = 4
	   goto RETURN;
	}
	//****************�����ٹ���**************//
  if(nPedalRatio < PEDAL_RATIO_MIN && G_un16RPM >= 750)     //PEDAL_RATIO_MIN=900 
	{
		 G_un16DuralMode = DURAL_MODE_OVERDEC;		
		 goto RETURN;
  }
  //*****************������ʻ����***************************//
  if(G_un16Pedal>=10 && G_un16RPM >=1100)   //
  {
	   G_un16DuralMode = DURAL_MODE_NORMAL;   //DURAL_MODE_NORMAL = 3
	}
  RETURN:
  nPedalADPre = G_un16PedalPosAD;     // ����λ�ø���ֵ
}
///////////////////////////////////////////////////////
//ϵͳ˫ȼ��ִ�����������                           //
///////////////////////////////////////////////////////
void DuralAppExcute(void){
  
	switch( G_un16DuralMode)
	{
		case DURAL_MODE_STOP:
			EngineStopCtrl();
			break;
		case DURAL_MODE_NORMAL:
			NormalCtrl();
			break;
		case DURAL_MODE_SPEEDLIMIT:
			SpeedLimitCtrl();
			break;
		case DURAL_MODE_OVERACC:
			OverAccCtrl();
			break;
		case DURAL_MODE_OVERDEC:
			OverDecCtrl();
			break;
	}
}
/*************************************************************/
/*                      ˫ȼ����ͨģʽ                       */
/*************************************************************/
void NormalCtrl()
{
  uint32 nTemp;
  G_DOLNGRVRelay = ON;
	/***************��ѯmap*******************************/
	G_un16InjWide = look2D_U16_U16_U16(G_un16RPM,G_un16Pedal, \
						        	u16TabSpeedX, 19,\
							        u16TabPedalY, 14,u16TabInjWidth);
	/*G_un16StepperPos = look2D_U16_U16_U16(G_un16RPM,G_un16Pedal, \
						        	u16TabSpeedX, 19,\
							        u16TabPedalY,14,u16TabStepperPos);
	/***************���������������*******************************						        
  nTemp = ((uint32)G_un16StepperPos + (uint32)G_un16StpP1)*((uint32)G_un16StpP2);
  nTemp = nTemp/100;
  G_un16StepperPos = nTemp&0xffff;   */
  
	//***************���䷧�������*******************//
	if (G_un16RPM >= G_un16HighSpeed)	
	{
			nTemp = (uint32)G_un16InjWide*(uint32)G_un16HSK1;
			nTemp = nTemp/100;
			G_un16InjWide = nTemp&0xffff;
			
	}
	else
	{
	   	nTemp = (uint32)G_un16InjWide*(uint32)G_un16LSK2;
			nTemp = nTemp/100;
			G_un16InjWide = nTemp&0xffff;
	}
}
/*************************************************************/
/*                      ˫ȼ���ٶ�����ģʽ                   */
/*************************************************************/
void SpeedLimitCtrl()
{
	 if(G_un16StepperPos != 0)	  
       G_un16StepperPos = 0;
	 
   if(G_un16InjWide != 0)
       G_un16InjWide = 0;
   
   G_DOLNGRVRelay = OFF;
}
/*************************************************************/
/*                      ˫ȼ�ϼ����ٿ���ģʽ                 */
/*************************************************************/
void OverAccCtrl()
{
    G_DOLNGRVRelay = ON;
    G_un16StepperPos = 500;
    G_un16InjWide = look2D_U16_U16_U16(G_un16RPM,G_un16Pedal, \
						        	u16TabSpeedX, 19,\
							        u16TabPedalY, 14,u16TabInjWidth);
}
/*************************************************************/
/*                      ˫ȼ�ϼ�����ģʽ                     */
/*************************************************************/
void OverDecCtrl()
{   
    G_DOLNGRVRelay = ON;
    G_un16StepperPos = 300;
    //G_un16InjWide = 1500;
}
/*************************************************************/
/*                      ������ֹͣģʽ                       */
/*************************************************************/
void EngineStopCtrl()
{
	 if(G_un16StepperPos != 0)
       G_un16StepperPos = 0;
   if(G_un16InjWide != 0)
       G_un16InjWide = 0;
   G_DOLNGRVRelay = OFF;
}

/*************************************************************/
/*                      ��ȡMAP                              */
/*************************************************************/  
void PedalRead(uint16 *pSensor) {
    uint8 i;
    //CopyPedalMap();
    for(i=0;i<11;i++)
	    *(pSensor+i) = *(G_PedalAdBgn+i);
}
extern uint16 un16TabPedalAD[11]; 
void CopyPedalMap(void) {
    uint8 i,flag;
    flag = checkFlashStatus();
    if(flag) {
      ReadFromFlash();
      for(i=0;i<11;i++)
	      *(G_PedalAdBgn+i) = un16TabPedalAD[i];
    } else{
      //for(i=0;i<11;i++)
	     // *(G_PedalAdBgn+i) = un16TabPedalAD[i];
    } 
}



