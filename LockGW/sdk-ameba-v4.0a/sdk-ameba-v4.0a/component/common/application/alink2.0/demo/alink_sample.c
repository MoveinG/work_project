/*
 * Copyright (c) 2014-2016 Alibaba Group. All rights reserved.
 *
 * Alibaba Group retains all right, title and interest (including all
 * intellectual property rights) in and to this computer program, which is
 * protected by applicable intellectual property laws.  Unless you have
 * obtained a separate written license from Alibaba Group., you are not
 * authorized to utilize all or a part of this computer program for any
 * purpose (including reproduction, distribution, modification, and
 * compilation into object code), and you must immediately destroy or
 * return to Alibaba Group all copies of this computer program.  If you
 * are licensed by Alibaba Group, your rights to utilize this computer
 * program are limited by the terms of that license.  To obtain a license,
 * please contact Alibaba Group.
 *
 * This computer program contains trade secrets owned by Alibaba Group.
 * and, unless unauthorized by Alibaba Group in writing, you agree to
 * maintain the confidentiality of this computer program and related
 * information and to not disclose this computer program and related
 * information to any other person or entity.
 *
 * THIS COMPUTER PROGRAM IS PROVIDED AS IS WITHOUT ANY WARRANTIES, AND
 * Alibaba Group EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED,
 * INCLUDING THE WARRANTIES OF MERCHANTIBILITY, FITNESS FOR A PARTICULAR
 * PURPOSE, TITLE, AND NONINFRINGEMENT.
 */
#ifdef PLATFORM_LINUX
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <unistd.h>
#endif

#include <stdlib.h>
#include "alink2.0/include/alink_export.h"
#include "alink2.0/include/json_parser.h"
#include "alink2.0/include/alink_platform.h"
#include "timers.h"

/* raw data device means device post byte stream to cloud,
 * cloud translate byte stream to json value by lua script
 * for each product model, vendor need to sumbit a lua script
 * doing this job
 *
 * undefine RAW_DATA_DEVICE, sample will post json string to cloud
 */
//#define RAW_DATA_DEVICE

#define Method_PostData    "postDeviceData"
#define Method_PostRawData "postDeviceRawData"
#define Method_GetAlinkTime "getAlinkTime"

#define CONFIG_SDS_KEY_SECRET_CHECK

#define PostDataFormat      "{\"ErrorCode\":{\"value\":\"%d\"},\"Hue\":{\"value\":\"%d\"},\"Luminance\":{\"value\":\"%d\"},\"Switch\":{\"value\":\"%d\"},\"WorkMode\":{\"value\":\"%d\"}}"
#define post_data_buffer_size    (512)

//add by levi 2018-01-18
#define TestPostFormat      "{\"ErrorCode\":{\"value\":\"%d\"},\"LockAlarm\":{\"value\":\"%d\"},\"LockDoor\":{\"value\":\"%d\"},\"LockState\":{\"value\":\"%d\"},\"OpenDoor\":{\"value\":\"%d\"}}"
//end levi

/* activate sample */
char active_data_tx_buffer[128];
#define ActivateDataFormat    "{\"ErrorCode\": { \"value\": \"%d\" }}"

#ifndef RAW_DATA_DEVICE
static char post_data_buffer[post_data_buffer_size];
#else
static char raw_data_buffer[post_data_buffer_size];

/* rawdata byte order
 *
 * rawdata[0] = 0xaa;
 * rawdata[1] = 0x07;
 * rawdata[2] = device.power;
 * rawdata[3] = device.work_mode;
 * rawdata[4] = device.temp_value;
 * rawdata[5] = device.light_value;
 * rawdata[6] = device.time_delay;
 * rawdata[7] = 0x55;
 */
#define RAW_DATA_SIZE           (8)
uint8_t device_state_raw_data[RAW_DATA_SIZE] = {
    0xaa, 0x07, 1, 8, 10, 50, 10, 0x55
};
#endif

enum {
    ATTR_ERRORCODE_INDEX,
    ATTR_HUE_INDEX,
    ATTR_LUMINANCE_INDEX,
    ATTR_SWITCH_INDEX,
    ATTR_WORKMODE_INDEX,
    ATTR_MAX_NUMS
};
#define DEVICE_ATTRS_NUM   (ATTR_MAX_NUMS)

/*watchdog timeout,in ms*/
 #define ALINK_WDG_TIMEOUT ((20)*(1000))


#ifndef TCP_LOCAL_PORT_RANGE_START
/* From http://www.iana.org/assignments/port-numbers:
   "The Dynamic and/or Private Ports are those from 49152 through 65535" */
