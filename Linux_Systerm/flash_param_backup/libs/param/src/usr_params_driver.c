#include <stdio.h>
#include "usr_params_driver.h"
static int load_usr_params(void);
static const unsigned short crc16tab[256]= {
	0x0000,0x1021,0x2042,0x3063,0x4084,0x50a5,0x60c6,0x70e7,
	0x8108,0x9129,0xa14a,0xb16b,0xc18c,0xd1ad,0xe1ce,0xf1ef,
	0x1231,0x0210,0x3273,0x2252,0x52b5,0x4294,0x72f7,0x62d6,
	0x9339,0x8318,0xb37b,0xa35a,0xd3bd,0xc39c,0xf3ff,0xe3de,
	0x2462,0x3443,0x0420,0x1401,0x64e6,0x74c7,0x44a4,0x5485,
	0xa56a,0xb54b,0x8528,0x9509,0xe5ee,0xf5cf,0xc5ac,0xd58d,
	0x3653,0x2672,0x1611,0x0630,0x76d7,0x66f6,0x5695,0x46b4,
	0xb75b,0xa77a,0x9719,0x8738,0xf7df,0xe7fe,0xd79d,0xc7bc,
	0x48c4,0x58e5,0x6886,0x78a7,0x0840,0x1861,0x2802,0x3823,
	0xc9cc,0xd9ed,0xe98e,0xf9af,0x8948,0x9969,0xa90a,0xb92b,
	0x5af5,0x4ad4,0x7ab7,0x6a96,0x1a71,0x0a50,0x3a33,0x2a12,
	0xdbfd,0xcbdc,0xfbbf,0xeb9e,0x9b79,0x8b58,0xbb3b,0xab1a,
	0x6ca6,0x7c87,0x4ce4,0x5cc5,0x2c22,0x3c03,0x0c60,0x1c41,
	0xedae,0xfd8f,0xcdec,0xddcd,0xad2a,0xbd0b,0x8d68,0x9d49,
	0x7e97,0x6eb6,0x5ed5,0x4ef4,0x3e13,0x2e32,0x1e51,0x0e70,
	0xff9f,0xefbe,0xdfdd,0xcffc,0xbf1b,0xaf3a,0x9f59,0x8f78,
	0x9188,0x81a9,0xb1ca,0xa1eb,0xd10c,0xc12d,0xf14e,0xe16f,
	0x1080,0x00a1,0x30c2,0x20e3,0x5004,0x4025,0x7046,0x6067,
	0x83b9,0x9398,0xa3fb,0xb3da,0xc33d,0xd31c,0xe37f,0xf35e,
	0x02b1,0x1290,0x22f3,0x32d2,0x4235,0x5214,0x6277,0x7256,
	0xb5ea,0xa5cb,0x95a8,0x8589,0xf56e,0xe54f,0xd52c,0xc50d,
	0x34e2,0x24c3,0x14a0,0x0481,0x7466,0x6447,0x5424,0x4405,
	0xa7db,0xb7fa,0x8799,0x97b8,0xe75f,0xf77e,0xc71d,0xd73c,
	0x26d3,0x36f2,0x0691,0x16b0,0x6657,0x7676,0x4615,0x5634,
	0xd94c,0xc96d,0xf90e,0xe92f,0x99c8,0x89e9,0xb98a,0xa9ab,
	0x5844,0x4865,0x7806,0x6827,0x18c0,0x08e1,0x3882,0x28a3,
	0xcb7d,0xdb5c,0xeb3f,0xfb1e,0x8bf9,0x9bd8,0xabbb,0xbb9a,
	0x4a75,0x5a54,0x6a37,0x7a16,0x0af1,0x1ad0,0x2ab3,0x3a92,
	0xfd2e,0xed0f,0xdd6c,0xcd4d,0xbdaa,0xad8b,0x9de8,0x8dc9,
	0x7c26,0x6c07,0x5c64,0x4c45,0x3ca2,0x2c83,0x1ce0,0x0cc1,
	0xef1f,0xff3e,0xcf5d,0xdf7c,0xaf9b,0xbfba,0x8fd9,0x9ff8,
	0x6e17,0x7e36,0x4e55,0x5e74,0x2e93,0x3eb2,0x0ed1,0x1ef0
};

static unsigned short wslib_crc16_ccitt(const void *buf, unsigned int len,unsigned short inicrc)
{
	register unsigned int counter;
	register unsigned short crc = inicrc;
	for(counter = 0; counter < len; counter++) {
		crc = (crc<<8) ^ crc16tab[((crc>>8) ^ ((unsigned char *)buf)[counter])&0x00FF];
	}
	return crc;
}

static osMutexId_t m_usr_params_mutex;

/*
*	flash存储数据区域地方
*/
data_params_frame m_data_params;

int usr_params_init(void)
{
	m_usr_params_mutex = (osMutexId_t)osMutexNew(0);
	return load_usr_params();
}


