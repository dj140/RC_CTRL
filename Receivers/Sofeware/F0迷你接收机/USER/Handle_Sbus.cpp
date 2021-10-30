#include "FileGroup.h"
#include "ComPrivate.h"

#define RC_CHANNEL_MIN -1000 	//每个通道的PWM最小值
#define RC_CHANNEL_MAX 1000 	//每个通道的PWM最大值
#define SBUS_MIN_OFFSET 173 	//SBUS协议的最小值
#define SBUS_MID_OFFSET 992 	//SBUS协议的中间值
#define SBUS_MAX_OFFSET 1811 	//SBUS协议的最大值
#define SBUS_CHANNEL_NUMBER 16 	//SBUS通道数，16个模拟通道，2个数字通道
#define SBUS_PACKET_LENGTH 25	// SBUS数据包的字节长度
#define SBUS_FRAME_HEADER 0x0f		// SBUS数据头，开始字节
#define SBUS_FRAME_FOOTER 0x00		// SBUS数据尾，结束字节
#define SBUS_FRAME_FOOTER_V2 0x04	// SBUS数据尾，结束字节2
#define SBUS_STATE_FAILSAFE 0x08	// 激活故障安全标志
#define SBUS_STATE_SIGNALLOSS 0x04 	// 丢失信号标志
#define SBUS_UPDATE_RATE 10 //SBUS输出更新时间ms

uint16_t PWMvalue[SBUS_CHANNEL_NUMBER];// 控制PWM占空比
uint8_t sbusPacket[SBUS_PACKET_LENGTH];// 25个字节的SBUS数据包
uint8_t signalLoss = 0;  // 1表示丢失信号
uint16_t i=0,startIndex=0;

uint8_t chPacket[32];

void sbusPreparePacket(uint8_t packet[], uint16_t channels[], uint8_t isSignalLoss, uint8_t isFailsafe)
{
	   
    static int output[SBUS_CHANNEL_NUMBER] = {0};//这里一定要16个元素的数组，不然其他通道会干扰
    /*将channel值1000-2000映射到SBUS协议的173-1811*/
    for (uint8_t i = 0; i < SBUS_CHANNEL_NUMBER; i++) {
        output[i] = (int)map(channels[i], RC_CHANNEL_MIN, RC_CHANNEL_MAX, SBUS_MIN_OFFSET, SBUS_MAX_OFFSET);
    }
    
    uint8_t stateByte = 0x00;
    if (isSignalLoss) {
        stateByte |= SBUS_STATE_SIGNALLOSS; // 丢失信号标志
    }
    if (isFailsafe) {
        stateByte |= SBUS_STATE_FAILSAFE;   // 激活故障安全标志
    }
    packet[0] = SBUS_FRAME_HEADER; //SBUS头，0x0F
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
    packet[23] = stateByte;         // 标志位0x00
    packet[24] = SBUS_FRAME_FOOTER; // SBUS结束字节0x00
}

void Task_Sbus()
{ 
	   for (uint8_t i = 0; i < 8; i++) {
	     PWMvalue[i] = RCX::GetRxPackChannel(i);
			}
		 	for (uint8_t i=8; i<16; i++) 
			{
				PWMvalue[i] = 1500;//未用到的通道全部置中
			}
     sbusPreparePacket(sbusPacket, PWMvalue, signalLoss, 0); //chNum通道数值转换为SBUS数据包
			
			for(uint8_t i = 0; i<SBUS_PACKET_LENGTH; i++)
			{
				Serial.write(sbusPacket[i]);

			}
}
