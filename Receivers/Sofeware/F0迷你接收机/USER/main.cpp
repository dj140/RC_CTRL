#include "FileGroup.h"
#include "ComPrivate.h"
#include <ODriveArduino.h>

MillisTaskManager mtm(TP_MAX, true);
HardwareSerial& odrive_serial = Serial;
ODriveArduino odrive(odrive_serial);

static void setup()
{
    pinMode(LED_Pin, OUTPUT);
    __LoopExecute((togglePin(LED_Pin), delay(80)), 10);
    
    pinMode(BAT_DET_Pin, INPUT_ANALOG);
    //ADC_DMA_Init();
    randomSeed(analogRead(BAT_DET_Pin));
    
//    PWM_Init(CH0_Pin, 1000, 50);
//    PWM_Init(CH1_Pin, 1000, 50);
//    PWM_Init(CH2_Pin, 1000, 50);
//    PWM_Init(CH3_Pin, 1000, 50);
//    PWM_Init(CH4_Pin, 1000, 50);
//    PWM_Init(CH5_Pin, 1000, 50);


    Com_Init();
    Serial.begin(115200);
	  //odrive_serial.begin(115200);

    mtm.TaskRegister(TP_ComHandler, Task_ComHandler, 10);
		//mtm.TaskRegister(TP_Sbus, Task_Sbus, 10);
    mtm.TaskRegister(TP_Ctrl, Task_Ctrl, 20);
    mtm.TaskRegister(TP_InfoLED, Task_InfoLED, 500);
    mtm.TaskRegister(TP_IWDG_Feed, IWDG_ReloadCounter, 500);
    mtm.TaskRegister(TP_ComPassback, Task_ComPassback, 1000);

    while (!RCX::Handshake::Process())
    {
//			    pinMode(CH0_Pin, INPUT_PULLDOWN);
//			    pinMode(CH1_Pin, INPUT_PULLDOWN);
//			    pinMode(CH2_Pin, INPUT_PULLDOWN);
//			    pinMode(CH3_Pin, INPUT_PULLDOWN);
//			    pinMode(CH4_Pin, INPUT_PULLDOWN);
//			    pinMode(CH5_Pin, INPUT_PULLDOWN);
			
   

//			  analogWrite(CH0_Pin, 0);
//			  analogWrite(CH1_Pin, 0);
//        analogWrite(CH2_Pin, 0);
//        analogWrite(CH3_Pin, 0);
//        analogWrite(CH4_Pin, 0);
//        analogWrite(CH5_Pin, 0);
//    
        __IntervalExecute(togglePin(LED_Pin), 2000);
    }
    
    Com_PassbackInit();
    IWDG_Init(IWDG_Prescaler_64, 625);
}

static void loop()
{
    mtm.Running(millis());
}

/**
  * @brief  Main Function
  * @param  None
  * @retval None
  */
int main(void)
{
    InternalClocks_Init();
    Delay_Init();
    ADCx_Init(ADC1);
    setup();
    for(;;)loop();
}
