#ifndef __USR_PARAMS_PORT_H__
#define __USR_PARAMS_PORT_H__

#ifdef __cplusplus
extern "C" {
#endif
#if 0
/*************************************************************************
下面是需要移植的部分 带操作系统移植
***************************************************************************/
/*
*	互斥类型
*/
#define osMutexId_t       OSMutexObj_p 

/*
*	互斥创建
*/
#define osMutexNew(name)        OsMutexCreate(name)

/*
*	互斥获取
*/
#define osMutexAcquire(id, timeout)    OsMutexPend(id, timeout)

/*
*	互斥释放
*/
#define osMutexRelease(id)    OsMutexPost(id)

/*
*	互斥操作返回成功
*/
#define osOK              0

/*
*	flash扇区大小
*/
#define ROM_SECTOR_SIZE    4096

/*
*	数据备份0 存入flash位置地址
*/
#define DATA_SAVE_0_OFFSET 0

/*
*	数据备份 1 存入flash位置地址
*/
#define DATA_SAVE_1_OFFSET 4096

/*
*	读写 flash接口 成功返回实际长度
*/
#define flash_write(addr, buf, len) spi_flash_write(addr, buf, len)
#define flash_read(addr, buf, len)  spi_flash_read(addr, buf, len)

#endif

/*************************************************************************
-------------------------end------------------------------------
***************************************************************************/
// 不带操作系统移植	
#if 1
int ram_flash_write(uint32_t addr, uint8_t* p, int len);
int ram_flash_read(uint32_t addr, uint8_t* p, int len);
//无操作系统移植例子
#define osMutexId_t       				int
#define osMutexNew(name)  				osOK 
#define osMutexAcquire(id, timeout)     osOK
#define osMutexRelease(id)   			do{}while(0)
#define osOK                  			0
#define ROM_SECTOR_SIZE    				4096
#define DATA_SAVE_0_OFFSET 				0
#define DATA_SAVE_1_OFFSET              4096	
#define flash_write(addr, buf, len)   ram_flash_write(addr, buf, len) 
#define flash_read(addr, buf, len)    ram_flash_read(addr, buf, len)   
#endif

#ifdef __cplusplus
}
#endif
#endif