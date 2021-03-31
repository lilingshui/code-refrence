/*
 * drivers/char/wfet_char_devices/wfos_ioctl.h
 *
 * Author liulf, liulf@ihep.ac.cn
 * Copyright (C) 2007 Changsha Wasion Meters Group
 *
 * The source code in this file can be freely used, adapted,
 * and redistributed in source or binary form, so long as an
 * acknowledgment appears in derived source files.  The citation
 * should list that the code comes from the book "Linux Device
 * Drivers" by Alessandro Rubini and Jonathan Corbet, published
 * by O'Reilly & Associates.   No warranty is attached;
 * we cannot take responsibility for errors or fitness for use.
 *
 */
/*
 * history:
 *  2011.12.27, add WFET-1000TS-V1.0 support (by Yu Weifeng, yuweifeng@wasion.cn)
 *      Intelligent Anti-electricity Stealing Terminal(IAST)
 *
 */

#ifndef __WFOS_IOCTL_9260_H
#define __WFOS_IOCTL_9260_H

#include <linux/ioctl.h> 	/* needed for the _IOW etc stuff used later */

/* Ioctl definitions */

/* Use 'c' as magic number */
#define WFET_AT91_IOC_MAGIC   'c'

/* LED stuffs */
#define LED_ON		1
#define LED_OFF		0

/* GPIO pin: output level */
#define OUTPUT_LEVEL_HIGH   1
#define OUTPUT_LEVEL_LOW    0

#define WORK_LED	 0
#define METER_LED	 1
#define NET_LED		 2
#define RSSI_LED	 3

struct led_blinking_timeout
{
	unsigned char led;	/* id or index */
	unsigned long timeout;	/* in m-sec */
	unsigned long continued;
};

struct st7567_data_address
{
	unsigned char x_addr;
	unsigned char page_addr;
};

/* LED light on / off. */
#define IOC_LED_ON	_IOW(WFET_AT91_IOC_MAGIC,0, int)
#define IOC_LED_OFF	_IOW(WFET_AT91_IOC_MAGIC,1, int)

/* Communication modules (GPRS,CDMA and etc) start/reset and power on/off. */
#define IOC_COMMU_MODULES_TYPE     _IOW(WFET_AT91_IOC_MAGIC,2, int)
#define IOC_COMMU_MODULES_START    _IOW(WFET_AT91_IOC_MAGIC,3, int)
#define IOC_COMMU_MODULES_RESET    _IOW(WFET_AT91_IOC_MAGIC,4, int)
#define IOC_COMMU_MODULES_POWERON  _IOW(WFET_AT91_IOC_MAGIC,5, int)
#define IOC_COMMU_MODULES_POWEROFF _IOW(WFET_AT91_IOC_MAGIC,6, int)

#define IOC_LED_BLINKING_START	    _IOW(WFET_AT91_IOC_MAGIC,7, int)
#define IOC_LED_BLINKING_STOP	    _IOW(WFET_AT91_IOC_MAGIC,8, int)

#define IOC_BLINKING_SET_TIMEOUT 	_IOW(WFET_AT91_IOC_MAGIC,9, int)

#define IOC_PLC_POWERON 	    _IOW(WFET_AT91_IOC_MAGIC,10, int)
#define IOC_PLC_POWEROFF 	    _IOW(WFET_AT91_IOC_MAGIC,11, int)

#define IOC_INPUT_CHAN_MAX 	    _IOR(WFET_AT91_IOC_MAGIC,12, int)
#define IOC_INPUT_STATE_GET     _IOR(WFET_AT91_IOC_MAGIC,13, int)
#define IOC_INPUT_ALL_CHAN 	    _IOR(WFET_AT91_IOC_MAGIC,14, int)

#define IOC_OUTPUT_CHAN_MAX	    _IOR(WFET_AT91_IOC_MAGIC,15, int)
#define IOC_OUTPUT_CTRL_SET	    _IOW(WFET_AT91_IOC_MAGIC,16, int)
#define IOC_OUTPUT_CTRL_CLEAR	_IOW(WFET_AT91_IOC_MAGIC,17, int)
#define IOC_OUTPUT_ALL_CHAN	    _IOR(WFET_AT91_IOC_MAGIC,18, int)

#define IOC_PULSE_CHAN_MAX 	    _IOR(WFET_AT91_IOC_MAGIC,19, int)
#define IOC_PULSE_CNT_GET 	    _IOR(WFET_AT91_IOC_MAGIC,20, int)

