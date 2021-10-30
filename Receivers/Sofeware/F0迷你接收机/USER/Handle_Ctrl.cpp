#include "FileGroup.h"
#include "ComPrivate.h"
#include <ODriveArduino.h>

#define DEAD_ZONE_VAL 40



void Task_Ctrl()
{
       if(!RCX::GetRxConnected())
    { 
    	 digitalWrite(LED_Pin, LOW);
        return;
    }
			       
	  int16_t CH0_Val = map(RCX::GetRxPackChannel(CH_JSL_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, -1000, 1000);
    int16_t CH1_Val = map(RCX::GetRxPackChannel(CH_JSL_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, -1000, 1000);
		int16_t CH2_Val = map(RCX::GetRxPackChannel(CH_JSR_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, -1000, 1000);
		int16_t CH3_Val = map(RCX::GetRxPackChannel(CH_JSR_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, -1000, 1000);
		int16_t CH4_Val = map(RCX::GetRxPackChannel(CH_LMT_L), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, -1000, 1000);
		int16_t CH5_Val = map(RCX::GetRxPackChannel(CH_LMT_R), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, -1000, 1000);
// 地平线60A电调脉宽 1.1-1.9  55-90
//    int16_t CH0_Val = map(RCX::GetRxPackChannel(CH_JSL_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 55, 90);
//    int16_t CH1_Val = map(RCX::GetRxPackChannel(CH_JSL_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 55, 90);
//		int16_t CH2_Val = map(RCX::GetRxPackChannel(CH_JSR_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 55, 90);
//		int16_t CH3_Val = map(RCX::GetRxPackChannel(CH_JSR_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 55, 90);
//		int16_t CH4_Val = map(RCX::GetRxPackChannel(CH_LMT_L), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 55, 90);
//		int16_t CH5_Val = map(RCX::GetRxPackChannel(CH_LMT_R), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 55, 90);

//		//普通舵机 0.5ms - 2.5ms   25 - 125	
//		//odrive  1ms - 2ms
//		int16_t CH0_Val = map(RCX::GetRxPackChannel(CH_JSL_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 50, 100);
//    int16_t CH1_Val = map(RCX::GetRxPackChannel(CH_JSL_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 50, 100);
//		int16_t CH2_Val = map(RCX::GetRxPackChannel(CH_JSR_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 50, 100);
//		int16_t CH3_Val = map(RCX::GetRxPackChannel(CH_JSR_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 50, 100);
//		int16_t CH4_Val = map(RCX::GetRxPackChannel(CH_LMT_L), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 50, 100);
//		int16_t CH5_Val = map(RCX::GetRxPackChannel(CH_LMT_R), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 50, 100);

			if( CH0_Val > 500)
		{ 
			odrive.SetVelocity(0, 1);
			odrive.SetVelocity(1, -1);

		}		
		if( CH0_Val < 40&&CH0_Val > -40)
		{ 
			odrive.SetVelocity(0, 0);
			odrive.SetVelocity(1, 0);

		}		
	if( CH0_Val < -500)
		{ 
			odrive.SetVelocity(0, -1);
			odrive.SetVelocity(1, 1);

		}		
		
}
