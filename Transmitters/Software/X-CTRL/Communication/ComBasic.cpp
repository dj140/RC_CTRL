#include "Basic/FileGroup.h"
#include "ComPrivate.h"
#include "BSP/BSP.h"

/*ʵ����NRF����*/
NRF_Basic nrf(
    NRF_MOSI_Pin, NRF_MISO_Pin, NRF_SCK_Pin,
    NRF_CE_Pin, NRF_CSN_Pin
);
//IRQ   MISO
//MOSI  SCK
//CSN   CE
//VCC   GND

/*��Ƶ�շ�������*/
NRF_TRM  nrfTRM(&nrf);

/*��Ƶ�շ�������*/
NRF_FHSS nrfFHSS(&nrf);

/*NRF�������ݻ�����*/
static uint8_t NRF_TxBuff[32];

/*NRF�������ݻ�����*/
static uint8_t NRF_RxBuff[32];

/*ͨ��ʹ��*/
static bool Com_Enable = false;

void Com_SetEnable(bool en)
{
    Com_Enable = en;
    Com_PassbackProcess(en ? PBS_Setup : PBS_Exit);
}

bool Com_GetEnable()
{
    return Com_Enable;
}

/**
  * @brief  ͨ�ų�ʼ��
  * @param  ��
  * @retval true�ɹ� falseʧ��
  */
bool Com_Init()
{
    /*Ĭ�ϳ�ʼ��*/
    bool isInit = nrf.Init();

    /*����ģʽ*/
    nrf.TX_Mode();

    /*���ݰ�����*/
    nrf.SetPayloadWidth(sizeof(NRF_TxBuff), sizeof(NRF_RxBuff));
    
    /*��������*/
    nrf.SetSpeed(CTRL.RF_Config->Speed);
    
    /*����Ƶ��*/
    nrf.SetFreqency(CTRL.RF_Config->Freq);
    
    /*���õ�ַ*/
    nrf.SetAddress(CTRL.RF_Config->Addr);

    /*������Ƶ*/
    nrf.SetRF_Enable(false);

    /*���¼Ĵ���״̬*/
    nrf.UpdateRegs();

    /*�����������*/
    return isInit;
}

static void Com_TxRxProcess()
{
    if(CTRL.State->FHSS)
    {
        nrfFHSS.TxProcess(
            NRF_TxBuff,
            CTRL.State->Passback ? NRF_RxBuff : NULL
        );
    }
    else
    {
        nrfTRM.TranRecv(NRF_TxBuff, NRF_RxBuff);
    }

    if(CTRL.State->Passback)
    {
        RCX::RxLoadPack(NRF_RxBuff);
        Com_PassbackProcess(RCX::RxGetSignalLost() ? PBS_Error : PBS_Loop);
    }
}

/**
  * @brief  ���ݷ�������
  * @param  ��
  * @retval ��
  */
void Com_Update()
{
    if(!Com_Enable)
        return;
    
    /*д�밴��״̬*/
    RCX::TxSetPackKey(CTRL.Key.Value);
    /*�������ݰ������ͻ�����*/
    RCX::TxLoadPack(NRF_TxBuff);

    if(CTRL.State->FHSS || CTRL.State->Passback)
    {
        Com_TxRxProcess();
    }
    else
    {
        if(nrf.GetRF_State() != nrf.State_TX)
        {
            nrf.TX_Mode();
        }
        nrf.TranCheck();
        nrf.Tran(NRF_TxBuff);//NRF��������
    }
}