#define TCP_LOCAL_PORT_RANGE_START        0xc000
#define TCP_LOCAL_PORT_RANGE_END          0xffff
#endif

extern long alink_fd;
#ifdef CONFIG_GPIO_TASK
_sema gpio_exception_sema;
#endif

int device_state[] = {0, 10, 50, 1, 2};/* default value */
char *device_attr[] = {
    "ErrorCode",
    "Hue",
    "Luminance",
    "Switch",
    "WorkMode",
    NULL
};

static int need_report = 1; /* force to report when device login */

void cloud_connected(void) { printf("alink cloud connected!\n"); }
void cloud_disconnected(void) { printf("alink cloud disconnected!\n"); }
int activate_button_pressed(void);

extern int wlan_wrtie_reconnect_data_to_flash(u8 *data, uint32_t len);

#ifndef RAW_DATA_DEVICE
void cloud_get_device_status(char *json_buffer) { need_report = 1; }

int cloud_set_device_status(char *json_buffer)
{
	int attr_len = 0, value_len = 0, value = 0, i;
	char *value_str = NULL, *attr_str = NULL;

	need_report = 1;

	for (i = 0; device_attr[i]; i++) {
	    attr_str = json_get_value_by_name(json_buffer, strlen(json_buffer),
	            device_attr[i], &attr_len, NULL);
	    value_str = json_get_value_by_name(attr_str, attr_len,
	            "value", &value_len, NULL);

	    if (value_str && value_len > 0) {
	        char last_char = *(value_str+value_len);
	        *(value_str + value_len) = 0;
	        value = atoi(value_str);
	        *(value_str + value_len) = last_char;
	        device_state[i] = value;
	    }
	}

	return 0;
}

/* helper function */
/*
int alink_post_data(char *json_params)
{
        return alink_report(Method_PostData, json_params);
}
*/

#else
static char a2x(char ch)
{
	switch (ch) {
	    case '1':
	        return 1;
	    case '2':
	        return 2;
	    case '3':
	        return 3;
	    case '4':
	        return 4;
	    case '5':
	        return 5;
	    case '6':
	        return 6;
	    case '7':
	        return 7;
	    case '8':
	        return 8;
	    case '9':
	        return 9;
	    case 'A':
	    case 'a':
	        return 10;
	    case 'B':
	    case 'b':
	        return 11;
	    case 'C':
	    case 'c':
	        return 12;
	    case 'D':
	    case 'd':
	        return 13;
	    case 'E':
	    case 'e':
	        return 14;
	    case 'F':
	    case 'f':
	        return 15;
	    default:
	        break;;
	}

	return 0;
}

int uart_send(const uint8_t *raw_data, int raw_data_len)
{
	//TODO: implement uart send here
	int i;
	for (i = 0; i < raw_data_len; i++)
	    printf("%02x ", raw_data[i]);

	printf("\n");
	return 0;
}

int raw_data_unserialize(char *json_buffer, uint8_t *raw_data, int *raw_data_len)
{
	int attr_len = 0, i = 0;
	char *attr_str = NULL;

//	assert(json_buffer && raw_data && raw_data_len);

	attr_str = json_get_value_by_name(json_buffer, strlen(json_buffer),
	        "rawData", &attr_len, NULL);

	if (!attr_str || !attr_len || attr_len > *raw_data_len * 2)
	    return -1;

	for (i = 0; i < attr_len; i += 2) {
	    raw_data[i / 2] = a2x(attr_str[i]) << 4;
	    raw_data[i / 2] += a2x(attr_str[i + 1]);
	}

	raw_data[i / 2] = '\0';
	*raw_data_len = i / 2;

	return 0;
}

int cloud_get_device_raw_data(char *json_buffer)
{
	int ret = 0, raw_data_len = RAW_DATA_SIZE;
	uint8_t raw_data[RAW_DATA_SIZE] = { 0 };

	need_report = 1;

	ret = raw_data_unserialize(json_buffer, raw_data, &raw_data_len);
	if (!ret)
	    return uart_send(raw_data, raw_data_len);
	else
	    return -1;
}

int cloud_set_device_raw_data(char *json_buffer)
{
	int ret = 0, raw_data_len = RAW_DATA_SIZE;
	uint8_t raw_data[RAW_DATA_SIZE] = { 0 };

	need_report = 1;

	ret = raw_data_unserialize(json_buffer, raw_data, &raw_data_len);
	if (!ret) {
	    /* update device state */
	    memcpy(device_state_raw_data, raw_data, raw_data_len);
	    return uart_send(raw_data, raw_data_len);
	} else
	    return -1;
}