/*
*	参数加载
*	返回 0 成功 其它失败
*/
static int load_usr_params(void)
{
	int reauls = -1;;
	data_save_head head[2];
	int indx = 0;
	uint32_t addr[2] = { DATA_SAVE_0_OFFSET, DATA_SAVE_1_OFFSET };
	if ( osMutexAcquire(m_usr_params_mutex, 5000) == osOK ) {
		m_data_params.status = 0;
		m_data_params.indx   = 0;
		flash_read(DATA_SAVE_0_OFFSET, (uint8_t *)&head[0], sizeof(data_save_head));
		flash_read(DATA_SAVE_1_OFFSET,  (uint8_t *)&head[1], sizeof(data_save_head));

		if (head[0].count >= head[1].count) {
			indx  = 0;
		} else {
			indx  = 1;
		}

		printf("==== head[0].count is %d, head[1].count is %d ====\n", head[0].count, head[1].count);
		printf("==== head[%d].flag is 0x%x ====\n", indx, head[indx].flag);
		printf("==== head[%d].crc.crc is %d ====\n", indx, head[indx].crc);
		
		if (head[indx].flag == DATA_SLAVE_FLAG) {
			//进行CRC校验的比对
			flash_read(addr[indx], (uint8_t *)&m_data_params.head, ROM_SECTOR_SIZE);
			if (wslib_crc16_ccitt((uint8_t *)&m_data_params.head.flag, ROM_SECTOR_SIZE-sizeof(uint16_t), 0) == head[indx].crc) {
				m_data_params.indx   = indx;
				m_data_params.status = 2;
				reauls = 2;
			} else {
				memset(&m_data_params, 0, sizeof(m_data_params));
			}
		}

		indx = (indx+1)%2;
		if (reauls < 0 && head[indx].flag == DATA_SLAVE_FLAG) {
			flash_read(addr[indx], (uint8_t *)&m_data_params.head, ROM_SECTOR_SIZE);
			if (wslib_crc16_ccitt((uint8_t *)&m_data_params.head.flag, ROM_SECTOR_SIZE-sizeof(uint16_t), 0) == head[indx].crc) {
					//asm(""::"memory");
				m_data_params.indx   = indx;
				m_data_params.status = 2;
				reauls = 3;
			} else {
				memset(&m_data_params, 0, sizeof(m_data_params));
			}
		}
		osMutexRelease(m_usr_params_mutex);
	}

	//m_data_params.status = 0xaa;
	return reauls;
}

/*
*	addr 地址偏移 0- (4000-8) 不能超过(4000-8)
*   返回 0 成功 其它失败
*/
int read_usr_params(uint32_t addr,  uint8_t *buf, int len)
{
	int reauls = -9;
	if (addr < sizeof(m_data_params.data) && len > 0 && (addr+len) <= sizeof(m_data_params.data)) {
		if (osMutexAcquire(m_usr_params_mutex, 5000) == osOK) {
			if (m_data_params.status) {
				memcpy(buf, m_data_params.data + addr, len);
				reauls = 0;
			} else {
				reauls = -2;
			}
			osMutexRelease(m_usr_params_mutex);	
		} else {
			reauls = -8;
		}
	}
	return reauls;
}

/*
*	addr 地址偏移 0- (FLASH_BLOCK_SIZE-8) 不能超过(FLASH_BLOCK_SIZE-8) flash 范围是 0-(FLASH_BLOCK_SIZE-8)
*   返回 0 成功 其它失败
*/
int write_usr_params(uint32_t addr,  uint8_t *buf, int len)
{
	int reauls = -9;
	if (addr < sizeof(m_data_params.data) && len > 0 && (addr+len) <= sizeof(m_data_params.data)) {
		if (osMutexAcquire(m_usr_params_mutex, 5000) == osOK) {
			int status = m_data_params.status;
			int indx   = m_data_params.indx%2;
			uint32_t count = m_data_params.head.count;
			int flash_addr = DATA_SAVE_0_OFFSET;
			if (status > 1) {
				indx = (indx+1)%2;
				if ( indx == 0 ) {
					flash_addr = DATA_SAVE_0_OFFSET;
				} else {
					flash_addr = DATA_SAVE_1_OFFSET;
				}
				m_data_params.head.count++;
			}
			else if (status == 1) {//不增加计数器
			}//第一次写需要增加计数器
			else {
				m_data_params.head.count = 0;
				count = 0;
			}

			memcpy(m_data_params.data + addr, buf, len);
			m_data_params.head.flag = DATA_SLAVE_FLAG;
			m_data_params.head.crc =  wslib_crc16_ccitt(((uint8_t *)(&m_data_params.head))+2, ROM_SECTOR_SIZE-sizeof(uint16_t),0);

			reauls = flash_write(flash_addr, (uint8_t *)&m_data_params.head,ROM_SECTOR_SIZE);
			if (reauls == ROM_SECTOR_SIZE) {//写成功
				//__asm(""::"memory");
				m_data_params.status = 0x02;
				m_data_params.indx = indx;
				reauls = 0;
			} else {//失败
				m_data_params.status = 1;
				m_data_params.head.count = count;
				reauls = -2;
			}

			printf("==== m_data_params.head.crc is %d ====\n", m_data_params.head.crc);
			printf("==== flash_addr is 0x%x ====\n", flash_addr);
			printf("==== m_data_params.head.count is 0x%x ====\n", m_data_params.head.count);
			osMutexRelease(m_usr_params_mutex);
		} else {
			reauls = -8;
		}
	}

    return reauls;
}

// uint8_t *get_usr_params_ptr(void)
// {
	// return (uint8_t *)&m_data_params.head;
// }
