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
    
    pinMode(M1_IN1_Pin, OUTPUT);
	  pinMode(M1_IN2_Pin, OUTPUT);
	  pinMode(Big_led, OUTPUT_OPEN_DRAIN);

	  PWM_Init(Servo_PWM_Pin, 1000, 50);
		PWM_Init(M1_PWM_Pin, 1000, 500);
 
    digitalWrite(M1_IN1_Pin, LOW);
    digitalWrite(M1_IN2_Pin, LOW);
    digitalWrite(Big_led, LOW);

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

}

/**
  * @brief  Main Function
  * @param  None
  * @retval None
  */
int main(void)
{
   // InternalClocks_Init();
	  GPIO_JTAG_Disable();
    Delay_Init();
    ADCx_Init(ADC1);
    setup();
    for(;;)loop();
}
