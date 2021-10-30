#include "FileGroup.h"
#include "ComPrivate.h"


MillisTaskManager mtm(TP_MAX, true);

static void setup()
{

    pinMode(LED_Pin, OUTPUT);
    __LoopExecute((togglePin(LED_Pin), delay(80)), 6);

    pinMode(BAT_DET_Pin, INPUT_ANALOG_DMA);
    ADC_DMA_Init();
    randomSeed(analogRead(BAT_DET_Pin));

    PWM_Init(CH0_Pin, 1000, 50);
    PWM_Init(CH1_Pin, 1000, 50);
    PWM_Init(CH2_Pin, 1000, 50);
    PWM_Init(CH3_Pin, 1000, 50);
    PWM_Init(CH4_Pin, 1000, 50);
    PWM_Init(CH5_Pin, 1000, 50);
    PWM_Init(CH6_Pin, 1000, 50);
    PWM_Init(CH7_Pin, 1000, 50);



    Com_Init();
		Serial3.begin(100000,SERIAL_9E2);
    
    mtm.TaskRegister(TP_ComHandler, Task_ComHandler, 10);
    mtm.TaskRegister(TP_Ctrl, Task_Ctrl, 20);
		mtm.TaskRegister(TP_Sbus, Task_Sbus, 10);
    mtm.TaskRegister(TP_InfoLED, Task_InfoLED, 500);
    mtm.TaskRegister(TP_IWDG_Feed, IWDG_ReloadCounter, 500);
    mtm.TaskRegister(TP_ComPassback, Task_ComPassback, 1000);

    while (!RCX::Handshake::Process())
    {
        __IntervalExecute(togglePin(LED_Pin), 2000);
    }
    
    Com_PassbackInit();
    IWDG_Init(IWDG_Prescaler_64, 625);
}

static void loop()
{
    mtm.Running(millis());
	  digitalWrite(LED_Pin, LOW);

}

/**
  * @brief  Main Function
  * @param  None
  * @retval None
  */
int main(void)
{
    InternalClocks_Init();
	  GPIO_JTAG_Disable();
    Delay_Init();
   // ADCx_Init(ADC1);
    setup();
    for(;;)loop();
}