#define IOC_ANALOG_CHAN_MAX	    _IOR(WFET_AT91_IOC_MAGIC,21, int)
#define IOC_DC_ANALOG_GET	    _IOR(WFET_AT91_IOC_MAGIC,22, int)

#define IOC_PULSE_LEVEL_GET     _IOR(WFET_AT91_IOC_MAGIC,23, int)//pulse_level
/* 这三个脉冲方面的IOCTL可以清除 */
//#define IOC_7022_READ           _IOR(WFET_AT91_IOC_MAGIC,24, int)//pulse_level
//#define IOC_7022_WRITE          _IOW(WFET_AT91_IOC_MAGIC,25, int)//pulse_level
//#define IOC_7022_HW_RESET       _IOW(WFET_AT91_IOC_MAGIC,26, int)//pulse_level

/* 遥信模块复位 */
#define IOC_INPUT_RESET         _IOW(WFET_AT91_IOC_MAGIC,25, int)

/* 取得脉冲累计数值和最后一次脉冲的发生时刻 */
#define IOC_PULSE_LASTTIME_GET		_IOR(WFET_AT91_IOC_MAGIC,24, int)

#define IOC_RELAY_LED_VALUE		    _IOW(WFET_AT91_IOC_MAGIC,27, int)//写led数据
#define IOC_RELAY_OUTPUT_ENABLE		_IOW(WFET_AT91_IOC_MAGIC,28, int)//打开"输出使用"
#define IOC_RELAY_OUTPUT_DISABLE	_IOW(WFET_AT91_IOC_MAGIC,29, int)//关闭"输出使用"

//added by zhangwei
#define AP89170_IOCTL_POWER_UP      _IOW(WFET_AT91_IOC_MAGIC,30, int)
#define AP89170_IOCTL_POWER_DOWN    _IOW(WFET_AT91_IOC_MAGIC,31, int)
#define AP89170_IOCTL_PAUSE         _IOW(WFET_AT91_IOC_MAGIC,32, int)
#define AP89170_IOCTL_RESUME        _IOW(WFET_AT91_IOC_MAGIC,33, int)
#define AP89170_IOCTL_PLAY          _IOW(WFET_AT91_IOC_MAGIC,34, int)
#define AP89170_IOCTL_STATUS        _IOW(WFET_AT91_IOC_MAGIC,35, int)
#define AP89170_IOCTL_PREFETCH      _IOW(WFET_AT91_IOC_MAGIC,36, int)
#define AP89170_IOCTL_PUP1          _IOW(WFET_AT91_IOC_MAGIC,37, int)
#define AP89170_IOCTL_PDN1          _IOW(WFET_AT91_IOC_MAGIC,38, int)
//29 to 38 changed by zhangwei

#define IOC_BATTERY_CHARGE          _IOW(WFET_AT91_IOC_MAGIC,39, int)
#define IOC_BATTERY_ENABLE          _IOW(WFET_AT91_IOC_MAGIC,40, int)

#define IOC_PULSE_CNT_CLEAR         _IOW(WFET_AT91_IOC_MAGIC,41, int)