int alink_post_raw_data(uint8_t *byte_stream, int len)
{
	    int i, size;
#define RawDataHeader   "{\"rawData\":\""
#define RawDataTail     "\", \"length\":\"%d\"}"

	    size = strlen(RawDataHeader);
	    strncpy(raw_data_buffer, RawDataHeader, post_data_buffer_size);
	    for (i = 0; i < len; i++) {
	       size += snprintf(raw_data_buffer + size,
	               post_data_buffer_size - size, "%02X", byte_stream[i]);
	    }

	    size += snprintf(raw_data_buffer + size,
	            post_data_buffer_size - size, RawDataTail, len * 2);
	    alink_printf(ALINK_INFO, "[%s] %s", __FUNCTION__, raw_data_buffer );
	    return alink_report(Method_PostRawData, raw_data_buffer);
}
#endif

static uint32_t work_time = 1000; //default work time 1s
void main_loop(void)
{
	uint32_t time_start, time_end;
	time_start = platform_get_time_ms();
        
	do {
		if (need_report) {
#ifdef RAW_DATA_DEVICE
			/*
			* Note: post data to cloud,
			* use sample alink_post_raw_data()
			* or alink_post()
			*/
			/* sample for raw data device */
			alink_post_raw_data(device_state_raw_data, RAW_DATA_SIZE);

#else
			/* sample for json data device */
			snprintf(post_data_buffer, post_data_buffer_size, PostDataFormat,
				device_state[ATTR_ERRORCODE_INDEX],
				device_state[ATTR_HUE_INDEX],
				device_state[ATTR_LUMINANCE_INDEX],
				device_state[ATTR_SWITCH_INDEX],
				device_state[ATTR_WORKMODE_INDEX]);

			alink_report(Method_PostData, post_data_buffer);
			alink_printf(ALINK_DEBUG, "[%s] %s", __FUNCTION__, post_data_buffer );
#endif

			need_report = 0;
		}
		platform_msleep(100);
		time_end = platform_get_time_ms();
	} while ((time_start + work_time) > time_end);
}

int alink_get_time(unsigned int *utc_time)
{
#define TIME_STR_LEN    (32)
	char buf[TIME_STR_LEN] = { 0 }, *attr_str;
	int size = TIME_STR_LEN, attr_len = 0;
	int ret;

	ret = alink_query(Method_GetAlinkTime, "{}", buf, &size);
	if (!ret) {
	    attr_str = json_get_value_by_name(buf, size, "time", &attr_len, NULL);
	    if (attr_str && utc_time) {
	        sscanf(attr_str, "%u", utc_time);
	    }
	}

	return ret;
}

void helper_api_test(void)
{
	unsigned int time;
	int ret = alink_get_time(&time);
	//    assert(!ret);

	alink_printf(ALINK_INFO, "Get alink utc time: %d\n", time);
}

static void wdg_timer_handle(void *para)
{
	watchdog_refresh();
}

/*
 * @return   status: Success:1 or Failure: Others.
 */
int  alink_flash_stream_read(uint32_t address, uint32_t len, uint8_t * data)
{
	flash_t flash;
	int ret;
	
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	ret = flash_stream_read(&flash, address, len, data);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);

	return ret;
}

/*
 * @return   status: Success:1 or Failure: Others.
 */
int  alink_flash_stream_write(uint32_t address, uint32_t len, uint8_t * data)
{
	flash_t flash;
	int ret;
	
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	ret = flash_stream_write(&flash, address, len, data);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);

	return ret;
}

/*
 * @return   none.
 */
void  alink_flash_erase_sector(uint32_t address)
{
	flash_t flash;
	
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_erase_sector(&flash, address);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);

	return;
}

/* write device key/secret into flash
 * argv[1] = "key" or "secret";
 * argv[2] = value;
 * write flash addr = CONFIG_DEVICE_INFO
 * @return   status: Success:0 or Failure: -1.
 */
