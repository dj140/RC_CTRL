#include "FileGroup.h"
#include "ComPrivate.h"

#define DEAD_ZONE_VAL 5


void Task_Ctrl()
{
    if(!RCX::GetRxConnected())
    {
        analogWrite(CH0_Pin, 0);
			  analogWrite(CH1_Pin, 0);
        analogWrite(CH2_Pin, 0);
        analogWrite(CH3_Pin, 0);
        analogWrite(CH4_Pin, 0);
        analogWrite(CH5_Pin, 0);
        analogWrite(CH6_Pin, 0);
        analogWrite(CH7_Pin, 0);
        return;
    }
    
    int16_t CH0_Val = map(RCX::GetRxPackChannel(CH_JSL_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
    int16_t CH1_Val = map(RCX::GetRxPackChannel(CH_JSL_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
		int16_t CH2_Val = map(RCX::GetRxPackChannel(CH_JSR_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
		int16_t CH3_Val = map(RCX::GetRxPackChannel(CH_JSR_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
		int16_t CH4_Val = map(RCX::GetRxPackChannel(CH_LMT_L), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
		int16_t CH5_Val = map(RCX::GetRxPackChannel(CH_LMT_R), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
		int16_t CH6_Val = map(RCX::GetRxPackChannel(CH_RMT_L), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
		int16_t CH7_Val = map(RCX::GetRxPackChannel(CH_RMT_R), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
   
		analogWrite(CH0_Pin, CH0_Val);
    analogWrite(CH1_Pin, CH1_Val);
    analogWrite(CH2_Pin, CH2_Val);
    analogWrite(CH3_Pin, CH3_Val);
    analogWrite(CH4_Pin, CH4_Val);        
		analogWrite(CH5_Pin, CH5_Val);        
		analogWrite(CH6_Pin, CH6_Val);       
		analogWrite(CH7_Pin, CH7_Val);
}
