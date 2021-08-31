/*
 *  Driver Control commands for WFET_CHAR_DEVICES
 *
 *  IO Control commands defines
 *
 *  Author Yu Weifeng, yuweifeng.798@gmail.com
 *  Copyright (C) 2013 Wasion Group Limited
 *
 * History
 *   Version 1.0, 2013-04-02
 *      yu-weifeng, xIaOYUAIboBOJIe
 *
 */

#ifndef __WFOS_IOCTL_9G45_H
#define __WFOS_IOCTL_9G45_H


/* Ioctl definitions */

/*
 * Forward-compatible
 */
#define IOC_PRODUCTINFO_GET_PRODUCT_ID  IOC_PRODUCT_ID

#define IOC_COMMU_MODULES_GET_ID        IOC_COMMU_MODULES_TYPE
#define IOC_WFET_LCD_RESET              IOC_LCD_RESET
#define IOC_ETHERNET_RESET              IOC_ETHERNET_RST_CTL
#define IOC_WFET_BEEP_ONOFF             IOC_WARN_BEEP


#define IOC_NR_(nr)	(WFET_AT91_IOC_9260_LAST + nr)

/* product info. */
/* IOC_PRODUCTINFO_GET_PRODUCT_ID */
#define IOC_PRODUCTINFO_GET_HARDWARE_ID	_IOR(WFET_AT91_IOC_MAGIC, IOC_NR_(1), int)

/* ethernet */
/* IOC_ETHERNET_RESET */
#define IOC_ETHERNET_RESET_IDX		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(2), int)

/* Commu */
/* IOC_COMMU_MODULES_GET_ID
   IOC_COMMU_MODULES_START
   IOC_COMMU_MODULES_RESET
   IOC_COMMU_MODULES_POWER */
/* temperature compensation */
#define IOC_COMMU_MODULES_POWER0	_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(3), int)
#define IOC_COMMU_MODULES_POWER1	_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(4), int)

#define IOC_COMMU_MODULES_TEMP_COMP	_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(5), int)

/* Output: Alarm etc. */
#define IOC_OUTPUT_STATE_GET		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(6), int)

/* MMC/SD */
#define IOC_MMC_WP			_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(7), int)

/* sbm */
#define IOC_SBM_SB_SCANNING		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(8), int)
#define IOC_SBM_SB_ONLINE		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(9), int)
#define IOC_SBM_SB_TYPE			_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(10), int)
#define IOC_SBM_SB_WRITE_RAW		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(11), int)
#define IOC_SBM_SB_READ_RAW		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(12), int)
#define IOC_SLOT_PNP_GET		IOC_SBM_STATE_GET
#define IOC_SLOT_TYP_GET		IOC_SBM_SB_ONLINE
/* sb power/reset/gain control */
struct wfet_sbm_write_raw_t {
	unsigned char slot_idx; /* spec. */
	unsigned int offset; /* spec. */
	unsigned char bit_mask; /* spec. */
	unsigned char bit_val; /* spec. */
};
struct wfet_sbm_read_raw_t {
	unsigned char slot_idx;
	unsigned int offset;

	unsigned char value;
};

/* MMC/SD */
#define IOC_MMC_WP_GET			IOC_MMC_WP
#define IOC_MMC_WP_SET			_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(13), int)

/* IOC_POWER_STATE */
#define IOC_PM_POWER_STATE_ALL		IOC_POWER_STATE

/* LCD, Gray Level */
#define IOC_LCD_SET_GRAY		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(14), int)
#define IOC_LCD_GET_GRAY		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(15), int)

/* Radio module */
#define IOC_RADIO_RESET		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(16), int)
#define IOC_RADIO_SEND		_IOW(WFET_AT91_IOC_MAGIC, IOC_NR_(17), int)

/* max */
#define WFET_AT91_IOC_9G45_LAST		IOC_NR_(40)


#endif /* __WFOS_IOCTL_9G45_H */
