//-------------------------------------------------------------------------*
//文件名:EUP Injector.h      					                             	     *
//说  明:喷射阀高低压分时驱动测试文件											                               *
//初始时间：  2017年07月04日
//作者：陈祥榛              			           			           *
//修订记录：     		              			           				                 *
//备注：      适用于MC9S12XET256                         	                 *
//-------------------------------------------------------------------------*
#ifndef _EUPINJECTOR_H_
#define _EUPINJECTOR_H_

//1、头文件   
#include "PIT.h"
#include "typedefine.h"           //类型别名定义
#include <MC9S12XET256.h>     /* derivative information */
#include <hidef.h> 
#include "PinMap.h"
#include "DIOModule.h"
//-------------------------------------------------------------------------*
//函数名: InjectorModuleInit                                               *
//功  能: 初始化喷射阀模块                                                 * 
//参  数: 无															                                 *
//返  回: 无                                                               *
//说  明: 无                                                               *
//-------------------------------------------------------------------------*

void EUPInjectorInit(void);
void EUPInjector(uint16 nWide);
#define InjectorOff() InjectorWide(0,0) 

#endif