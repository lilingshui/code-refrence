#ifndef __USR_PARAMS_DRIVER_H__
#define __USR_PARAMS_DRIVER_H__

#include <stdint.h>
#include "usr_params_port.h"
#include <string.h>

#define DATA_SLAVE_FLAG (0xa5cd)


#pragma pack(1)


typedef struct{
			uint16_t crc;
			uint16_t flag;
			uint32_t count;
}data_save_head;

typedef struct{
		uint8_t status;
		uint8_t indx;
		data_save_head head;
		uint8_t data[ROM_SECTOR_SIZE-sizeof(data_save_head)-4];
}data_params_frame;

#pragma pack()

#ifdef __cplusplus
extern "C" {
#endif


/*
*	初始化 返回0成功 其它失败
*/
int usr_params_init(void);


/*
*	读写参数 addr 存储位置偏移 0- block-8, 
*   @param buf 读写数据缓存
*   @param len 读写数据长度
*   @return 返回0成功 其它失败
*/
int read_usr_params(uint32_t addr,  uint8_t *buf, int len);
int write_usr_params(uint32_t addr,  uint8_t *buf, int len);

#ifdef __cplusplus
}
#endif
#endif
