/*
 * MIT License
 * Copyright (c) 2019 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __FILEGROUP_H
#define __FILEGROUP_H

/**
  *@Illustrate: A Cross-platform migration Project | Arduino for STM32F0xx
  *@Author: FASTSHIFT
  *@Website: https://github.com/FASTSHIFT/Arduino-For-Keil
  */

//************* Arduino Library **************//
#include "Arduino.h"
#include "SPI.h"
#include "Tone.h"
#include "Wire.h"

#include "SysConfig.h"
#include "MillisTaskManager/MillisTaskManager.h"
#include "CommonMacro.h"

#include "ButtonEvent.h"
extern uint8_t count;
void Button_Init();
void Button_Update();

extern MillisTaskManager mtm;
enum TaskPriority
{
	  TP_Button_Update,
    TP_ComHandler,
    TP_Ctrl,
    TP_InfoLED,
    TP_IWDG_Feed,
    TP_ComPassback,
		TP_Sbus,
    TP_MAX
};

void Task_ComHandler();
void Task_ComPassback();
void Task_Ctrl();
void Task_InfoLED();
void Task_Sbus();

void IWDG_Init(uint8_t prescaler, uint16_t reload);

#endif