#define IOCTL_FM1702SL_SPIINIT    	    _IOW(WFET_AT91_IOC_MAGIC,42, int)
#define IOCTL_FM1702SL_INIT      		_IOW(WFET_AT91_IOC_MAGIC,43, int)
#define IOCTL_FM1702SL_REQUESTALL   	_IOW(WFET_AT91_IOC_MAGIC,44, int)
#define IOCTL_FM1702SL_REQUESTIDLE   	_IOW(WFET_AT91_IOC_MAGIC,45, int)
#define IOCTL_FM1702SL_GETUID      		_IOW(WFET_AT91_IOC_MAGIC,46, int)
#define IOCTL_FM1702SL_SELECTTAG     	_IOW(WFET_AT91_IOC_MAGIC,47, int)
#define IOCTL_FM1702SL_WRITEKEYTOE2     _IOW(WFET_AT91_IOC_MAGIC,48, int)
#define IOCTL_FM1702SL_LOADKEYE2      	_IOW(WFET_AT91_IOC_MAGIC,49, int)
#define IOCTL_FM1702SL_AUTHENTICATIONA  _IOW(WFET_AT91_IOC_MAGIC,50, int)
#define IOCTL_FM1702SL_AUTHENTICATIONB  _IOW(WFET_AT91_IOC_MAGIC,51, int)
#define IOCTL_FM1702SL_WRITEBLOCK       _IOW(WFET_AT91_IOC_MAGIC,52, int)
#define IOCTL_FM1702SL_READBLOCK      	_IOW(WFET_AT91_IOC_MAGIC,53, int)
#define IOCTL_FM1702SL_INCREMENT      	_IOW(WFET_AT91_IOC_MAGIC,54, int)
#define IOCTL_FM1702SL_DECREMENT      	_IOW(WFET_AT91_IOC_MAGIC,55, int)
#define IOCTL_FM1702SL_RESTORE      	_IOW(WFET_AT91_IOC_MAGIC,56, int)
#define IOCTL_FM1702SL_TRANSFER      	_IOW(WFET_AT91_IOC_MAGIC,57, int)
#define IOCTL_FM1702SL_HALT      		_IOW(WFET_AT91_IOC_MAGIC,58, int)
#define IOCTL_FM1702SL_RESET			_IOW(WFET_AT91_IOC_MAGIC,59, int)
#define IOCTL_FM1702SL_LOADKEYFIFO		_IOW(WFET_AT91_IOC_MAGIC,60, int)
#define IOCTL_FM1702SL_STANDBY		    _IOW(WFET_AT91_IOC_MAGIC,61, int)
#define IOCTL_FM1702SL_WAKEUP		    _IOW(WFET_AT91_IOC_MAGIC,62, int)
#define IOC_LEDS_ON		                _IOW(WFET_AT91_IOC_MAGIC,63, int)
#define IOC_LEDS_OFF		            _IOW(WFET_AT91_IOC_MAGIC,64, int)
#define IOCTL_71M6534_RECEIVE		    _IOW(WFET_AT91_IOC_MAGIC,65, int)
#define IOCTL_71M6534_SEND		        _IOW(WFET_AT91_IOC_MAGIC,66, int)

/*
 * The following commands  originaly defined in
*  drivers/char/wfet_char_devices/wfos_flags1600u.h, should be moved here.
*  Caution: don't delete the macros below!
*  */

/* add by dq, IO for PLC */
//090805 #define IOC_PLC_POWERON     _IOW(WFET_AT91_IOC_MAGIC, 50, int)
//090805 #define IOC_PLC_POWEROFF    _IOW(WFET_AT91_IOC_MAGIC, 51, int)
#define IOC_PLC_RESET       _IOW(WFET_AT91_IOC_MAGIC, 52, int)
#define IOC_PLC_A           _IOW(WFET_AT91_IOC_MAGIC, 53, int)
#define IOC_PLC_B           _IOW(WFET_AT91_IOC_MAGIC, 54, int)
#define IOC_PLC_C           _IOW(WFET_AT91_IOC_MAGIC, 55, int)

/* add by dq, IO for BATTERY */
#define IOC_BATTERY_CHARGE_ENABLE   _IOW(WFET_AT91_IOC_MAGIC, 60, int)
#define IOC_BATTERY_CHARGE_DISABLE  _IOW(WFET_AT91_IOC_MAGIC, 61, int)
#define IOC_BATTERY_SUPPLY_ENABLE   _IOW(WFET_AT91_IOC_MAGIC, 62, int)
#define IOC_BATTERY_SUPPLY_DISABLE  _IOW(WFET_AT91_IOC_MAGIC, 63, int)
#define IOC_BATTERY_STATE           _IOR(WFET_AT91_IOC_MAGIC, 64, int)

/* add by dq, IO for Product IO */
#define IOC_PIO_BIT0        _IOW(WFET_AT91_IOC_MAGIC, 70, int)
#define IOC_PIO_BIT1        _IOW(WFET_AT91_IOC_MAGIC, 71, int)
#define IOC_PIO_BIT2        _IOW(WFET_AT91_IOC_MAGIC, 72, int)
#define IOC_PIO_BIT3        _IOW(WFET_AT91_IOC_MAGIC, 73, int)
#define IOC_PIO_BIT4        _IOW(WFET_AT91_IOC_MAGIC, 74, int)
#define IOC_PIO_BIT5        _IOW(WFET_AT91_IOC_MAGIC, 75, int)
#define IOC_PIO_BIT6        _IOW(WFET_AT91_IOC_MAGIC, 76, int)
#define IOC_PIO_BIT7        _IOW(WFET_AT91_IOC_MAGIC, 77, int)

