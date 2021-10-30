#include "FileGroup.h"
#include "ComPrivate.h"

#define DEAD_ZONE_VAL 40
int MAX_Power;
static void MotorWrite(int16_t val)
{
	if(val > DEAD_ZONE_VAL)
	{
		    val = map(val, 0, RCX_CHANNEL_DATA_MAX, 0, MAX_Power);
			  analogWrite(M1_PWM_Pin, val);
	      digitalWrite(M1_IN1_Pin, LOW);
        digitalWrite(M1_IN2_Pin, HIGH);
	}
	else if(val < -DEAD_ZONE_VAL)
	{
	    val = map(val, 0, -RCX_CHANNEL_DATA_MAX, 0, 600);
	    analogWrite(M1_PWM_Pin, val);
			digitalWrite(M1_IN1_Pin, HIGH);
      digitalWrite(M1_IN2_Pin, LOW);
	}
	else 
	{
	      analogWrite(M1_PWM_Pin, 0);
			  digitalWrite(M1_IN1_Pin, LOW);
        digitalWrite(M1_IN2_Pin, LOW);
	}
}

static void SteerWrite(int16_t val)
{
      analogWrite(Servo_PWM_Pin, val);
}


void Task_Ctrl()
{
    if(!RCX::GetRxConnected())
    {
        MotorWrite(0);
        SteerWrite(0);
			  digitalWrite(M1_IN1_Pin, LOW);
        digitalWrite(M1_IN2_Pin, LOW);
			  digitalWrite(Big_led, LOW);

        return;
    }
     
		pinMode(Big_led, OUTPUT);
    int16_t motorVal = map(RCX::GetRxPackChannel(CH_JSL_Y), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, -1000, 1000);
    int16_t mode = (float)RCX::GetRxPackChannel(CH_LMT_L) / RCX_CHANNEL_DATA_MAX;
		
 
		int16_t steerVal = map(RCX::GetRxPackChannel(CH_JSR_X), -RCX_CHANNEL_DATA_MAX, RCX_CHANNEL_DATA_MAX, 25, 125);
    int16_t Light = (float)RCX::GetRxPackChannel(CH_LMT_R) / RCX_CHANNEL_DATA_MAX;
		
		if(mode==-1)
		{
		  MAX_Power=600;
		}
		else if(mode==1)
		{
		  MAX_Power=900;
		}
		if(Light==-1)
		{
			  digitalWrite(Big_led, LOW);
		}
		else if(Light==1)
		{
			  digitalWrite(Big_led, HIGH);
		}
		
    MotorWrite(motorVal);
    SteerWrite(steerVal);	

}
