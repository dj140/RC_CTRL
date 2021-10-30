#include "Basic/FileGroup.h"
#include "MusicPlayer/MusicPlayer.h"

using namespace MusicPlayer_Type;

/*����Ƶ�ʶ�Ӧ��*/
typedef enum
{
    L1 = 262,
    L1h = 277,
    L2 = 294,
    L2h = 311,
    L3 = 330,
    L4 = 349,
    L4h = 370,
    L5 = 392,
    L5h = 415,
    L6 = 440,
    L6h = 466,
    L7 = 494,
    M1 = 523,
    M1h = 554,
    M2 = 587,
    M2h = 622,
    M3 = 659,
    M4 = 698,
    M4h = 740,
    M5 = 784,
    M5h = 831,
    M6 = 880,
    M6h = 932,
    M7 = 988,
    H1 = 1046,
    H1h = 1109,
    H2 = 1175,
    H2h = 1245,
    H3 = 1318,
    H4 = 1397,
    H4h = 1480,
    H5 = 1568,
    H5h = 1661,
    H6 = 1760,
    H6h = 1865,
    H7 = 1976,
} Tone_TypeDef;

static void MusicPlayer_Callback(uint32_t freq, uint16_t volume)
{
//    tone(Audio_Pin, freq);
    MotorLRA_Tone(freq);
}

/*ʵ�������ֲ�����*/
static MusicPlayer player(MusicPlayer_Callback);