int  alink_write_device_info(int argc, unsigned char **argv)
{
	// flags ensure write ORDERLY
	static int32_t device_flag	= 0;
	if (!strcmp(argv[1], "k")) {
		if(strlen(argv[2]) != 20) {
			alink_printf(ALINK_WARNING, "\"key\" must be 20-byte long\n");
			return -1;
		}
		alink_flash_erase_sector(CONFIG_DEVICE_INFO);
		//sizeof(secret) == 20B
		if (1 == alink_flash_stream_write(CONFIG_DEVICE_INFO, 21, argv[2])) {
			device_flag = 1;
			alink_printf(ALINK_INFO, "write \"key\" successfully\n");	
		} else {
			alink_printf(ALINK_WARNING, "write \"key\" fail\n");
			return -1;
		}
	} else if(!strcmp(argv[1], "s")) {
		if(strlen(argv[2]) != 32) {
			alink_printf(ALINK_WARNING, "\"secret\" must be 32-byte long\n");
			return -1;
		}
		if(device_flag != 1) {
			alink_printf(ALINK_WARNING, "write \"key\" first !");
			return -1;
		}
		if(1 == alink_flash_stream_write(CONFIG_DEVICE_INFO + 21, 33, argv[2])) {
			alink_printf(ALINK_INFO, "write \"secret\" successfully\n");	
		} else {
			alink_printf(ALINK_WARNING, "write \"secret\" fail\nl");
			return -1;
		}
	} else {
		alink_printf(ALINK_WARNING, "wrong operation\n");
		return -1;
	}
	
	return 0;
}

int rtl_erase_wifi_config_data()
{
	LwIP_DHCP(0, DHCP_RELEASE_IP);
	LwIP_DHCP(0, DHCP_STOP);
	vTaskDelay(10);
	fATWD(NULL);
	vTaskDelay(20);
	alink_flash_erase_sector(FAST_RECONNECT_DATA);
	alink_printf(ALINK_DEBUG, "%s: clean ap-config data",__FUNCTION__ );
	return 0;
}

void alink_set_log_level(int argc, unsigned char **argv)
{

	static char log_level = ALINK_LL_DEBUG;
	if (!strcmp(argv[2], "trace")) {
	        log_level = ALINK_LL_TRACE;
	} else if (!strcmp(argv[2], "debug")) {
	        log_level = ALINK_LL_DEBUG;
	} else if (!strcmp(argv[2], "info")) {
	        log_level = ALINK_LL_INFO;
	} else if (!strcmp(argv[2], "warn")) {
	        log_level = ALINK_LL_WARN;
	} else if (!strcmp(argv[2], "error")) {
	        log_level = ALINK_LL_ERROR;
	} else if (!strcmp(argv[2], "fatal")) {
	        log_level = ALINK_LL_FATAL;
	} else if (!strcmp(argv[2], "none")) {
	        log_level = ALINK_LL_NONE;
	} else {
	        log_level = ALINK_LL_INFO;
		alink_printf(ALINK_WARNING, "wrong operation : %s, set INFO log level by default\n", argv[2]);
	}
	alink_printf(ALINK_INFO, "set log level: %s!\n", argv[2]);
	alink_set_loglevel(log_level);
	return;
}

int alink_clean_config_data()
{
	/*Erase alink-sdk data*/
	alink_flash_erase_sector(CONFIG_DATA_ADDRESS);
	alink_printf(ALINK_DEBUG, "%s: clean alink-sdk data",__FUNCTION__ );
	return 0;
}

void alink_reset_to_factory(void *arg)
{
	int ret = -1;
	ret = alink_factory_reset();
	if (ret < 0) {
		alink_err_printf("Failed to remove device information, ret = %d\n", ret);
	} else {
		alink_printf(ALINK_INFO, "Remove all device information, ret = %d\n", ret);
	}
	//close tcp connect socket
	platform_tcp_close((void *)alink_fd);
	alink_clean_config_data();
	rtl_erase_wifi_config_data();
	platform_sys_reboot();
}

u16 alink_get_tcp_new_port()
{
	uint16_t port;
	alink_printf(ALINK_DEBUG, "[%s] Get time = %d\n", __FUNCTION__, xTaskGetTickCount());
	srand(xTaskGetTickCount());
	port = rand() % (TCP_LOCAL_PORT_RANGE_END - TCP_LOCAL_PORT_RANGE_START) + TCP_LOCAL_PORT_RANGE_START;
	return port;
}

void alink_erase_wifi_config()
{
	//close tcp connect socket
	platform_tcp_close((void *)alink_fd);
	//Erase alink config flash
	rtl_erase_wifi_config_data();
	//restart
	platform_sys_reboot();
}