/*add by zrm for ESAM module*/
#define IOC_ESAM_COOL_RESET             _IOW(WFET_AT91_IOC_MAGIC,67, int)
#define IOC_ESAM_WARM_RESET             _IOW(WFET_AT91_IOC_MAGIC,68, int)
#define IOC_ESAM_RELEASE                _IOW(WFET_AT91_IOC_MAGIC,69, int)

/*add by zrm for voice module*/
#define IOCTL_VOICE_MODULES_POWERON     _IOW(WFET_AT91_IOC_MAGIC,70, int)
#define IOCTL_VOICE_MODULES_POWEROFF    _IOW(WFET_AT91_IOC_MAGIC,71, int)

/* YuWF, 20170604 */
#define IOCTL_VOICE_PUP		AP89170_IOCTL_POWER_UP
#define IOCTL_VOICE_PDN		AP89170_IOCTL_POWER_DOWN
#define IOCTL_VOICE_PAUSE	AP89170_IOCTL_PAUSE
#define IOCTL_VOICE_RESUME	AP89170_IOCTL_RESUME
#define IOCTL_VOICE_PLAY	AP89170_IOCTL_PLAY
#define IOCTL_VOICE_STATUS	AP89170_IOCTL_STATUS
#define IOCTL_VOICE_PREFETCH	AP89170_IOCTL_PREFETCH
#define IOCTL_VOICE_PUP1	AP89170_IOCTL_PUP1
#define IOCTL_VOICE_PDN1	AP89170_IOCTL_PDN1

/*add by zrm for rtc module*/
#define IOCTL_DS3231_GET_TEMP           _IOW(WFET_AT91_IOC_MAGIC,72, int)

/*add by zrm for power module*/
#define IOC_POWER_STATE     _IOW(WFET_AT91_IOC_MAGIC,73, int)
#define IOC_V6513_STATE     _IOW(WFET_AT91_IOC_MAGIC,74, int)
#define IOC_VCC5V_STATE     _IOW(WFET_AT91_IOC_MAGIC,75, int)
#define IOC_VCC5V_ADC       _IOW(WFET_AT91_IOC_MAGIC,76, int)

/*add by zrm for relay module*/
#define IOC_LOADCONTROL_START     _IOW(WFET_AT91_IOC_MAGIC,77, int)
#define IOC_LOADCONTROL_POWER     _IOW(WFET_AT91_IOC_MAGIC,78, int)
#define IOC_LOADCONTROL_RELAY_ON      _IOW(WFET_AT91_IOC_MAGIC,79, int)
#define IOC_LOADCONTROL_RELAYS_ON     _IOW(WFET_AT91_IOC_MAGIC,80, int)

#define SLCD_MSG_SIZE_MAX       25
struct  slcd_msg_arg {
    size_t size;
    unsigned char *msg;
};

#define IOC_SLCD_CMD        _IOW(WFET_AT91_IOC_MAGIC,81, int)

#define IOC_PLC_MAC_ENABLE           _IOW(WFET_AT91_IOC_MAGIC, 82, int)
#define IOC_PLC_MAC_DISABLE           _IOW(WFET_AT91_IOC_MAGIC, 83, int)

#define IOC_MODEM_POWER_ON		            _IOW(WFET_AT91_IOC_MAGIC,84, int)
#define IOC_MODEM_POWER_OFF		    _IOW(WFET_AT91_IOC_MAGIC,85, int)
#define IOC_MODEM_TYPE_GET		        _IOW(WFET_AT91_IOC_MAGIC,86, int)
#define IOC_MODEM_RESET		        _IOW(WFET_AT91_IOC_MAGIC,87, int)

#define IOC_LCD_FRESH_ON		    _IOW(WFET_AT91_IOC_MAGIC,88, int)
#define IOC_LCD_FRESH_OFF		            _IOW(WFET_AT91_IOC_MAGIC,89, int)
#define IOC_LCD_BACKLIGHT_ON		            _IOW(WFET_AT91_IOC_MAGIC,90, int)
#define IOC_LCD_BACKLIGHT_OFF		        _IOW(WFET_AT91_IOC_MAGIC,91, int)
#define IOC_LCD_SET_FRESHTIME		        _IOW(WFET_AT91_IOC_MAGIC,92, int)
#define IOC_LCD_RESET		        _IOW(WFET_AT91_IOC_MAGIC,93, int)

#define IOC_MODULES_TYPE_GET		        _IOW(WFET_AT91_IOC_MAGIC,94, int)
#define IOC_BOARD_TYPE_GET		        _IOW(WFET_AT91_IOC_MAGIC,95, int)

