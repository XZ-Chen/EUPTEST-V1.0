#include "SPI.h"
#include "SysTask.h"
#include "Diagnostic.h"

extern SYS_PARA sys_para;
#define G_un16Inject1Err      sys_para.item.un16Inject1Err
#define G_un16Inject2Err      sys_para.item.un16Inject2Err
#define G_un16bErrCount       sys_para.item.un16bErrCount
#define CMD_A3944_broken 0x803f


void InjectDigProcess(void)
{
    UINT16 errflag;
    //G_un16Inject1Err = SPIReadWord(SPI_A39441,CMD_A3944_broken); 
    errflag = SPIReadWord(SPI_A39441,CMD_A3944_broken);
    if(errflag & 0x0001) {  //0x0001根据硬件调整
       G_un16Inject1Err = TRUE;
    }    
}





