static void alink_watchdog_init()
{
	//RTL_TIMER *wdg_timer;
	TimerHandle_t *wdg_timer;

	/*wdg init*/
	watchdog_init(ALINK_WDG_TIMEOUT);
	watchdog_start();

	/*start a timer to handle wdg*/
	//wdg_timer = RtlTimerCreate("alink_wdg_timer", (u32)(5000), wdg_timer_handle, NULL, 1);
	wdg_timer = xTimerCreate((const char *)"alink_wdg_timer", (5000/portTICK_RATE_MS), pdTRUE, NULL, wdg_timer_handle);
	//RtlTimerStart(wdg_timer,0);	
	xTimerStart(wdg_timer, 0);
}

//add by levi 2018-01-17
int buttonTimeCount = 0;
char post_data_tx_buffer[128];
extern TimerHandle_t ioTimerHandle;

void myTimerCallback( TimerHandle_t pxTimer )
{
        gpio_t obj;
        obj.pin = BUTTON;
        
        if(gpio_read(&obj))
        {
          //alink_printf(ALINK_INFO, "GPIO push button !\n");
          buttonTimeCount++;
          if(buttonTimeCount == 50)
          {
            buttonTimeCount = 0;
            xTimerStop( pxTimer, 0 );
            alink_erase_wifi_config();
          }
        }
        else
        {
          buttonTimeCount = 0;
          xTimerStop( pxTimer, 0 );
          //alink_printf(ALINK_INFO, "GPIO button release!\n");
        }
}

void alink_post_device_state(void)
{
    int errorCode = 0;
    int lockAlarm = 8;
    int lockDoor  = 0;
    int lockState = 2;
    int openDoor  = 0;
    memset(post_data_tx_buffer,0,128);
    sprintf(post_data_tx_buffer, TestPostFormat,errorCode,lockAlarm,lockDoor,lockState,openDoor);
	alink_printf(ALINK_INFO, "[%s] send:%s\n", __FUNCTION__, post_data_tx_buffer);
    alink_report(Method_PostData, (char *)post_data_tx_buffer);
}
//end levi

int activate_button_pressed_n_times(void)
{
	int count = 1;

	while (count) {
		--count;
		activate_button_pressed();
	}
	need_report = 1;
        
    //add by levi 2018-01-17
    if(xTimerStart( ioTimerHandle, 0 ) != pdPASS )
    {
		alink_printf(ALINK_INFO, "\r\nmy timer can't start!\n");
    }
    //end levi
//	main_loop();
	return 0;

}


static void alink_reset_gpio_irq_handler(uint32_t id, gpio_irq_event event)
{
#ifdef CONFIG_GPIO_TASK
	alink_printf(ALINK_DEBUG, "GPIO push button !\n");
	xSemaphoreGive(gpio_exception_sema);
#else
	timer timer_handler;
	memset(&timer_handler, 0, sizeof(_timer));
	rtw_init_timer(&timer_handler, NULL, activate_button_pressed_n_times, NULL, "NULL_timer");
	rtw_set_timer(&timer_handler, 0);
#endif
}

static void alink_reset_gpio_init()
{
	gpio_t	gpio_softap_reset_button;
	gpio_irq_t	gpioirq_softap_reset_button;

	gpio_irq_init(&gpioirq_softap_reset_button, BUTTON, alink_reset_gpio_irq_handler, (uint32_t)(&gpio_softap_reset_button));
	gpio_irq_set(&gpioirq_softap_reset_button, IRQ_RISE, 1);//add by levi 2018-01-17 //IRQ_FALL
	gpio_irq_enable(&gpioirq_softap_reset_button);
}

void alink_dev_init()
{
#ifdef CONFIG_GPIO_TASK
	gpio_exception_sema = xSemaphoreCreateCounting(300, 0); 
#endif
	alink_reset_gpio_init();
	/*watchdog : 20s*/
	alink_watchdog_init();
}

void awss_demo(void)
{
#if 0
    char ssid[PLATFORM_MAX_SSID_LEN] = { 0 };
    char passwd[PLATFORM_MAX_PASSWD_LEN] = { 0 };
#define WLAN_CONNECTION_TIMEOUT     (30 * 1000) //30 seconds

    /* after system booting, read ssid & passwd from flash */
    vendor_read_ssid_passwd_from_flash(ssid, passwd);
#endif
	int ret = -1;
#if !(CONFIG_EXAMPLE_WLAN_FAST_CONNECT == 1)
	rtl_var_init();
#endif
	ret = awss_start(); /* Note: awss_start() will block until success */
	if (0 == ret) {
		alink_printf(ALINK_DEBUG, "connect AP  success\n");
	} else {
		if (-1 == ret) {
			alink_err_printf ("Fail to get ssid & passwd");
		} else {
			alink_err_printf("DHCP fail");
		}
	}
}

