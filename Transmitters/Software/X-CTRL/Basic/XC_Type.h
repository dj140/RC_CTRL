#ifndef __XC_TYPE_H
#define __XC_TYPE_H

#include "stdint.h"
#include "Communication/RCX/RCX.h"

#pragma pack(1)

/*У׼*/
typedef struct
{
    int16_t Val;

    int16_t AdcVal;
    int16_t Min;
    int16_t Mid;
    int16_t Max;
    bool Reverse;
    struct
    {
        double Start;
        double End;
    } Curve;
} XC_Channel_TypeDef;

/*ҡ��*/
typedef struct
{
    XC_Channel_TypeDef X;
    XC_Channel_TypeDef Y;
} XC_Joystick_TypeDef;

/*����ʹ��*/
typedef struct
{
    bool Passback;
    bool Handshake;
    bool FHSS;
    bool IdleWarn;
    bool SignWarn;
    bool JostickFilter;
    bool Sound;
    bool LRA_Vibrate;
    bool ERM_Vibrate;
    bool IMU;
    bool Bluetooth;
    bool CurrentDisp;
}XC_State_TypeDef;

/*��Ƶ����*/
typedef struct
{
    uint8_t Speed;
    uint8_t Freq;
    uint8_t Addr[5];
}XC_RF_Config_TypeDef;

/*ͨ������*/
typedef struct
{
    bool Reverse[RCX_CHANNEL_NUM];
    uint8_t AttachMap[RCX_CHANNEL_NUM];
}XC_CH_Config_TypeDef;

/*ң����״̬*/
typedef struct
{
    /*ҡ��*/
    XC_Joystick_TypeDef JS_L;
    XC_Joystick_TypeDef JS_R;

    /*����*/
    union
    {
        struct
        {
            uint8_t BT_UP : 1;
            uint8_t BT_DOWN : 1;
            uint8_t BT_BACK : 1;
            uint8_t BT_OK : 1;
            uint8_t BT_L1 : 1;
            uint8_t BT_L2 : 1;
            uint8_t BT_R1 : 1;
            uint8_t BT_R2 : 1;
        } Bit;
        uint8_t Value;
    } Key;

    /*����ʽ����*/
    int16_t Switch[4];

    /*ͨ��������Ϣ*/
    XC_CH_Config_TypeDef* CH_Config;

    /*���ܿ���*/
    XC_State_TypeDef* State;
    
    /*��Ƶ����*/
    XC_RF_Config_TypeDef* RF_Config;
    
    uint8_t ModelIndex;

    /*�����Ϣ*/
    struct
    {
        float Usage;
        float Voltage;
    } Battery;
} X_CTRL_TypeDef;

#pragma pack()

#endif
