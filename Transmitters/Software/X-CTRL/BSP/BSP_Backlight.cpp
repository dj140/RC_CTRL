#include "Basic/FileGroup.h"
#include "GUI/DisplayPrivate.h"
#include "BSP.h"

static void Backlight_AnimCallback(void * obj, int16_t brightness)
{
    Backlight_SetValue(brightness);
}

void Backlight_SetGradual(uint16_t target, uint16_t time)
{
    static lv_anim_t a;
    lv_obj_add_anim(
        NULL, &a,
        (lv_anim_exec_xcb_t)Backlight_AnimCallback,
        Backlight_GetValue(), target,
        time
    );
}

uint16_t Backlight_GetValue()
{
    return timer_get_compare(PIN_MAP[LCD_BLK_Pin].TIMx, PIN_MAP[LCD_BLK_Pin].TimerChannel);
}

void Backlight_SetValue(int16_t val)
{
    __ExecuteOnce(PWM_Init(LCD_BLK_Pin, 1000, 20000));
    __LimitValue(val, 0, 1000);
    analogWrite(LCD_BLK_Pin, val);
}