#define IOC_LOADCONTROL_LED_ON      _IOW(WFET_AT91_IOC_MAGIC,96, int)
#define IOC_LOADCONTROL_LEDS_ON      _IOW(WFET_AT91_IOC_MAGIC,97, int)
#define IOC_LOADCONTROL_LED_OFF      _IOW(WFET_AT91_IOC_MAGIC,98, int)
#define IOC_LOADCONTROL_LEDS_OFF      _IOW(WFET_AT91_IOC_MAGIC,99, int)
#define IOC_LOADCONTROL_LEDS_MAX     _IOW(WFET_AT91_IOC_MAGIC,100, int)
#define IOC_LOADCONTROL_RELAY_OFF      _IOW(WFET_AT91_IOC_MAGIC,101, int)
#define IOC_LOADCONTROL_RELAYS_OFF     _IOW(WFET_AT91_IOC_MAGIC,102, int)
#define IOC_LOADCONTROL_RELAYS_MAX     _IOW(WFET_AT91_IOC_MAGIC,103, int)

#define IOC_PRODUCT_ID          _IOW(WFET_AT91_IOC_MAGIC,104, int)
#define IOC_WARN_BEEP           _IOW(WFET_AT91_IOC_MAGIC,105, int)
#define IOC_RTC_BAT_VOLTAGE     _IOW(WFET_AT91_IOC_MAGIC,106, int)
#define IOC_BAK_BAT_VOLTAGE     _IOW(WFET_AT91_IOC_MAGIC,107, int)

#define IOC_LOADCONTROL_RESET	_IOW(WFET_AT91_IOC_MAGIC,108, int)

#define IOC_ETHERNET_RST_CTL	_IOW(WFET_AT91_IOC_MAGIC,109, int)

#define IOC_ESAM_INTERFACE	_IOW(WFET_AT91_IOC_MAGIC,110, int)

#define IOC_ST7567_RESET        _IOW(WFET_AT91_IOC_MAGIC,111, int)
#define IOC_ST7567_SET_ADDR     _IOW(WFET_AT91_IOC_MAGIC,112, int)
#define IOC_ST7567_CLEAN_SCREEN _IOW(WFET_AT91_IOC_MAGIC,113, int)

#define IOC_PLC_ENABLE          _IOW(WFET_AT91_IOC_MAGIC,114, int)

/*check*/
#define IOC_ADC_CHANNEL_SELECT   _IOW(WFET_AT91_IOC_MAGIC,115, int)
#define IOC_TTL_MODE_SET   _IOW(WFET_AT91_IOC_MAGIC,116, int)
#define IOC_TTL_MODE_GET   _IOW(WFET_AT91_IOC_MAGIC,117, int)
#define IOC_COMMU_MODULES_STATE _IOW(WFET_AT91_IOC_MAGIC,118, int)

/* camera */
#define IOC_CAMERA_MODULES_POWER    _IOW(WFET_AT91_IOC_MAGIC,119, int)
#define IOC_CAMERA_MODULES_CABLE    _IOW(WFET_AT91_IOC_MAGIC,120, int)
#define IOC_CAMERA_MODULES_STATUS   _IOW(WFET_AT91_IOC_MAGIC,121, int)
#define IOC_CAMERA_MODULES_RESET    _IOW(WFET_AT91_IOC_MAGIC,122, int)

/* LP-wireless */
#define IOC_WIRELESS_MODULES_RESET	_IOW(WFET_AT91_IOC_MAGIC,123, int)

/* GPRS DTR */
#define IOC_COMMU_MODULES_DTR       _IOW(WFET_AT91_IOC_MAGIC,124, int)

/* crypt (non-ESAM) */
#define IOC_CRYPT_MODULE_POWER          _IOW(WFET_AT91_IOC_MAGIC, 125, int)
#define IOC_CRYPT_MODULE_RESET          _IOW(WFET_AT91_IOC_MAGIC, 126, int)

/* loadcontrol leds valid/invalid */
#define IOC_LOADCONTROL_LEDS_SET_STATE  _IOW(WFET_AT91_IOC_MAGIC, 127, int)

/* ESAM V2.0 */
#define IOC_ESAM_POWER_CONTROL              _IOW(WFET_AT91_IOC_MAGIC, 128, int)

/* LoadControl detect state */
#define IOC_LOADCONTROL_DETECT_STATE_SCAN   _IOW(WFET_AT91_IOC_MAGIC, 129, int)
#define IOC_LOADCONTROL_DETECT_STATE_GET    _IOW(WFET_AT91_IOC_MAGIC, 130, int)

