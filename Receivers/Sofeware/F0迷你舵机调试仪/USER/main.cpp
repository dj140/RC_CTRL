#include "FileGroup.h"
#include "ComPrivate.h"

MillisTaskManager mtm(TP_MAX, true);
int16_t speed;
void blink()
{
   for(int j = 0; j <= 1000; j++)
        {
            analogWrite(LED_Pin, j);
            delay_us(500);
        }
  for(int j = 1000; j > 0; j--)
        {
            analogWrite(LED_Pin, j);
            delay_us(500);
        }
}
void fan_speed()
{
switch(count){
	case 0:
		  speed=55;
		  break;
	case 1:
		  speed=70;
		  analogWrite(LED_Pin, 150); 
		  break;
	case 2:
			analogWrite(LED_Pin, 350); 
		  speed=75;
		  break;
	case 3:
		analogWrite(LED_Pin, 550); 
		  speed=80;
		  break;
	case 4:
				analogWrite(LED_Pin, 750); 

		  speed=85;
		  break;
	case 5:
				analogWrite(LED_Pin, 950); 

		  speed=90;
		  break;
	case 6:
		  speed=55;
	    analogWrite(LED_Pin, 0); 
		  break;
	 default:	 
		// blink();
		 speed=55;       
}
//if(count>0 &&  count<6) __IntervalExecute(blink(), 1);
analogWrite(PPM_Pin, speed); 

}
static void setup()
{
    pinMode(LED_Pin, OUTPUT);
    __LoopExecute((togglePin(LED_Pin), delay(80)), 10);
//    
//    pinMode(BAT_DET_Pin, INPUT_ANALOG);
//    //ADC_DMA_Init();
//    randomSeed(analogRead(BAT_DET_Pin));
//    
//    PWM_Init(CH0_Pin, 1000, 50);
//    PWM_Init(CH1_Pin, 1000, 50);
//    PWM_Init(CH2_Pin, 1000, 50);
//    PWM_Init(CH3_Pin, 1000, 50);
	Button_Init();
	//  pinMode(CH4_Pin, INPUT_PULLUP);
    //PWM_Init(CH4_Pin, 1000, 50);
    PWM_Init(PPM_Pin, 1000, 50);
	  PWM_Init(LED_Pin, 1000, 500);

    mtm.TaskRegister(TP_Button_Update, Button_Update, 1);
    mtm.TaskRegister(TP_Ctrl, fan_speed, 2);

  // mtm.TaskRegister(TP_InfoLED, blink, 500);

//    Com_Init();
//   	Serial.begin(100000,SERIAL_9E2);
//	
//    mtm.TaskRegister(TP_ComHandler, Task_ComHandler, 10);
//		mtm.TaskRegister(TP_Sbus, Task_Sbus, 10);
//    mtm.TaskRegister(TP_Ctrl, Task_Ctrl, 20);
//    mtm.TaskRegister(TP_InfoLED, Task_InfoLED, 500);
//    mtm.TaskRegister(TP_IWDG_Feed, IWDG_ReloadCounter, 500);
//    mtm.TaskRegister(TP_ComPassback, Task_ComPassback, 1000);

//    while (!RCX::Handshake::Process())
//    {
//        __IntervalExecute(togglePin(LED_Pin), 2000);
//    }
//    
//    Com_PassbackInit();
//    IWDG_Init(IWDG_Prescaler_64, 625);
}

static void loop()
{
	       // __IntervalExecute(togglePin(LED_Pin), 2000);


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
