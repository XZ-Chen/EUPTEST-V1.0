//-------------------------------------------------------------------------*
//�ļ���:  					                             	                   *
//˵  ��: 	  								                       *
//��ʼʱ�䣺  2012��06��30��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#ifndef _DFLASHMODULE_H_           //��ֹ�ظ�����
#define _DFLASHMODULE_H_ 

//1��ͷ�ļ�    
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "SysTask.h"
void MapToBuffer(uint16 *ptr);
void WriteToFlash(void);
//void PedalReadFlash(uint16 *pSensor);
//-----------------------------------------------------------------------*
//������: SensorModuleInit                                                  	   *
//��  ��: ��ʼ��ATDģ��                                                  * 
//��  ��: ��															                               *
//��  ��: ��                                                             *
//˵  ��: ��                                                             *
//-----------------------------------------------------------------------*
typedef struct{
  uint8 WritedFlag;
  uint8 CopyFlag;
}FlashPara;
void DFlash_ParaInit(void);
void JudgeFlashStatus(void);
void DFlash_ParaInit(void);
void ReadFromFlash(void);  
void MapPedalAdBgn(void);   
uint8 checkFlashStatus(void); 
void CheckSave(void);  
#endif



