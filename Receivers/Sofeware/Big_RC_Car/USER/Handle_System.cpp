#include "FileGroup.h"

void IWDG_Init(uint8_t prescaler, uint16_t reload)
{
    /*Tout=((4 * 2 ^ prescaler) * reload)/32 (ms)*/
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); //ʹ�ܶ�IWDG->PR IWDG->RLR��д
    IWDG_SetPrescaler(prescaler); //����IWDG��Ƶϵ��
    IWDG_SetReload(reload);   //����IWDGװ��ֵ
    IWDG_ReloadCounter(); //reload
    IWDG_Enable();       //ʹ�ܿ��Ź�
}
