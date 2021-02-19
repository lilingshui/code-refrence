#include <stdio.h>
#include "usr_params_driver.h"
#include <stdint.h>

static uint8_t m_flash_buf[ROM_SECTOR_SIZE*2];

 int ram_flash_write(uint32_t addr, uint8_t* p, int len)
{
	memcpy(m_flash_buf + addr, p, len);
	return len;
}

 int ram_flash_read(uint32_t addr, uint8_t* p, int len)
{
	memcpy(p, m_flash_buf + addr,  len);
	return len;
}


 uint8_t test[] = "123456789abcdefg";

 //data_params_frame kkk;
int main()
{
	uint8_t buf[100];
	//kkk.status = 0x12;

	int s = usr_params_init();
	printf("init flash=%d\r\n", s);

	s = write_usr_params(0, test, sizeof(test));
	printf("flash write =%d\r\n", s);

	s = write_usr_params(0, test, sizeof(test));
	printf("flash write =%d\r\n", s);

	s = read_usr_params(0, buf, sizeof(test));
	printf("flash read =%d: %s\r\n", s, buf);

	s = usr_params_init();
	printf("init flash=%d\r\n", s);
	s = write_usr_params(0, test, sizeof(test));
	printf("flash write =%d\r\n", s);
	s = read_usr_params(0, buf, sizeof(test));
	printf("flash read =%d: %s\r\n", s, buf);

	while (1) {}
}