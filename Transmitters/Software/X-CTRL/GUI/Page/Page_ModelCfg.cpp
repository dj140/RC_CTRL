#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "GUI/lv_settings.h"
#include "Model/XC_Model.h"
#include "Communication/ComPrivate.h"

static lv_obj_t * appWindow;

static lv_settings menu;

enum item_index{
    IIDX_ModelList,
    IIDX_ModelDel,
    IIDX_MAX
};

static char ModelListBuf[XC_MODEL_NAME_MAX * XC_MODEL_NUM];

static lv_settings::item_t item_grp[IIDX_MAX] =
{
    {.type = menu.TYPE_DDLIST,  .name = "Model",       .value = ModelListBuf},
    {.type = menu.TYPE_BTN,     .name = "Double click",.value = "Delete"},
};

static void ModelList_Update()
{
    String tempStr = "";
    ModelListBuf[0] = '\0';
    bool first = true;
    for(int i = 0; i < XC_MODEL_NUM; i++)
    {
        const char* name = XC_Model[i].Name;
        if(name[0] != '\0')
        {
            if(first)
            {
                tempStr += String(name);
                first = false;
            }
            else
            {
                tempStr += "\n";
                tempStr += String(name);
            }
        }
    }
    tempStr.toCharArray(ModelListBuf, sizeof(ModelListBuf));
}

static void Menu_EventHandler(lv_obj_t * obj, lv_event_t event)
{
    /*Get the caller item*/
    lv_settings::item_t * act_item = (lv_settings::item_t *)lv_event_get_data();
#define IS_ITEM(item_name) (strcmp((item_name), act_item->name) == 0)
    
    if(event == LV_EVENT_VALUE_CHANGED)
    {
        char modelName[16];
        lv_ddlist_get_selected_str(act_item->obj, modelName, sizeof(modelName));
        int16_t index = Model_GetNameIndex(modelName);
        if(index >= 0)
        {
            Model_Update(index);
        }
    }
    else if(event == LV_EVENT_CLICKED)
    {
        static uint32_t lastClickTime = 0;
        
        if(millis() - lastClickTime > 300)
        {
            lastClickTime = millis();
            return;
        }
        
        const char* name = Model_GetCurrentName();
        if(name != NULL && name[0] != '\0')
        {
            Model_Delete(name);
            ModelList_Update();
            lv_ddlist_set_options(item_grp[IIDX_ModelList].obj, ModelListBuf);
        }
    }
}

static void Menu_Init()
{
    ModelList_Update();
    
    menu.create(appWindow, Menu_EventHandler);
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
    Com_ChannelInit();
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
void PageRegister_ModelCfg(uint8_t pageID)
{
    appWindow = AppWindow_GetCont(pageID);
    page.PageRegister(pageID, Setup, NULL, Exit, Event);
}
