/***************************************************************************** 
* 
* File Name : main.c
* 
* Description: main 
* 
* Copyright (c) 2014 Winner Micro Electronic Design Co., Ltd. 
* All rights reserved. 
* 
* Author : dave
* 
* Date : 2014-6-14
*****************************************************************************/ 
#include "wm_include.h"

extern int user_gpio_func(void);
void UserMain(void)
{
	printf("\n user task\n");

#if DEMO_CONSOLE
	CreateDemoTask();
#endif
  printf("\r\ndate--%s,time--%s\r\n",__DATE__,__TIME__);
  printf("\r\n********proj create by zpf********\r\n");
  user_gpio_func();
//用户自己的task
}

