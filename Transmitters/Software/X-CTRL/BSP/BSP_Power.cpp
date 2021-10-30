#include "Basic/FileGroup.h"
#include "IP5108/IP5108.h"
#include "BSP.h"

static IP5108 charger;
static int16_t BattVoltage;

void Power_GetInfo(float* battCurrent,float* battVoltage,float* battVoltageOc)
{
    if(battCurrent)
        *battCurrent = charger.current;
    
    if(battVoltage)
        *battVoltage = charger.voltage;
    
    if(battVoltageOc)
        *battVoltageOc = charger.voltageOc;
}

float Power_GetBattUsage()
{
      //VDDA=3.268 
	   BattVoltage = analogRead_DMA(BAT_DET_Pin);
	  if(BattVoltage<=2005 )
		{
			BattVoltage=0;
		}
		else if(BattVoltage>=2632 )
		{
			BattVoltage=2632;
		}
    float batUsage = __Map(BattVoltage, 2005, 2632, 0.0f, 100.0f);
    __LimitValue(batUsage, 0, 100);
    return batUsage;
}

void Power_Init()
{
  /*LED*/
    pinMode(LED_Pin, OUTPUT);
    digitalWrite(LED_Pin, LOW);
    
    /*电源保持*/
    pinMode(POWER_ON_Pin, OUTPUT);
    digitalWrite(POWER_ON_Pin, HIGH);
    
    /*电源按键*/
    pinMode(POWER_EN_Pin, INPUT);
	
	  
	  pinMode(BAT_DET_Pin, INPUT_ANALOG_DMA);
    ADC_DMA_Init();

    Power_SetLedState(true);
}

void Power_Update()
{
    //charger.update();
//    Serial.printf("Batt U = %0.2fmV, I = %0.2fmA, ", charger.voltage, charger.current);
//    Serial.printf("Oc U = %0.2fmV\r\n", charger.voltageOc);
}

void Power_Shutdown()
{
   Backlight_SetGradual(0, 200);
	 digitalWrite(LED_Pin, HIGH);
   pinMode(POWER_ON_Pin, OUTPUT_OPEN_DRAIN);
   digitalWrite(POWER_ON_Pin, LOW);
}

void Power_SetLedState(bool state)
{
    analogWrite(LED_Pin, state ? 1000 : 0);
}

void Power_SetLedValue(uint16_t val)
{
    analogWrite(LED_Pin, val);
}
