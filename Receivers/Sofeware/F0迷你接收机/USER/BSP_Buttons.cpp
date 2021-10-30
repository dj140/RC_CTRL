#include "FileGroup.h"
#include "ComPrivate.h"

uint8_t count=0;

ButtonEvent btOK;

static void ButtonEvent_Handler(ButtonEvent* btn, int event)
{
    if(btn == &btOK)
    {
        if(event == ButtonEvent::EVENT_ButtonPress)
        {
					count+=1;
					if(count>5)count=1;
        }
        if(event == ButtonEvent::EVENT_ButtonLongPressed)
        {
					count=6;
        }
//        if(event == ButtonEvent::EVENT_ButtonDoubleClick)
//        {
//    
//        }
    }
    
  
}

void Button_Init()
{
    
    pinMode(SBUS_Pin, INPUT_PULLUP); 
   btOK.EventAttach(ButtonEvent_Handler);
}



void Button_Update()
{

    btOK.EventMonitor(!digitalRead(SBUS_Pin));
    
  
}
