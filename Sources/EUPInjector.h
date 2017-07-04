//-------------------------------------------------------------------------*
//�ļ���:EUP Injector.h      					                             	     *
//˵  ��:���䷧�ߵ�ѹ��ʱ���������ļ�											                               *
//��ʼʱ�䣺  2017��07��04��
//���ߣ������              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*
#ifndef _EUPINJECTOR_H_
#define _EUPINJECTOR_H_

//1��ͷ�ļ�   
#include "PIT.h"
#include "typedefine.h"           //���ͱ�������
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "PinMap.h"
#include "DIOModule.h"
//-------------------------------------------------------------------------*
//������: InjectorModuleInit                                               *
//��  ��: ��ʼ�����䷧ģ��                                                 * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*

void EUPInjectorInit(void);
void EUPInjector(uint16 nWide);
#define InjectorOff() InjectorWide(0,0) 

#endif