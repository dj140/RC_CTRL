#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "Communication/ComPrivate.h"

/*��ѡ�е�ѡ��*/
static int16_t ItemSelect = 0;

/*��ѡѡ��������*/
static uint8_t ItemSelect_MAX = 0;

/**
  * @brief  ҳ���ʼ���¼�
  * @param  ��
  * @retval ��
  */
static void Setup()
{
    Com_SetEnable(false);//ң�عر�
    ItemSelect_MAX = 0;
    ItemSelect = 0;
    
    /*���û�����Ϣ*/
    RCX::Handshake::Pack_t* master = RCX::Handshake::GetMaster();
    master->EnableFunction.Passback = CTRL.State->Passback;
    master->EnableFunction.FHSS = CTRL.State->FHSS;
    master->Speed = nrf.GetSpeed();

    /*���ֳ�ʼ��*/
    RCX::Handshake::Init(&nrfTRM, &nrfFHSS, XC_NAME);
    
    /*����׼������*/
    RCX::Handshake::Process(RCX::Handshake::State_Prepare);
    
    Serial.println("Searching...");
    /*��ʱ����*/
    uint32_t time = millis();
    uint8_t ItemSelect_MAX_Last = 0;
    while(millis() - time < 5000)
    {
        /*��ȡ�ӻ��б�����*/
        ItemSelect_MAX = RCX::Handshake::Process(RCX::Handshake::State_Search);

        if(ItemSelect_MAX > ItemSelect_MAX_Last)
        {
            Serial.printf("Find %d Slave...\r\n", ItemSelect_MAX);
            ItemSelect_MAX_Last = ItemSelect_MAX;
            break;
        }

        PageDelay(1);
    }

    /*��ʾ�������*/
    Serial.println(ItemSelect_MAX > 0 ? "Search Done!" : "Not Found!");
    PageDelay(200);
}

/**
  * @brief  ҳ��ѭ���¼�
  * @param  ��
  * @retval ��
  */
static void Loop()
{
    page.PagePush(PAGE_CtrlPage);
}

/**
  * @brief  ҳ���˳��¼�
  * @param  ��
  * @retval ��
  */
static void Exit()
{
    /*�������Ӵӻ�*/
    Serial.println("Connecting...");

    /*��ʱ����*/
    uint32_t timeout = millis();
    bool IsTimeout = false;
    /*�ȴ��ӻ���Ӧ�����ź�*/
    while(
        RCX::Handshake::Process(
            RCX::Handshake::State_ReqConnect, 
            ItemSelect, 
            RCX::Handshake::CMD_AttachConnect
        ) 
        != RCX::Handshake::CMD_AgreeConnect
    )
    {
        /*��ʱ*/
        if(millis() - timeout > 1000)
        {
            Serial.println("Timeout");
            IsTimeout = true;
            break;
        }
        PageDelay(1);
    }

    /*������β���ã���ת��Լ���õ�����Ƶ���Լ���ַ*/
    RCX::Handshake::Process(RCX::Handshake::State_Connected);

    /*���δ��ʱ��ʾ���ֳɹ�*/
    if(!IsTimeout)
    {
        Serial.println("Connect successfully");
        Audio_PlayMusic(MC_Type::MC_Connect);
    }
    else
    {
        Audio_PlayMusic(MC_Type::MC_UnstableConnect);
    }

    nrf.SetRF_Enable(false);
}

/**
  * @brief  ҳ���¼�
  * @param  btn:�����¼��İ���
  * @param  event:�¼����
  * @retval ��
  */
static void Event(void* btn, int event)
{
    if(event == ButtonEvent::EVENT_ButtonPress)
    {

    }
}

/**
  * @brief  ҳ��ע��
  * @param  pageID:Ϊ��ҳ������ID��
  * @retval ��
  */
void PageRegister_HandshakeAuto(uint8_t pageID)
{
    page.PageRegister(pageID, Setup, Loop, Exit, Event);
}
