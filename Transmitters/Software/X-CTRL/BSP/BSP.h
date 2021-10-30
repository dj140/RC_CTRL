#ifndef __BSP_H
#define __BSP_H

#include "Basic/SysConfig.h"
#include "Basic/CommonMacro.h"
#include "Basic/XC_Type.h"
#include "Arduino.h"

#define DEBUG_FUNC_LOG() Serial.printf("%s (%0.3fms)\r\n", __FUNCTION__, micros()/1000.0f)

/*Backlight*/
uint16_t Backlight_GetValue();
void Backlight_SetValue(int16_t val);
void Backlight_SetGradual(uint16_t target, uint16_t time = 500);

/*Buttons*/
#include "ButtonEvent/ButtonEvent.h"
enum{
    BTN_IDX_UP,
    BTN_IDX_DOWN,
    BTN_IDX_OK,
    BTN_IDX_BACK,
    BTN_IDX_UPL,
    BTN_IDX_DOWNL,
    BTN_IDX_POWER,
    BTN_IDX_MAX
};
extern ButtonEvent  btGrp[BTN_IDX_MAX];
#define btUP       (btGrp[BTN_IDX_UP])
#define btDOWN     (btGrp[BTN_IDX_DOWN])
#define btOK       (btGrp[BTN_IDX_OK])
#define btBACK     (btGrp[BTN_IDX_BACK])
#define btUPL      (btGrp[BTN_IDX_UPL])
#define btDOWNL    (btGrp[BTN_IDX_DOWNL])
#define btPOWER    (btGrp[BTN_IDX_POWER])
void Button_Init();
void Button_Update();

/*Switch*/
#include "SwitchEvent/SwitchEvent.h"
enum{
    SW_IDX_E,
    SW_IDX_F,
    SW_IDX_G,
    SW_IDX_H,
    SW_IDX_MAX
};
extern SwitchEvent swGrp[SW_IDX_MAX];
#define swE swGrp[SW_IDX_E]
#define swF swGrp[SW_IDX_F]
#define swG swGrp[SW_IDX_G]
#define swH swGrp[SW_IDX_H]
void Switch_Init();
void Switch_Update(uint16_t swVal);


/*Audio*/
namespace MC_Type {
typedef enum {
    MC_StartUp,
    MC_Error,
    MC_Connect,
    MC_Disconnect,
    MC_UnstableConnect,
    MC_BattChargeStart,
    MC_BattChanargeEnd,
    MC_DeviceInsert,
    MC_DevicePullout,
    MC_NoOperationWarning,
    MC_Astronomia,
    MC_MAX
}MusicCode_ID_Type;
}
void Audio_Init();
void Audio_Update();
void Audio_PlayMusic(uint8_t music);
void Audio_Tone(uint32_t freq, uint32_t time);

/*Joystick*/
void Joystick_Init();
void Joystick_Update();
void Joystick_SetDefault();
void Joystick_SetCurve(XC_Joystick_TypeDef* js, float startK, float endK);
void Joystick_GetCurve(XC_Joystick_TypeDef* js, int16_t* points, uint32_t size);

/*IMU*/
void IMU_Init();
void IMU_Update();

/*EEPROM*/
#define EEPROM_REG_VALUE(data) EEPROM_Register(&(data), sizeof(data))
uint8_t EEPROM_Init();
bool EEPROM_Register(void *pdata, uint16_t size);
bool EEPROM_ReadAll();
bool EEPROM_SaveAll();

/*I2C*/
void I2C_Scan(bool startScan = true);
void I2C_SetLock(bool lock);
bool I2C_GetLocked();

/*Power*/
void Power_Init();
void Power_GetInfo(float* battCurrent,float* battVoltage,float* battVoltageOc);
float Power_GetBattUsage();
void Power_Update();
void Power_Shutdown();
void Power_SetLedState(bool state);
void Power_SetLedValue(uint16_t val);

/*Bluetooth*/
void Bluetooth_Init();
void Bluetooth_UpdatePowerState();

/*MotorLRA*/
void MotorLRA_Init();
void MotorLRA_Update();
void MotorLRA_SetEnable(bool en);
void MotorLRA_Vibrate(float strength, uint32_t time);
void MotorLRA_WriteData(int16_t data);
void MotorLRA_Tone(float freq);
void MotorLRA_Tone(float freq, uint32_t time);
void MotorLRA_ToneSetVolume(uint16_t volume);
uint16_t MotorLRA_ToneGetVolume();
void MotorLRA_NoTone();

/*MotorERM*/
void MotorERM_Init();
void MotorERM_SetEnable(bool en);
void MotorERM_SetValue(uint16_t value);

#endif