int activate_button_pressed(void)
{
	int errorcode = 0;
	if (0 == errorcode){
	     errorcode = 1;
	 }else {
	     errorcode = 0;
	 }
    //add by levi 2018-01-17
    memset(active_data_tx_buffer,0,128);
    userUartPrintf("button_pressed\r\n",strlen("button_pressed\r\n"));
    //alink_clean_config_data();
    //rtl_erase_wifi_config_data();
    //end levi
	sprintf(active_data_tx_buffer, ActivateDataFormat, errorcode);
	alink_printf(ALINK_INFO, "[%s] send:%s\n", __FUNCTION__, active_data_tx_buffer);
    
	return alink_report(Method_PostData, (char *)active_data_tx_buffer);
}


enum SERVER_ENV {
	DAILY = 0,
	SANDBOX,
	ONLINE,
	DEFAULT
};
const char *env_str[] = {"daily", "sandbox", "online", "default"};
void usage(void)
{
	printf("\nalink_sample -e enviroment -d enable_dead_loop -l log_level\n");
	printf("\t -e alink server environment, 'daily', 'sandbox' or 'online'(default)\n");
	printf("\t -d dead loop, never return\n");
	printf("\t -l log level, trace/debug/info/warn/error/fatal/none\n");
	printf("\t -h show help text\n");
}

static int env = ONLINE;
static char dead_loop = 1;
static char log_level = ALINK_LL_DEBUG;

//extern char *optarg;
#if 0
void parse_opt(int argc, char *argv[])
{
    char ch;

    while ((ch = getopt(argc, argv, "e:d::l:h")) != -1) {
        switch (ch) {
        case 'e':
            if (!strcmp(optarg, "daily"))
                env = DAILY;
            else if (!strcmp(optarg, "sandbox"))
                env = SANDBOX;
            else if (!strcmp(optarg, "online"))
                env = ONLINE;
            else {
                env = ONLINE;
                printf("unknow opt %s, use default env\n", optarg);
            }
            break;
        case 'd':
            dead_loop = 1;
            break;
        case 'l':
            if (!strcmp(optarg, "trace"))
                log_level = ALINK_LL_TRACE;
            else if (!strcmp(optarg, "debug"))
                log_level = ALINK_LL_DEBUG;
            else if (!strcmp(optarg, "info"))
                log_level = ALINK_LL_INFO;
            else if (!strcmp(optarg, "warn"))
                log_level = ALINK_LL_WARN;
            else if (!strcmp(optarg, "error"))
                log_level = ALINK_LL_ERROR;
            else if (!strcmp(optarg, "fatal"))
                log_level = ALINK_LL_FATAL;
            else if (!strcmp(optarg, "none"))
                log_level = ALINK_LL_NONE;
            else
                log_level = ALINK_LL_INFO;
            break;
        case 'h':
        default:
            usage();
	    return;
 //           exit(0);
        }
    }

    printf("alink server: %s, dead_loop: %s, log level: %d\n",
            env_str[env], dead_loop ? "true" : "false", log_level);
}
#endif

