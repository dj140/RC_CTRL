#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "GUI/lv_settings.h"
#include "BSP/IMU_Private.h"

static lv_obj_t * appWindow;

static lv_settings menu;

static char AxisLimitStr[3][20];

enum item_index{
    IIDX_SW_IMU,
    IIDX_BTN_Calibrate,
    IIDX_Pitch,
    IIDX_Roll,
    IIDX_Yaw,
    IIDX_MAX
};

static lv_settings::item_t item_grp[IIDX_MAX] =
{
    {.type = menu.TYPE_SW,     .name = "Gyroscope",    .value = "Use gyroscope"},
    {.type = menu.TYPE_BTN,    .name = "Calibrate",    .value = "Start"},
    {.type = menu.TYPE_NUMSET, .name = "Pitch/Limit",  .value = AxisLimitStr[0],    .user_data.ptr = &IMU_Axis.Pitch.Limit},
    {.type = menu.TYPE_NUMSET, .name = "Roll/Limit",   .value = AxisLimitStr[1],    .user_data.ptr = &IMU_Axis.Roll.Limit},
    {.type = menu.TYPE_NUMSET, .name = "Yaw/Limit",    .value = AxisLimitStr[2],    .user_data.ptr = &IMU_Axis.Yaw.Limit},
};

static lv_task_t * taskIMU_Update;

static void Task_IMU_Update(lv_task_t * task)
{
    snprintf(AxisLimitStr[0], sizeof(AxisLimitStr[0]), "%0.1f/+-%d"LV_SYMBOL_DEGREE_SIGN, IMU_Axis.Pitch.Angle, IMU_Axis.Pitch.Limit);
    menu.refr(&item_grp[IIDX_Pitch]);
    
    snprintf(AxisLimitStr[1], sizeof(AxisLimitStr[1]), "%0.1f/+-%d"LV_SYMBOL_DEGREE_SIGN, IMU_Axis.Roll.Angle, IMU_Axis.Roll.Limit);
    menu.refr(&item_grp[IIDX_Roll]);
    
    snprintf(AxisLimitStr[2], sizeof(AxisLimitStr[2]), "%0.1f/+-%d"LV_SYMBOL_DEGREE_SIGN, IMU_Axis.Yaw.Angle, IMU_Axis.Yaw.Limit);
    menu.refr(&item_grp[IIDX_Yaw]);
}

static void Menu_EventHandler(lv_obj_t * obj, lv_event_t event)
{
    /*Get the caller item*/
    lv_settings::item_t * act_item = (lv_settings::item_t *)lv_event_get_data();
#define IS_ITEM(item_name) (strcmp((item_name), act_item->name) == 0)
    
    if(event == LV_EVENT_VALUE_CHANGED)
    {
        String name = String(act_item->name);
        if(name.endsWith("Limit"))
        {
            if(name.startsWith("Yaw"))
            {
                __LimitValue(act_item->state, 1, 180);
            }
            else
            {
                __LimitValue(act_item->state, 1, 90);
            }
            *(int16_t*)act_item->user_data.ptr = act_item->state;
        }
    }
    else if(event == LV_EVENT_CLICKED)
    {
        if(IS_ITEM("Calibrate"))
        {
            IMU_CalibrateStart();
        }
    }
}

static void Menu_Init()
{
    menu.create(appWindow, Menu_EventHandler);
    
#define SW_ATTACH_PTR(name) item_grp[IIDX_SW_##name].user_data.ptr=&CTRL.State->name
    
    SW_ATTACH_PTR(IMU);
    
    for(int i = 0; i < __Sizeof(item_grp); i++)
    {
        lv_settings::item_t * item = &item_grp[i];

        if(i >= IIDX_Pitch && i <= IIDX_Yaw)
        {
            item_grp[i].state = *(int16_t*)item_grp[i].user_data.ptr;
        }
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
    Menu_AnimOpen(&menu, true);
    
    taskIMU_Update = lv_task_create(Task_IMU_Update, 100, LV_TASK_PRIO_MID, 0);
}

/**
  * @brief  ҳ���˳��¼�
  * @param  ��
  * @retval ��
  */
static void Exit()
{
    Menu_AnimOpen(&menu, false);
    lv_task_del(taskIMU_Update);
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
void PageRegister_GyroscopeCfg(uint8_t pageID)
{
    appWindow = AppWindow_GetCont(pageID);
    page.PageRegister(pageID, Setup, NULL, Exit, Event);
}
