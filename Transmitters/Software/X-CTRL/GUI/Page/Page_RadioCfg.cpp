#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "GUI/lv_settings.h"
#include "Communication/ComPrivate.h"

static lv_obj_t * appWindow;

static lv_settings menu;

/*�˵��Զ����ַ���������*/
static char FrequencyStr[10] = "2400MHz";
static char AddrStr[5][10];

enum item_index{
    IIDX_SW_Passback,
    IIDX_SW_FHSS,
    IIDX_SW_Handshake,
    IIDX_SW_SignWarn,
    IIDX_Baudrate,
    IIDX_Frequency,
    IIDX_Addr0,
    IIDX_Addr1,
    IIDX_Addr2,
    IIDX_Addr3,
    IIDX_Addr4,
    IIDX_MAX
};

static lv_settings::item_t item_grp[IIDX_MAX] =
{
    {.type = menu.TYPE_SW,     .name = "Passback",    .value = "Data Backhaul"      },
    {.type = menu.TYPE_SW,     .name = "FHSS",        .value = "Frequency agility"  },
    {.type = menu.TYPE_SW,     .name = "Handshake",   .value = "Handshake to slave" },
    {.type = menu.TYPE_SW,     .name = "Signal warn", .value = "Signal low warn",   },
    {.type = menu.TYPE_DDLIST, .name = "Baudrate",    .value = "250Kbps\n1Mbps\n2Mbps", .user_data.ptr = &CTRL.RF_Config->Speed},
    {.type = menu.TYPE_SLIDER, .name = "Frequency",   .value = FrequencyStr,            .user_data.ptr = &CTRL.RF_Config->Freq},
    {.type = menu.TYPE_NUMSET, .name = "Address[0]",     .value = AddrStr[0]},
    {.type = menu.TYPE_NUMSET, .name = "Address[1]",     .value = AddrStr[1]},
    {.type = menu.TYPE_NUMSET, .name = "Address[2]",     .value = AddrStr[2]},
    {.type = menu.TYPE_NUMSET, .name = "Address[3]",     .value = AddrStr[3]},
    {.type = menu.TYPE_NUMSET, .name = "Address[4]",     .value = AddrStr[4]},
};



static void Menu_EventHandler(lv_obj_t * obj, lv_event_t event)
{
    /*Get the caller item*/
    lv_settings::item_t * act_item = (lv_settings::item_t *)lv_event_get_data();
#define IS_ITEM(item_name) (strcmp((item_name), act_item->name) == 0)
    
    if(event == LV_EVENT_VALUE_CHANGED)
    {
        if(IS_ITEM("Baudrate"))
        {
            CTRL.RF_Config->Speed = act_item->state;
            nrf.SetSpeed(CTRL.RF_Config->Speed);
        }
        else if(IS_ITEM("Frequency"))
        {
            CTRL.RF_Config->Freq = act_item->state;
            snprintf(FrequencyStr, sizeof(FrequencyStr), "%04dMHz", CTRL.RF_Config->Freq + 2400);
            nrf.SetFreqency(CTRL.RF_Config->Freq);
        }
        else if(String(act_item->name).startsWith("Address["))
        {
            uint8_t index = act_item->name[8] - '0';
            
            if(index > 4)
                return;
            
            __LimitValue(act_item->state, 0, 0xFF);
            snprintf(AddrStr[index], sizeof(AddrStr[index]), "0x%02x", act_item->state);
            CTRL.RF_Config->Addr[index] = act_item->state;
            nrf.SetAddress(CTRL.RF_Config->Addr);
        }
    }
}

