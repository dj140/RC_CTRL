#include "FileGroup.h"
#include "ComPrivate.h"

void Task_InfoLED()
{
	
    if (RCX::GetRxConnected())
    {
        digitalWrite_HIGH(LED_Pin);
    }
    else if (RCX::GetRxPackErrorCode())
    {
        mtm.TaskSetIntervalTime(TP_InfoLED, 100);
        togglePin(LED_Pin);
			  pinMode(CH0_Pin, INPUT_PULLDOWN);
			    pinMode(CH1_Pin, INPUT_PULLDOWN);
			    pinMode(CH2_Pin, INPUT_PULLDOWN);
			    pinMode(CH3_Pin, INPUT_PULLDOWN);
			    pinMode(CH4_Pin, INPUT_PULLDOWN);
			    pinMode(CH5_Pin, INPUT_PULLDOWN);
			
			  analogWrite(CH0_Pin, 0);
			  analogWrite(CH1_Pin, 0);
        analogWrite(CH2_Pin, 0);
        analogWrite(CH3_Pin, 0);
        analogWrite(CH4_Pin, 0);
        analogWrite(CH5_Pin, 0);
    
    }
    else
    {
        mtm.TaskSetIntervalTime(TP_InfoLED, 200);
        togglePin(LED_Pin);
    }
}
