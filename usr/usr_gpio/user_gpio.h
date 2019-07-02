#ifndef USER_GPIO_H
#define USER_GPIO_H

#define TEST_GPIO 1// CFG_ON

#include <stdio.h>
#include <stdlib.h>
#include "wm_type_def.h"

#include "wm_gpio.h"
#include "wm_params.h"
#include "wm_osal.h"
#include "wm_efuse.h"
#include "wm_regs.h"
#include "FreeRTOS.h"
#if 1 
#define USR_DBG(fmt,...) \
	printf("[%s][Func:%s]#%d#"fmt"\r\n",__FILE__,__func__,__LINE__,##__VA_ARGS__); 
#else
#define USR_DBG(format,...)
#endif

#endif  //USER_GPIO_H
 