static void Menu_Init()
{
    menu.create(appWindow, Menu_EventHandler);
    
    #define SW_ATTACH_PTR(name) item_grp[IIDX_SW_##name].user_data.ptr=&CTRL.State->name
    
    SW_ATTACH_PTR(Passback);
    SW_ATTACH_PTR(FHSS);
    SW_ATTACH_PTR(Handshake);
    SW_ATTACH_PTR(SignWarn);
    
    menu.add(item_grp, __Sizeof(item_grp));
    
    /*Baudrate*/
    item_grp[IIDX_Baudrate].state = CTRL.RF_Config->Speed;
    lv_obj_t * ddlist = item_grp[IIDX_Baudrate].obj;
    lv_ddlist_set_selected(ddlist, item_grp[IIDX_Baudrate].state);
    //menu.refr(&item_grp[IIDX_Baudrate]);/*�������*/

    /*Frequency slider*/
    lv_obj_t * slider = item_grp[IIDX_Frequency].obj;
    lv_slider_set_range(slider, 0, 125);
    item_grp[IIDX_Frequency].state = nrf.GetFreqency();
    snprintf(FrequencyStr, sizeof(FrequencyStr), "%04dMHz", item_grp[IIDX_Frequency].state + 2400);
    menu.refr(&item_grp[IIDX_Frequency]);
    

    
    /*ADDR*/
    for(int i = 0; i < 5; i++)
    {
        uint8_t addr = nrf.GetAddress(i);
        CTRL.RF_Config->Addr[i] = addr;
        item_grp[IIDX_Addr0 + i].state = addr;
        snprintf(AddrStr[i], sizeof(AddrStr[i]), "0x%02x", addr);
        menu.refr(&item_grp[IIDX_Addr0 + i]);
    }
}

void Menu_AnimOpen(lv_settings * menu, bool open)
{
    lv_obj_t * cont = menu->act_cont;
    lv_coord_t y_target = lv_obj_get_y(cont);
    if(open)
    {
        lv_obj_set_y(cont, y_target + lv_obj_get_height(cont));
    }
    else
    {
        y_target = lv_obj_get_y(cont) + lv_obj_get_height(cont);
    }
    LV_OBJ_ADD_ANIM(cont, y, y_target, LV_ANIM_TIME_DEFAULT);
    Page_Delay(LV_ANIM_TIME_DEFAULT);
}

/**
  * @brief  ҳ���ʼ���¼�
  * @param  ��
  * @retval ��
  */
static void Setup()
{
    /*����ҳ���Ƶ�ǰ̨*/
    lv_obj_move_foreground(appWindow);

    Menu_Init();
    Menu_AnimOpen(&menu, true);
}

/**
  * @brief  ҳ���˳��¼�
  * @param  ��
  * @retval ��
  */
static void Exit()
{
    Menu_AnimOpen(&menu, false);
    menu.del();
    lv_obj_clean(appWindow);
}

/**
  * @brief  ҳ���¼�
  * @param  btn:�����¼��İ���
  * @param  event:�¼����
  * @retval ��
  */
static void Event(void* btn, int event)
{
    if(btn == &btBACK)
    {
        if(event == ButtonEvent::EVENT_ButtonPress)
        {
            if(!menu.back())
            {
                page.PagePop();
            }
        }
    }

    if(btn == &btOK)
    {
        if(event == ButtonEvent::EVENT_ButtonPress || event == ButtonEvent::EVENT_ButtonLongPressRepeat)
        {
            menu.click();
        }
    }

    if(event == ButtonEvent::EVENT_ButtonPress || event == ButtonEvent::EVENT_ButtonLongPressRepeat)
    {
        lv_coord_t dist = (event == ButtonEvent::EVENT_ButtonLongPressRepeat) ? 5 : 1;
        if(btn == &btUP)
        {
            menu.move(-dist);
        }
        if(btn == &btDOWN)
        {
            menu.move(+dist);
        }
        if(btn == &btUPL)
        {
            menu.scroll(-20);
        }
        if( btn == &btDOWNL)
        {
            menu.scroll(+20);
        }
    }
}

/**
  * @brief  ҳ��ע��
  * @param  pageID:Ϊ��ҳ������ID��
  * @retval ��
  */
void PageRegister_RadioCfg(uint8_t pageID)
{
    appWindow = AppWindow_GetCont(pageID);
    page.PageRegister(pageID, Setup, NULL, Exit, Event);
}
