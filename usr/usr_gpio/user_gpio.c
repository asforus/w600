/*****************************************************************************
*
* File Name : wm_gpio_demo.c
*
* Description: gpio demo function
*
* Copyright (c) 2014 Winner Micro Electronic Design Co., Ltd.
* All rights reserved.
*
* Author : dave
*
* Date : 2014-6-2
*****************************************************************************/
//#include "wm_include.h"
#include "user_gpio.h"


#if TEST_GPIO 
extern int gpio_test_timer_proc(void);

#define GPIO_SCAN_TIME					((configTICK_RATE_HZ)*5) //5s	//100ms
#define USR_GPIO_PIN 				(WM_IO_PB_08)
int user_gpio_func(void)
{
	u16 gpio_pin;
  s8 ret = 0;
	tls_os_timer_t *GpioTimer = NULL;
	//printf([])
	USR_DBG("gpio test start");
	gpio_pin= USR_GPIO_PIN;
	//for(gpio_pin = WM_IO_PB_06; gpio_pin < WM_IO_PB_19; gpio_pin ++)
	{
		//tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_PULLLOW);
		tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_FLOATING);
		ret = tls_gpio_read(gpio_pin);	/*œ»∂¡ƒ¨»œ◊¥Ã¨*/
		printf("\ngpio%c[%d] default value==[%d]\n", (gpio_pin > WM_IO_PB_00) ?'B':'A', gpio_pin - WM_IO_PB_00,ret);
	}
	tls_os_timer_create(&GpioTimer, gpio_test_timer_proc, NULL, GPIO_SCAN_TIME, TRUE, NULL);
	tls_os_timer_start(GpioTimer);
}


//gpio ≤‚ ‘≥Ã–Ú
int gpio_test_timer_proc(void)
{
	u16 gpio_pin;
	u16 ret;
  printf("\r\n***start***\r\n");
	//≤‚ ‘gpioB 13,14
	gpio_pin= USR_GPIO_PIN;
	//for(gpio_pin = WM_IO_PB_06; gpio_pin < WM_IO_PB_19; gpio_pin ++)
	{
		//tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_PULLHIGH);
		//ret = tls_gpio_read(gpio_pin);	/*œ»∂¡ƒ¨»œ◊¥Ã¨*/
		//printf("\ngpio%c[%d] default value==[%d]\n", (gpio_pin > WM_IO_PB_00) ?'B':'A', gpio_pin - WM_IO_PB_00,ret);
		/*
		tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_FLOATING);
		tls_gpio_write(gpio_pin,1);			//–¥∏ﬂ
		ret = tls_gpio_read(gpio_pin);
		printf("\ngpio%c[%d] floating high value==[%d]\n", (gpio_pin > WM_IO_PB_00) ? 'B':'A', gpio_pin - WM_IO_PB_00,ret);

		tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_FLOATING);
		tls_gpio_write(gpio_pin,0);			//–¥µÕ
		ret = tls_gpio_read(gpio_pin);
		printf("\ngpio%c[%d] floating low value==[%d]\n", (gpio_pin > WM_IO_PB_00) ? 'B':'A', gpio_pin - WM_IO_PB_00,ret);

		tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
		tls_gpio_write(gpio_pin,1);			//–¥∏ﬂ
		ret = tls_gpio_read(gpio_pin);
		printf("\ngpio%c[%d] pulllow high value==[%d]\n", (gpio_pin > WM_IO_PB_00) ?'B':'A', gpio_pin - WM_IO_PB_00,ret);

		tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_OUTPUT, WM_GPIO_ATTR_PULLLOW);
		tls_gpio_write(gpio_pin,0);			//–¥µÕ
		*/
		tls_gpio_write(gpio_pin,0);			//–¥µÕ
		ret = tls_gpio_read(gpio_pin);
		printf("\ngpio%c[%d]==[%d]\n", (gpio_pin >= WM_IO_PB_00) ? 'B':'A', gpio_pin - WM_IO_PB_00,ret);
		tls_os_time_delay(300);
		tls_gpio_write(gpio_pin,1);
		ret = tls_gpio_read(gpio_pin);
		printf("\ngpio%c[%d]==[%d]\n", (gpio_pin >= WM_IO_PB_00) ? 'B':'A', gpio_pin - WM_IO_PB_00,ret);
		
		}
	printf("\r\n####end####\r\n");
	return WM_SUCCESS;
}

#define USER_ISR_IO		WM_IO_PA_01
static void usr_gpio_isr_callback(void *context)
{
	u16 ret;

	ret = tls_get_gpio_irq_status(USER_ISR_IO);
	printf("\nint flag =%d\n",ret);
	if(ret)
	{
		tls_clr_gpio_irq_status(USER_ISR_IO);
		ret = tls_gpio_read(USER_ISR_IO);
		printf("\nafter int io =%d\n",ret);
	}
}

int gpio_isr_test(void)
{
	u16 gpio_pin;

	gpio_pin = USER_ISR_IO;

	//≤‚ ‘÷–∂œ
	tls_gpio_cfg(gpio_pin, WM_GPIO_DIR_INPUT, WM_GPIO_ATTR_PULLLOW);
	tls_gpio_isr_register(gpio_pin, usr_gpio_isr_callback, NULL);
	tls_gpio_irq_enable(gpio_pin, WM_GPIO_IRQ_TRIG_RISING_EDGE);
	printf("\ntest gpio %d rising isr\n",gpio_pin);
	return WM_SUCCESS;
}

#endif