#define IOC_NRSEC_POWER_CONTROL	_IOW(WFET_AT91_IOC_MAGIC, 131, int)

/* led */
#define IOC_LED_SET_DIRECTLY	_IOR(WFET_AT91_IOC_MAGIC, 132, int)
struct wfet_led_raw
{
	char chan;	/* index */
	int directly;	/* 1 - user control; 0 - kernel control */
};
#define IOC_LED_GET_COUNT	_IOR(WFET_AT91_IOC_MAGIC, 133, int)

/* sbm */
#define IOC_SBM_ALL_SLOTS_STATE_GET	_IOR(WFET_AT91_IOC_MAGIC, 134, int)
#define IOC_SBM_SB_ADDRESS		_IOR(WFET_AT91_IOC_MAGIC, 135, int)
#define IOC_SBM_STATE_GET	IOC_SBM_ALL_SLOTS_STATE_GET
#define IOC_SBM_ADDRESS_GET	IOC_SBM_SB_ADDRESS


/* LP-wireless */
#define IOC_WIRELESS_MODULES_POWER	_IOW(WFET_AT91_IOC_MAGIC, 136, int)

/* extern watchdog */
/* enum WFET_TIMER_TPYE_TAG */
#define IOC_WDT_SET_DIRECTLY		_IOR(WFET_AT91_IOC_MAGIC, 137, int)
/* enum WFET_WDT_STATUS_TAG */
#define IOC_WDT_SET_STATUS		_IOR(WFET_AT91_IOC_MAGIC, 138, int)
#define IOC_WDT_SET_TIMEOUT		_IOR(WFET_AT91_IOC_MAGIC, 139, int)

#define IOC_NRSEC_ALARM		_IOR(WFET_AT91_IOC_MAGIC, 140, int)
#define IOC_NRSEC_ATTACK	_IOR(WFET_AT91_IOC_MAGIC, 141, int)

#define IOC_PLC_DETECT		_IOW(WFET_AT91_IOC_MAGIC, 142, int)

#define IOC_BATTERY_DISCHARGE        _IOW(WFET_AT91_IOC_MAGIC, 143, int)

/* 宽带载波 */
#define IOC_BB_PLC_POWERON		_IOW(WFET_AT91_IOC_MAGIC, 144, int)
#define IOC_BB_PLC_POWEROFF		_IOW(WFET_AT91_IOC_MAGIC, 145, int)
#define IOC_BB_PLC_RESET		_IOW(WFET_AT91_IOC_MAGIC, 146, int)
#define IOC_BB_PLC_DETECT		_IOR(WFET_AT91_IOC_MAGIC, 147, int)

/* Farah capacitors */
#define IOC_CAPACITORS_CHARGE		_IOW(WFET_AT91_IOC_MAGIC, 148, int)

/* RFID */
#define IOC_RFID_POWER		_IOW(WFET_AT91_IOC_MAGIC, 149, int)
#define IOC_RFID_RESET		_IOW(WFET_AT91_IOC_MAGIC, 150, int)

/* SCM */
#define IOC_SCM_RESET		_IOW(WFET_AT91_IOC_MAGIC, 151, int)
#define IOC_SCM_POWERDOWN	_IOW(WFET_AT91_IOC_MAGIC, 152, int)

/* battery */
#define IOC_BATTERY_VOLTAGE	_IOW(WFET_AT91_IOC_MAGIC, 153, int)
#define IOC_BATTERY_VOLTAGE_CH	_IOW(WFET_AT91_IOC_MAGIC, 154, int)

/* Wi-Fi module */
#define	IOC_WIFI_POWER		_IOW(WFET_AT91_IOC_MAGIC, 155, int)

/* commu module led control */
#define	IOC_COMMU_MODULES_LED_ON	_IOW(WFET_AT91_IOC_MAGIC, 156, int)
#define	IOC_COMMU_MODULES_LED_OFF	_IOW(WFET_AT91_IOC_MAGIC, 157, int)
#define	IOC_COMMU_MODULES_HOT_CARD	_IOW(WFET_AT91_IOC_MAGIC, 158, int)
#define	IOC_COMMU_MODULES_BAT_CTRL	_IOW(WFET_AT91_IOC_MAGIC, 159, int)

#define WFET_AT91_IOC_9260_LAST          160
/*
#define WFET_AT91_IOC_MAXNR 200
*/


#endif