#define ASTR_T_TIME 180
#define ASTR_S_TIME 20
static const MusicCode_t MC_Astronomia[] = 
{
    /*1-1*/
    {M4, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M4, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M4, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M4, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M6, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M6, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M6, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M6, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    
    /*1-2*/
    {M5, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M5, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M5, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {M5, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H1, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H1, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H1, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H1, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    
    /*1-3*/
    {H2, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H2, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H2, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H2, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H2, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H2, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H2, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    {H2, ASTR_T_TIME},
    {0, ASTR_S_TIME},
    
    /*1-4*/
    {M5, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    {M1, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {M6, ASTR_T_TIME},
    
    /*2-1*/
    {M5, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    
    /*2-2*/
    {M5, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    
    /*2-3*/
    {H3, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    {H3, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    
    /*2-4*/
    {H3, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    {H3, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {M6, ASTR_T_TIME},
    
    /*3-1*/
    {M5, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    
    /*3-2*/
    {M5, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    {M3, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    
    /*3-3*/
    {H3, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    {H3, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {0, ASTR_T_TIME},
    {M2, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    
    /*3-4*/
    {H3, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    {H3, ASTR_T_TIME},
    {H4, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    {M4, ASTR_T_TIME},
    
    /*4-1*/
    {M6, ASTR_T_TIME},
    {M6, ASTR_T_TIME},
    {M6, ASTR_T_TIME},
    {M6, ASTR_T_TIME},
    {M5, ASTR_T_TIME},
    {M5, ASTR_T_TIME},
    {M5, ASTR_T_TIME},
    {M5, ASTR_T_TIME},
    
    /*4-2*/
    {H1, ASTR_T_TIME},
    {H1, ASTR_T_TIME},
    {H1, ASTR_T_TIME},
    {H1, ASTR_T_TIME},
    {H2, ASTR_T_TIME},
    {H2, ASTR_T_TIME},
    {H2, ASTR_T_TIME},
    {H2, ASTR_T_TIME},
    
    /*4-3*/
    {H2, ASTR_T_TIME},
    {H2, ASTR_T_TIME},
    {H2, ASTR_T_TIME},
    {H2, ASTR_T_TIME},
};

/*������*/
static const MusicCode_t MC_StartUp[] =
{
    {M1, 80, 100},
    {M6, 80, 100},
    {M3, 80, 100},
};

/*������ʾ��*/
static const MusicCode_t MC_Error[] =
{
    {100, 80, 100},
    {0,   80, 100},
    {100, 80, 100},
};

/*���ӳɹ���*/
static const MusicCode_t MC_Connect[] =
{
    {H1, 80, 100},
    {H2, 80, 100},
    {H3, 80, 100},
};

/*�Ͽ�������*/
static const MusicCode_t MC_Disconnect[] =
{
    {H3, 80, 100},
    {H2, 80, 100},
    {H1, 80, 100},
};

/*�źŲ��ȶ���ʾ��*/
static const MusicCode_t MC_UnstableConnect[] =
{
    {H1, 80, 100},
    {0, 80, 100},
    {H1, 80, 100},
};

/*���������ʾ��*/
static const MusicCode_t MC_BattChargeStart[] =
{
    {L1, 80, 100},
    {L3, 80, 100},
};

/*���ر���ʾ��*/
static const MusicCode_t MC_BattChargeEnd[] =
{
    {L3, 80, 100},
    {L1, 80, 100},
};

/*�豸������ʾ��*/
static const MusicCode_t MC_DeviceInsert[] =
{
    /*C4,A3,F3,F4*/
    {M1, 180, 100},
    {L6, 80, 100},
    {L4, 80, 100},
    {M4, 160, 100},
};

/*�豸�γ���ʾ��*/
static const MusicCode_t MC_DevicePullout[] =
{
    /*A4,F4,E4*/
    {L6, 80, 100},
    {L4, 80, 100},
    {L3, 80, 100},
};

/*�޲�����ʾ��*/
static const MusicCode_t MC_NoOperationWarning[] = {
    {4000, 40, 100},
    {0, 80, 100},
    {4000, 40, 100},
    {0, 80, 100},
    {4000, 40, 100},
};

/*�б��������Ͷ���*/
typedef struct
{
    const MusicCode_t *mc;
    uint16_t length;
} MC_List_t;

#define PLAY_MUSIC(mc) player.Play(mc,__Sizeof(mc))
#define ADD_MUSIC(mc) {mc,__Sizeof(mc)}

/*��ʾ����ַ�����б�*/
static const MC_List_t MC_List[MC_Type::MC_MAX] =
{
    ADD_MUSIC(MC_StartUp),
    ADD_MUSIC(MC_Error),
    ADD_MUSIC(MC_Connect),
    ADD_MUSIC(MC_Disconnect),
    ADD_MUSIC(MC_UnstableConnect),
    ADD_MUSIC(MC_BattChargeStart),
    ADD_MUSIC(MC_BattChargeEnd),
    ADD_MUSIC(MC_DeviceInsert),
    ADD_MUSIC(MC_DevicePullout),
    ADD_MUSIC(MC_NoOperationWarning),
    ADD_MUSIC(MC_Astronomia)
};

/**
  * @brief  ��ʼ��������
  * @param  ��
  * @retval ��
  */
void Audio_Init()
{
    DEBUG_FUNC_LOG();
    MotorLRA_ToneSetVolume(1000);
}

/**
  * @brief  ���ֲ�������
  * @param  ��
  * @retval ��
  */
void Audio_Update()
{
    player.Running(millis());
}

/**
  * @brief  ���ֲ���
  * @param  music:���ֱ��
  * @retval ��
  */
void Audio_PlayMusic(uint8_t music)
{
    if(!CTRL.State->Sound) //�Ƿ�ʹ�ܷ�����
        return;

    if(music >= MC_Type::MC_MAX) //��������Ƿ�Խ��
        return;

    /*��������������*/
    player.Play(MC_List[music].mc, MC_List[music].length);
}

/**
  * @brief  �����������ָ��Ƶ�ʺͳ���ʱ��ķ����ź�(������ʽ)
  * @param  freq:Ƶ��(Hz)
  * @param  time:����ʱ��(ms)
  * @retval ��
  */
void Audio_Tone(uint32_t freq, uint32_t time)
{
    if(!CTRL.State->Sound)
        return;
    
    MotorLRA_Tone(freq, time);
}
