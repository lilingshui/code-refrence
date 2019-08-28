#include <stdio.h>
#include "hal.h"

int main(int argc, char** argv)
{
	printf("===== In test function 1 =====\n");

	struct tag_HW_DEVICE *device = NULL;
	/* 获取LED模块的struct tag_HW_DEVICE指针 */
	device = hw_get_device(LED_HARDWARE_MODULE_ID);
	
	if (NULL != device) 
	{
		/* 指针强转为led_device_t类型 */
		int val = 0;
		led_device_t* led_device = (led_device_t *)device;
		led_device->set_onoff(led_device, val);
		led_device->get_status(led_device, &val);
		led_device->close_led_device((struct tag_HW_DEVICE *)led_device);
	}

	printf("===== In test function 2 =====\n");
	return 0;
}

