#include "Basic/FileGroup.h"
#include "ComPrivate.h"

/*��ѡ�е�ѡ��*/
static int16_t ItemSelect = 0;

/*��ѡѡ��������*/
static uint8_t ItemSelect_MAX = 0;

static void ConnectSetup()
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
    RCX::Handshake::Init(&nrfTRM, &nrfFHSS);
    
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
    }

    /*��ʾ�������*/
    Serial.println(ItemSelect_MAX > 0 ? "Search Done!" : "Not Found!");
}

static void ConnectProcess()
{
    /*�������Ӵӻ�*/
    Serial.printf("Connecting %s...\r\n", RCX::Handshake::GetSlave(ItemSelect)->Description);

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
    }

    /*������β���ã���ת��Լ���õ�����Ƶ���Լ���ַ*/
    RCX::Handshake::Process(RCX::Handshake::State_Connected);

    /*���δ��ʱ��ʾ���ֳɹ�*/
    if(!IsTimeout)
    {
        Serial.println("Connect successfully");
    }
    else
    {
        Serial.println("Connect timeout");
    }

    nrf.SetRF_Enable(false);
}

void Com_TestSetup()
{
    Serial.begin(115200);
    CTRL.State->Handshake = true;
    CTRL.State->FHSS = true;
    CTRL.State->Passback = false;
    
    if(Com_Init())
    {
        Serial.println("RF init successful");
    }
    ConnectSetup();
    ConnectProcess();
    
    nrf.SetRF_Enable(true);
    RCX::ChannelReset();
    Com_SetEnable(true);
}

static void Joystick_Update()
{
    CTRL.JS_L.X.Val++;
    CTRL.JS_R.Y.Val++;
    
    if(CTRL.JS_L.X.Val > RCX_CHANNEL_DATA_MAX)
        CTRL.JS_L.X.Val = -RCX_CHANNEL_DATA_MAX;
    
    if(CTRL.JS_R.Y.Val > RCX_CHANNEL_DATA_MAX)
        CTRL.JS_R.Y.Val = -RCX_CHANNEL_DATA_MAX;
}

void Com_TestLoop()
{
    __IntervalExecute(Com_Update(), 10);
    __IntervalExecute(Serial.printf("RSSI:%d\r\n", nrf.GetRSSI()), 1000);
    __IntervalExecute(Joystick_Update(), 1);
}
