#include "FileGroup.h"
#include "ComPrivate.h"

#define RC_CHANNEL_MIN -1000 	//ÿ��ͨ����PWM��Сֵ
#define RC_CHANNEL_MAX 1000 	//ÿ��ͨ����PWM���ֵ
#define SBUS_MIN_OFFSET 173 	//SBUSЭ�����Сֵ
#define SBUS_MID_OFFSET 992 	//SBUSЭ����м�ֵ
#define SBUS_MAX_OFFSET 1811 	//SBUSЭ������ֵ
#define SBUS_CHANNEL_NUMBER 16 	//SBUSͨ������16��ģ��ͨ����2������ͨ��
#define SBUS_PACKET_LENGTH 25	// SBUS���ݰ����ֽڳ���
#define SBUS_FRAME_HEADER 0x0f		// SBUS����ͷ����ʼ�ֽ�
#define SBUS_FRAME_FOOTER 0x00		// SBUS����β�������ֽ�
#define SBUS_FRAME_FOOTER_V2 0x04	// SBUS����β�������ֽ�2
#define SBUS_STATE_FAILSAFE 0x08	// ������ϰ�ȫ��־
#define SBUS_STATE_SIGNALLOSS 0x04 	// ��ʧ�źű�־
#define SBUS_UPDATE_RATE 10 //SBUS�������ʱ��ms

uint16_t PWMvalue[SBUS_CHANNEL_NUMBER];// ����PWMռ�ձ�
uint8_t sbusPacket[SBUS_PACKET_LENGTH];// 25���ֽڵ�SBUS���ݰ�
uint8_t signalLoss = 0;  // 1��ʾ��ʧ�ź�
uint16_t i=0,startIndex=0;

uint8_t chPacket[32];

void sbusPreparePacket(uint8_t packet[], uint16_t channels[], uint8_t isSignalLoss, uint8_t isFailsafe)
{
	   
    static int output[SBUS_CHANNEL_NUMBER] = {0};//����һ��Ҫ16��Ԫ�ص����飬��Ȼ����ͨ�������
    /*��channelֵ1000-2000ӳ�䵽SBUSЭ���173-1811*/
    for (uint8_t i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
        output[i] = (int)map(channels[i], RC_CHANNEL_MIN, RC_CHANNEL_MAX, SBUS_MIN_OFFSET, SBUS_MAX_OFFSET);
    }
    
    uint8_t stateByte = 0x00;
    if (isSignalLoss) {
        stateByte |= SBUS_STATE_SIGNALLOSS; // ��ʧ�źű�־
    }
    if (isFailsafe) {
        stateByte |= SBUS_STATE_FAILSAFE;   // ������ϰ�ȫ��־
    }
    packet[0] = SBUS_FRAME_HEADER; //SBUSͷ��0x0F
    packet[1] = (uint8_t) (output[0] & 0x07FF);
    packet[2] = (uint8_t) ((output[0] & 0x07FF)>>8 | (output[1] & 0x07FF)<<3);
    packet[3] = (uint8_t) ((output[1] & 0x07FF)>>5 | (output[2] & 0x07FF)<<6);
    packet[4] = (uint8_t) ((output[2] & 0x07FF)>>2);
    packet[5] = (uint8_t) ((output[2] & 0x07FF)>>10 | (output[3] & 0x07FF)<<1);
    packet[6] = (uint8_t) ((output[3] & 0x07FF)>>7 | (output[4] & 0x07FF)<<4);
    packet[7] = (uint8_t) ((output[4] & 0x07FF)>>4 | (output[5] & 0x07FF)<<7);
    packet[8] = (uint8_t) ((output[5] & 0x07FF)>>1);
    packet[9] = (uint8_t) ((output[5] & 0x07FF)>>9 | (output[6] & 0x07FF)<<2);
    packet[10] = (uint8_t) ((output[6] & 0x07FF)>>6 | (output[7] & 0x07FF)<<5);
    packet[11] = (uint8_t) ((output[7] & 0x07FF)>>3);
    packet[12] = (uint8_t) ((output[8] & 0x07FF));
    packet[13] = (uint8_t) ((output[8] & 0x07FF)>>8 | (output[9] & 0x07FF)<<3);
    packet[14] = (uint8_t) ((output[9] & 0x07FF)>>5 | (output[10] & 0x07FF)<<6);  
    packet[15] = (uint8_t) ((output[10] & 0x07FF)>>2);
    packet[16] = (uint8_t) ((output[10] & 0x07FF)>>10 | (output[11] & 0x07FF)<<1);
    packet[17] = (uint8_t) ((output[11] & 0x07FF)>>7 | (output[12] & 0x07FF)<<4);
    packet[18] = (uint8_t) ((output[12] & 0x07FF)>>4 | (output[13] & 0x07FF)<<7);
    packet[19] = (uint8_t) ((output[13] & 0x07FF)>>1);
    packet[20] = (uint8_t) ((output[13] & 0x07FF)>>9 | (output[14] & 0x07FF)<<2);
    packet[21] = (uint8_t) ((output[14] & 0x07FF)>>6 | (output[15] & 0x07FF)<<5);
    packet[22] = (uint8_t) ((output[15] & 0x07FF)>>3);
    packet[23] = stateByte;         // ��־λ0x00
    packet[24] = SBUS_FRAME_FOOTER; // SBUS�����ֽ�0x00
}

void Task_Sbus()
{ 
	   for (uint8_t i = 0; i < 8; i++) {
	     PWMvalue[i] = RCX::GetRxPackChannel(i);
			}
		 	for (uint8_t i=8; i<16; i++) 
			{
				PWMvalue[i] = 1500;//δ�õ���ͨ��ȫ������
			}
     sbusPreparePacket(sbusPacket, PWMvalue, signalLoss, 0); //chNumͨ����ֵת��ΪSBUS���ݰ�
			
			for(uint8_t i = 0; i<SBUS_PACKET_LENGTH; i++)
			{
				Serial.write(sbusPacket[i]);

			}
}
