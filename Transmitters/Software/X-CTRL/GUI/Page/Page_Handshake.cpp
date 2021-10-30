#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "Communication/ComPrivate.h"
#include "Model/XC_Model.h"

static lv_obj_t * appWindow;

static int16_t SlaveSelectNum = 0;
static uint8_t SlaveFoundNum = 0;
static bool SlaveConnectExit = false;
static bool SlaveBreakSearch = false;

#ifndef PART_SEARCH
static lv_obj_t * preloadSearch;
static lv_obj_t * labelSlaveNum;
static lv_obj_t * labelState;

static void SearchPreload_Creat(lv_obj_t * par)
{
    lv_obj_t * preload = lv_preload_create(par, NULL);
    
    static lv_style_t style;
    style = *lv_preload_get_style(preload, LV_PRELOAD_STYLE_MAIN);
    style.line.width = 10;                         /*10 px thick arc*/
    style.line.color = lv_color_hex3(0x258);       /*Blueish arc color*/

    style.body.border.color = lv_color_hex3(0xBBB); /*Gray background color*/
    style.body.border.width = 10;
    style.body.padding.left = 0;
    lv_preload_set_style(preload, LV_PRELOAD_STYLE_MAIN, &style);
    
    lv_preload_set_type(preload, LV_PRELOAD_TYPE_FILLSPIN_ARC);
    lv_obj_set_size(preload, 40, 40);
    lv_obj_align(preload, par, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);
    
    preloadSearch = preload;
    
    lv_obj_t * label = lv_label_create(par, NULL);
    lv_label_set_text(label, "0");
    lv_obj_align(label, preload, LV_ALIGN_CENTER, 0, 2);
    lv_obj_set_auto_realign(label, true);
    labelSlaveNum = label;
}

static void StateLabel_Creat(lv_obj_t * par)
{
    lv_obj_t * label = lv_label_create(par, NULL);
    LV_LABEL_SET_FONT(label, HandGotn_20, LV_COLOR_BLACK);
    lv_label_set_text(label, "searching...");
    lv_obj_align(label, preloadSearch, LV_ALIGN_OUT_LEFT_MID, -20, 0);
    lv_obj_set_auto_realign(label, true);
    lv_obj_set_opa_scale_enable(label, true);
    
    static lv_anim_t a;
    lv_anim_set_playback(&a, 100);
    lv_anim_set_repeat(&a, 100);
    lv_obj_add_anim(
        label, &a,
        (lv_anim_exec_xcb_t)lv_obj_set_opa_scale,
        LV_OPA_COVER, LV_OPA_TRANSP,
        1000
    );
    
    labelState = label;
}
#endif

#ifndef PART_LIST_SLAVE

static lv_obj_t * listSlave;
static lv_obj_t * listSlaveBtn[5];

static void SlaveList_EventHandler(lv_obj_t * obj, lv_event_t event)
{
    if(event == LV_EVENT_APPLY)
    {
        page.PagePush(PAGE_CtrlPage);
    }
}