int alink_load_wifi_config(struct wlan_fast_reconnect	* data)
{
	int ret;
	uint8    pscan_config;
	uint8    scan_channel;
	int dhcp_retry = 1;	
	int connect_retry = 0;
	
	pscan_config = PSCAN_ENABLE;
	scan_channel	= (data->channel) & 0xFF;
	if(data->security_type == RTW_SECURITY_WEP_PSK) {
		/*wifi->password_len*/
		if(sizeof(data->psk_passphrase) == 10)
		{
			u32 p[5];
			u8 pwd[6], i = 0; 
			sscanf((const char*)data->psk_passphrase, "%02x%02x%02x%02x%02x", &p[0], &p[1], &p[2], &p[3], &p[4]);
			for(i=0; i< 5; i++)
				pwd[i] = (u8)p[i];
			pwd[5] = '\0';
			memset(data->psk_passphrase, 0, 65);
			strcpy((char*)data->psk_passphrase, (char*)pwd);
		} else if(sizeof(data->psk_passphrase) == 26) {
			u32 p[13];
			u8 pwd[14], i = 0;
			sscanf((const char*)data->psk_passphrase, "%02x%02x%02x%02x%02x%02x%02x"\
				"%02x%02x%02x%02x%02x%02x", &p[0], &p[1], &p[2], &p[3], &p[4],\
				&p[5], &p[6], &p[7], &p[8], &p[9], &p[10], &p[11], &p[12]);
			for(i=0; i< 13; i++)
				pwd[i] = (u8)p[i];
			pwd[13] = '\0';
			memset(data->psk_passphrase, 0, 65);
			strcpy((char*)data->psk_passphrase, (char*)pwd);
		}
	}

	wifi_disable_powersave();//add to close powersave

	alink_printf(ALINK_INFO, "Set pscan channel = %d\n", scan_channel); 
	if(wifi_set_pscan_chan(&scan_channel, &pscan_config, 1) < 0) {
		alink_err_printf("wifi set partial scan channel fail");
	//	return 0;
	}

	do{
		ret = wifi_connect((char*)data->psk_essid,
					  (rtw_security_t)data->security_type,
					  (char*)data->psk_passphrase,
					  (int)strlen((char const *)data->psk_essid),
					  (int)strlen((char const *)data->psk_passphrase),
					  0,
					  NULL);
		if (ret == ALINK_OK) {
Try_again:		
			ret = LwIP_DHCP(0, DHCP_START);	
			if(ret != DHCP_ADDRESS_ASSIGNED) {
				if(dhcp_retry){
					alink_err_printf( "DHCP failed. Goto try again!\n\r");
					dhcp_retry--;
					goto Try_again;
				} else {
					alink_err_printf("DHCP failed. \n\r");
				}
			} else {	
				alink_printf(ALINK_INFO, "[%s] wifi connect ok !\n", __func__);
				if (connect_retry) {
					wlan_wrtie_reconnect_data_to_flash((u8 *)data, sizeof(struct wlan_fast_reconnect));
				}
			}
		} else {
			++connect_retry;
			alink_err_printf("wifi connect fail !");
			if (connect_retry) {
				if(get_ap_security_mode((char*)data->psk_essid, &data->security_type, &scan_channel) != 0) {
					scan_channel = 0;
					data->security_type = RTW_SECURITY_WPA2_AES_PSK;
					alink_printf(ALINK_WARNING, "Warning : unknow security type, default set to WPA2_AES");
				} else {
					if ((data->channel)  != (uint32_t) scan_channel ) {
						(data->channel)  = (uint32_t) scan_channel;
						alink_printf(ALINK_INFO, "Reset pscan channel = %d\n", scan_channel); 
						u8 pscan_config = PSCAN_ENABLE;
						if(scan_channel > 0 && scan_channel < 14) {
							if(wifi_set_pscan_chan(&scan_channel, &pscan_config, 1) < 0) {
								alink_printf(ALINK_WARNING, "wifi set partial scan channel fail\n");
							}	
						} 
					}
				}
			}
		}	
	}while(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS);
	
	return ALINK_OK;
}

#ifdef CONFIG_GPIO_TASK
void gpio_exception_thread(void *param)
{
	while(xSemaphoreTake(gpio_exception_sema, portMAX_DELAY) == pdTRUE) {
		activate_button_pressed_n_times();
		platform_msleep(200); //add by levi 2018-01-17 //2000
		gpio_exception_sema = xSemaphoreCreateCounting(300, 0); 
	}
	vTaskDelete(NULL);
}
#endif

/* Determine device  key and secret exist or not. 
 *
 * @para: pinfo
 * ret: exist:              0
 *	    not exsit:      -1
 */
 #ifdef CONFIG_SDS_KEY_SECRET_CHECK
static int is_device_info_exist()
{
	char key[21] = {0};
	char secret[33] = {0};
	char *pdevice_key = key;
	char *pdevice_secret = secret;
	if (product_get_device_key(pdevice_key) == NULL || product_get_device_secret(pdevice_secret) == NULL) {
		return -1;
	}
	alink_printf(ALINK_INFO, "\nDevice key: %s", key);
	alink_printf(ALINK_INFO, "\nDevice secret: %s", secret);
	return 0;
}
#endif

