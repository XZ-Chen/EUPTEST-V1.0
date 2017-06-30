//-------------------------------------------------------------------------*
//�ļ���: ATD.c 					                             	                   *
//˵  ��: ģ/��ת��ģ�������ļ�	  								                         *
//��ʼʱ�䣺  2012��06��30��              			           			           *
//�޶���¼��     		              			           				                 *
//��ע��      ������MC9S12XS128                         	                 *
//-------------------------------------------------------------------------*
#include "ATD.h"

//������ѹ��������


//-------------------------------------------------------------------------*
//������: ATD_Init                                                  	     *
//��  ��: ��ʼ��ATDģ��                                                    * 
//��  ��: ��															                                 *
//��  ��: ��                                                               *
//˵  ��: ��                                                               *
//-------------------------------------------------------------------------*
void ATDInit(void)
{
    ATD0CTL1 = 0b00100000;    //
    ATD1CTL1 = 0b00100000;    //
    //           ||||||||_____ETRIGCH0:  �ⲿ�����ź�ͨ��ѡ�����λ
    //           |||||||______ETRIGCH1:
    //           ||||||_______ETRIGCH2:
    //           |||||________ETRIGCH3:
    //           ||||_________SMP_DIS:   ****����ǰ�ŵ����λ**** 1=����ǰ�ŵ�;0=����ǰ���ŵ�
    //           |||__________SRES0:     ****ADת������ѡ��λ****
    //           ||___________SRES1:     00 8λ����  01 10λ���� 11 12λ����
    //           |____________ETRIGSEL:  �ⲿ����ѡ��λ����δ֪�� 
    
    ATD0CTL2 = 0b01000000;
    ATD1CTL2 = 0b01000000;     //
    //           ||||||||_____ACMPIE:    ATD�Ƚ��ж�ʹ��λ
    //           |||||||______ASCIE:     ATDת�����н����ж�ʹ��λ 1=����
    //           ||||||_______ETRIGE:    �ⲿ��������λ
    //           |||||________ETRIGP:    �ⲿ�������Կ���λ
    //           ||||_________ETRIGLE:   �ⲿ������ƽ/���ؿ���λ
    //           |||__________ICLKSTP:   ֹͣģʽ�ڲ�ʱ��ʹ��λ
    //           ||___________AFFC:      ****ATD��־�������ʹ��λ**** 1=�Զ����CCFλ��0=�������CCFλ
    //           |____________0
    
    ATD0CTL3 = 0b10001000;    //
    ATD1CTL3 = 0b10001000;    //
    //           ||||||||_____FRZ0:  �����������λ
    //           |||||||______FRZ1
    //           ||||||_______FIFO:  ����Ĵ����Ƚ��ȳ�ģʽ����λ ת��ӳ������
    //           |||||________S1C:   ****ת�����г���ѡ�����λ****
    //           ||||_________S2C:   *��ͨ������
    //           |||__________S4C:
    //           ||___________S8C:
    //           |____________DJM:   ****ת��������뷽ʽ����λ****  1=�Ҷ��룻0=�����  
    
    ATD0CTL4 = 0b00000011;    // ����Ƶ��Ϊ5MHZ��0.28~8.3��   PRS = 3
    ATD1CTL4 = 0b00000011;    // ����Ƶ��Ϊ5MHZ��0.28~8.3��   PRS = 3
    //           ||||||||_____PRS0:  ****A/Dת��Ԥ��Ƶ���ÿ���λ****  ATD��������
    //           |||||||______PRS1:  f(ATDCLK)=f(BUS)/[2*(PRS+1)]
    //           ||||||_______PRS2:
    //           |||||________PRS3:  
    //           ||||_________PRS4:
    //           |||__________SMP0:  ����ʱ��ѡ��λ ����ʱ��ΪN��ATD��������
    //           ||___________SMP1:  000  4  001  6  010  8  011 10    
    //           |____________SMP2:  100 12  101 16  110 20  111 24
    
    ATD0DIEN = 0b00000000;   //     ��ֹ�����ж�����
    ATD1DIEN = 0b00000000;   //     ��ֹ�����ж����� 
    //           ||||||||____IEN7   �����ź�����ʹ�ܿ���λ
    //           |||||||_____IEN6   1  ��Ӧλ�����ź������ֹ
    //           ||||||______IEN5   0  ��Ӧλ�����ź�����ʹ��
    //           |||||_______IEN4
    //           ||||________IEN3
    //           |||_________IEN2
    //           ||__________IEN1
    //           |___________IEN0  
    //ATD_CR5 = 0b00010000;    //
    //            ||||||||_____CA:    ****����ͨ��ѡ�����λ****
    //            |||||||______CB:
    //            ||||||_______CC:
    //            |||||________CD:
    //            ||||_________MULT:  ****��/��ͨ��A/Dת��ѡ�����λ****        1=��ͨ����0=��ͨ��
    //            |||__________SCAN:  ****����/����A/Dת��ģʽѡ�����λ****    1=����ת����0=����ת��
    //            ||___________SC:    ����ͨ��ת������λ                1=����ͨ��ת��������0=����ͨ��ת����ֹ
    //            |____________0
    //��ֵ��ʱ��ʼת��
    
}
//-------------------------------------------------------------------------*
//������: ATD_Read                                               	     *
//��  ��: ATDģ��ɼ���ѹ                                                  * 
//��  ��: nChͨ������															                                 *
//��  ��: ����ֵ                                                               *
//˵  ��: �ɼ�����ѹ�󲢽���ת���ɶ�Ӧ����ֵ�����磺�¶�                   *
//-------------------------------------------------------------------------*
//��ͨ������ʱ��һ��Ҫע�⣬��ʼͨ���Ĳ���ֵ�Ǵ���ATD0DRL0��ATD0DRH0
//�Դ�����
   
uint16 ATDRead(uint8 nCh)
{
    if(nCh > 16)
      return 0;
    if(nCh < 8) {
       ATD0CTL5 = 0x10 | nCh;  //����һ�㣬����0ͨ����ʼ�ɣ��������Ա�֤һһ��Ӧ
       while(ATD0STAT0_SCF == 0);  //�ȴ�ͨ��ת������   
       return (ATD0DR0H<<8) | ATD0DR0L;   //ͨ��ѡ��     
    }
    else {
      
       ATD1CTL5 = 0x10 | (nCh - 8); 
       while(ATD1STAT0_SCF == 0);  //�ȴ�ͨ��ת������   
       return (ATD1DR0H<<8) | ATD1DR0L;   //ͨ��ѡ��
    }
}















z


