static void SlaveList_Creat(lv_obj_t * par)
{
    lv_obj_t * list = lv_list_create(par, NULL);
    lv_obj_set_size(list, AppWindow_GetWidth() - 30, AppWindow_GetHeight() - 20);
    lv_obj_align(list, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_list_set_edge_flash(list, true);
    lv_list_set_single_mode(list, true);
    lv_list_set_anim_time(list, 200);

    /*����*/
    static lv_style_t style_bg;
    style_bg = lv_style_plain;
    style_bg.body.main_color = LV_COLOR_BLACK;
    style_bg.body.grad_color = LV_COLOR_BLACK;
    style_bg.body.opa = LV_OPA_50;
    style_bg.body.radius = 5;
    style_bg.body.shadow.color = LV_COLOR_BLACK;
    style_bg.body.shadow.width = 10;
    style_bg.body.shadow.type = LV_SHADOW_FULL;
    lv_list_set_style(list, LV_LIST_STYLE_BG, &style_bg);
    
    /*��ť*/
    static lv_style_t style_btn_rel;
    style_btn_rel = *lv_list_get_style(list, LV_LIST_STYLE_BTN_REL);
//    style_btn_rel.body.main_color = LV_COLOR_ARMY_GREEN;
//    style_btn_rel.body.grad_color = LV_COLOR_ARMY_GREEN;
    style_btn_rel.body.border.width = 0;
    lv_list_set_style(list, LV_LIST_STYLE_BTN_REL, &style_btn_rel);
        
    for(int i = 0; i < SlaveFoundNum; i++)
    {
        lv_obj_t * list_btn = lv_list_add_btn(list, NULL, "");
        listSlaveBtn[i] = list_btn;
        lv_obj_set_event_cb(list_btn, SlaveList_EventHandler);
        
        const RCX::Handshake::Pack_t * slave;
        slave = RCX::Handshake::GetSlave(i);

        lv_obj_t * label = lv_list_get_btn_label(list_btn);
        lv_label_set_text_fmt(
            label,
            "T%02x  0x%02x  %s",
            slave->Type,
            slave->ID,
            slave->Description
        );
    }
    listSlave = list;
}
static void SlaveList_Move(int8_t dir)
{
    if(SlaveFoundNum == 0 || listSlave == NULL)
        return;
    
    SlaveSelectNum += dir;
    __LimitValue(SlaveSelectNum, 0, SlaveFoundNum - 1);
//    lv_list_focus(listSlaveBtn[SlaveSelectNum], LV_ANIM_ON);
    lv_list_set_btn_selected(listSlave, listSlaveBtn[SlaveSelectNum]);
}
#endif

static void ExitHandshakeProcess()
{
    nrf.SetRF_Enable(false);
    lv_obj_clean(appWindow);
}

/**
  * @brief  ҳ���ʼ���¼�
  * @param  ��
  * @retval ��
  */
static void Setup()
{
    SearchPreload_Creat(appWindow);
    StateLabel_Creat(appWindow);
    
    Com_SetEnable(false);//ң�عر�
    SlaveFoundNum = 0;
    SlaveSelectNum = 0;
    SlaveConnectExit = false;
    SlaveBreakSearch = false;
    listSlave = NULL;
    
    /*���û�����Ϣ*/
    RCX::Handshake::Pack_t* master = RCX::Handshake::GetMaster();
    master->EnableFunction.Passback = CTRL.State->Passback;
    master->EnableFunction.FHSS = CTRL.State->FHSS;
    master->Speed = CTRL.RF_Config->Speed;

    /*���ֳ�ʼ��*/
    RCX::Handshake::Init(&nrfTRM, &nrfFHSS, XC_NAME);
    
    /*����׼������*/
    RCX::Handshake::Process(RCX::Handshake::State_Prepare);
    
    /*��ʱ����*/
    uint8_t lastFound = 0;
    uint32_t time = millis();
    while(millis() - time < 5000)
    {
        /*��ȡ�ӻ��б�����*/
        SlaveFoundNum = RCX::Handshake::Process(RCX::Handshake::State_Search);

        if(SlaveFoundNum > lastFound)
        {
            lv_label_set_text_fmt(labelSlaveNum, "%d", SlaveFoundNum);
            lastFound = SlaveFoundNum;
        }
        
        if(SlaveBreakSearch)
            break;

        PageDelay(1);
    }

    /*��ʾ�������*/
    lv_label_set_text(labelState, SlaveFoundNum > 0 ? "search done!" : "not found!");
    PageDelay(200);
    lv_obj_set_hidden(labelState, true);
    lv_obj_set_hidden(preloadSearch, true);
    lv_obj_set_hidden(labelSlaveNum, true);
    
    if(SlaveFoundNum == 0)
    {
        SlaveConnectExit = true;
        return;
    }
    
    if(SlaveConnectExit)
        return;
    
    SlaveList_Creat(appWindow);
    SlaveList_Move(0);
}

/**
  * @brief  ҳ��ѭ���¼�
  * @param  ��
  * @retval ��
  */
static void Loop()
{
    if(SlaveConnectExit)
    {
        page.PagePop();
    }
}

/**
  * @brief  ҳ���˳��¼�
  * @param  ��
  * @retval ��
  */
static void Exit()
{
    if(SlaveConnectExit)
    {
        ExitHandshakeProcess();
        return;
    }
    
    lv_obj_set_hidden(listSlave, true);
    lv_obj_set_hidden(labelState, false);
    lv_obj_set_hidden(preloadSearch, false);
    
    /*�������Ӵӻ�*/
    const char* slaveName = RCX::Handshake::GetSlave(SlaveSelectNum)->Description;
    lv_label_set_text_fmt(labelState, ">> %s...", slaveName); 

    /*��ʱ����*/
    uint32_t timeout = millis();
    bool IsTimeout = false;
    /*�ȴ��ӻ���Ӧ�����ź�*/
    while(
        RCX::Handshake::Process(
            RCX::Handshake::State_ReqConnect, 
            SlaveSelectNum, 
            RCX::Handshake::CMD_AttachConnect
        ) 
        != RCX::Handshake::CMD_AgreeConnect
    )
    {
        /*��ʱ*/
        if(millis() - timeout > 1000)
        {
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
        Model_Add(slaveName);
        Com_ChannelInit();
        
        lv_label_set_text(labelState, "success");
        Audio_PlayMusic(MC_Type::MC_Connect);
    }
    else
    {
        lv_label_set_text(labelState, "timeout");
        Audio_PlayMusic(MC_Type::MC_UnstableConnect);
    }

    ExitHandshakeProcess();
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
        if(btn == &btBACK)
        {
            page.PagePop();
            SlaveConnectExit = true;
            SlaveBreakSearch = true;
        }
        if(btn == &btOK)
        {
            SlaveBreakSearch = true;
        }
        
        if(listSlave)
        {
            if(btn == &btUP || btn == &btUPL)
            {
                SlaveList_Move(-1);
            }
            if(btn == &btDOWN || btn == &btDOWNL)
            {
                SlaveList_Move(+1);
            }
            
            if(btn == &btOK)
            {
                lv_event_send(listSlaveBtn[SlaveSelectNum], LV_EVENT_APPLY, NULL);
            }
        }
    }
}

/**
  * @brief  ҳ��ע��
  * @param  pageID:Ϊ��ҳ������ID��
  * @retval ��
  */
void PageRegister_Handshake(uint8_t pageID)
{
    appWindow = AppWindow_GetCont(pageID);
    page.PageRegister(pageID, Setup, Loop, Exit, Event);
}