void alink_example_thread(int argc, char *argv[])
{
	alink_printf(ALINK_INFO, "\n [%s] alink server: %s, work_time: %d ms,  log level: %d\n",
	        __FUNCTION__, env_str[env], work_time, log_level);
	alink_set_loglevel(log_level);
	alink_dev_init();

#ifdef CONFIG_SDS_KEY_SECRET_CHECK
	//Determine device  key and secret exist or not. 
	int ret = -1;
	ret = is_device_info_exist();
	if (ret) {
		goto ERROR;
	}
#endif
	
#ifdef CONFIG_GPIO_TASK
	if(xTaskCreate((TaskFunction_t)gpio_exception_thread, ((const char*)"gpio handle"), 384, NULL, tskIDLE_PRIORITY + 5, NULL) != pdPASS) {
		alink_err_printf("xTaskCreate failed\n");	
	}
#endif
	/* reload or config wifi*/
	struct wlan_fast_reconnect	*data;
	data = (struct wlan_fast_reconnect *)rtw_zmalloc(sizeof(struct wlan_fast_reconnect));
	if (data) {
		flash_t 	flash;
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_stream_read(&flash, FAST_RECONNECT_DATA, sizeof(struct wlan_fast_reconnect), (uint8_t *)data);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);

		/* reload ap profile*/
		if((*((uint32_t *) data) != ~0x0) && strlen(data->psk_essid)) {
			alink_printf(ALINK_INFO, "Read AP profile from flash : ssid = %s, pwd = %s, ssid length = %d, pwd length = %d, channel = %d, security =%d\n", 
				data->psk_essid, data->psk_passphrase, strlen(data->psk_essid), strlen(data->psk_passphrase), data->channel, data->security_type);
			alink_load_wifi_config(data);
		} else {
			alink_printf(ALINK_INFO, "No AP profile read from FLASH, start alink...\n");
			awss_demo();
		}
#if CONFIG_AUTO_RECONNECT
			wifi_set_autoreconnect(1);
#endif
	
		if(data) {
			rtw_mfree((u8*)data, sizeof(sizeof(struct wlan_fast_reconnect)));
		}
	} else {
		alink_err_printf("malloc failed !");
		vTaskDelete(NULL);
	}

	if (env == SANDBOX) {
		alink_enable_sandbox_mode();
	} else if (env == DAILY) {
		alink_enable_daily_mode(NULL, 0);
	}

	alink_register_callback(ALINK_CLOUD_CONNECTED, (void *)&cloud_connected);
	alink_register_callback(ALINK_CLOUD_DISCONNECTED, (void *)&cloud_disconnected);
	/*
	 * NOTE: register ALINK_GET/SET_DEVICE_STATUS or ALINK_GET/SET_DEVICE_RAWDATA
	 */
#ifdef RAW_DATA_DEVICE
	/*
	 * TODO: before using callback ALINK_GET/SET_DEVICE_RAWDATA,
	 * submit product_model_xxx.lua script to ALINK cloud.
	 * ALINKTEST_LIVING_LIGHT_SMARTLED_LUA is done with it.
	 */
	alink_register_callback(ALINK_GET_DEVICE_RAWDATA, (void *)&cloud_get_device_raw_data);
	alink_register_callback(ALINK_SET_DEVICE_RAWDATA, (void *)&cloud_set_device_raw_data);
#else
	alink_register_callback(ALINK_GET_DEVICE_STATUS, (void *)&cloud_get_device_status);
	alink_register_callback(ALINK_SET_DEVICE_STATUS, (void *)&cloud_set_device_status);
#endif

    /* call alink_start() after system got IP address */
	alink_start();
	alink_wait_connect(ALINK_WAIT_FOREVER);
    /* activate device after alink connnected, see activate_button_pressed */
/*
	int count = 1;
	while (count) {
		count--;
		platform_msleep(1000);
		activate_button_pressed();
	}
*/
	alink_set_loglevel(ALINK_LL_INFO);

	helper_api_test(); 
loop:
	main_loop();

	if (dead_loop)
		goto loop;

	/*‘›∆¡±Œ∏¥Œª¥˙¬Î£¨±‹√‚≤‚ ‘÷–ŒÛ÷ÿ∆Ù*/
	//alink_factory_reset();
	alink_end();
ERROR:
	vTaskDelete(NULL);
}

typedef int (*init_done_ptr)(void);
extern init_done_ptr p_wlan_init_done_callback;

int start_alink()
{
	xTaskHandle app_task_handle = NULL;
       
	p_wlan_init_done_callback = NULL;
	if(xTaskCreate((TaskFunction_t)alink_example_thread, (char const *)"Alink_entry", 1024*3, NULL, tskIDLE_PRIORITY + 5, &app_task_handle) != pdPASS) {
		alink_err_printf("xTaskCreate failed\n");	
	}
	alink_printf(ALINK_INFO, "start alink:app_task_handle = %p\n", app_task_handle);
        
        //add by levi 2018-01-18
        myUartadapter_init();
        //end levi
	return 0;
}

void example_alink(void)
{
	//have to be called after wlan init done.
	p_wlan_init_done_callback = start_alink;
}


