#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "GUI/lv_settings.h"
#include "Communication/ComPrivate.h"

static lv_obj_t * appWindow;

static lv_settings menu;

enum item_index{
    IIDX_SW_JostickFilter,
    IIDX_LeftCurve,
    IIDX_RightCurve,
    IIDX_Calibrate,
    IIDX_MAX
};

static lv_settings::item_t item_grp[IIDX_MAX] =
{
    {.type = menu.TYPE_SW,     .name = "ADC filter",      .value = "PT1 Lowpass filter"},
    {.type = menu.TYPE_BTN,    .name = "Left curve",      .value = "Config"},
    {.type = menu.TYPE_BTN,    .name = "Right curve",     .value = "Config"},
    {.type = menu.TYPE_BTN,    .name = "Calibration",     .value = "Start"},
};

static void Menu_EventHandler(lv_obj_t * obj, lv_event_t event)
{
    /*Get the caller item*/
    lv_settings::item_t * act_item = (lv_settings::item_t *)lv_event_get_data();
#define IS_ITEM(item_name) (strcmp((item_name), act_item->name) == 0)
    
    if(event == LV_EVENT_VALUE_CHANGED)
    {
       
    }
    else if(event == LV_EVENT_CLICKED)
    {
        extern void Joystick_CurveCfg(XC_Joystick_TypeDef* js);
        if(IS_ITEM("Left curve"))
        {
            Joystick_CurveCfg(&CTRL.JS_L);
            page.PagePush(PAGE_JoystickCurveCfg);
        }
        else if(IS_ITEM("Right curve"))
        {
            Joystick_CurveCfg(&CTRL.JS_R);
            page.PagePush(PAGE_JoystickCurveCfg);
        }
    }
}

static void Menu_Init()
{
    menu.create(appWindow, Menu_EventHandler);
    
#define SW_ATTACH_PTR(name) item_grp[IIDX_SW_##name].user_data.ptr=&CTRL.State->name
    
    SW_ATTACH_PTR(JostickFilter);
    
    for(int i = 0; i < __Sizeof(item_grp); i++)
    {
        lv_settings::item_t * item = &item_grp[i];

        menu.add(item);
    }
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
    Menu_AnimOpen(&menu, true);;
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
        if(event == ButtonEvent::EVENT_ButtonPress)
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
void PageRegister_JoystickCfg(uint8_t pageID)
{
    appWindow = AppWindow_GetCont(pageID);
    page.PageRegister(pageID, Setup, NULL, Exit, Event);
}
