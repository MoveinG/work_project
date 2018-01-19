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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>

#include <net/if.h>	      // struct ifreq
//inet_ntoa
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include "platform_config.h"
#endif

#include "alink2.0/include/alink_platform.h"

#include "wdt_api.h"
#include "sys_api.h"

#if defined(CONFIG_PLATFORM_8711B)
#define SDK_SOFTVER    "rtl-amebaz-sdk-v4.0-05"
#define MODULE_TYPE    "RTL8710BN"
#else
#define SDK_SOFTVER    "rtl-ameba1-sdk-v4.0-05"
#define MODULE_TYPE    "RTL8711AM"
#endif

#define DEV_CHIPID "rtl8188eu 12345678"


extern struct netif xnetif[NET_IF_NUM]; 

char *platform_wifi_get_mac(char mac_str[PLATFORM_MAC_LEN])
{
	uint8* tmp;
	uint8 mac[6]={0};
	
	/*get mac address*/
	tmp= LwIP_GetMAC(&xnetif[0]);
	mac[0] = tmp[0];
	mac[1] = tmp[1];
	mac[2] = tmp[2];
	mac[3] = tmp[3];
	mac[4] = tmp[4];
	mac[5] = tmp[5];

	sprintf((char *)mac_str,"%02X:%02X:%02X:%02X:%02X:%02X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
	return mac_str;
}

int platform_wifi_get_rssi_dbm(void)
{
	int rssi;
	int wifi_strength;
	wext_get_rssi(WLAN0_NAME, &rssi);
	wifi_strength = (int)rssi_to_strength(rssi);
	return wifi_strength;
}

uint32_t platform_wifi_get_ip(char ip_str[PLATFORM_IP_LEN],  const char *ifname)
{
	uint32_t ip_addr;
	uint8* tmp;
	uint8 ip[4]={0};
	char ifname_buff[IFNAMSIZ] = "wlan0";
//	strcpy(ifname_buff, "eth0")

	if((NULL == ifname || strlen(ifname) == 0) ){
		ifname = ifname_buff;
	}
	/*get IP address*/
	tmp = LwIP_GetIP(&xnetif[0]);

	ip[0] = tmp[0];
	ip[1] = tmp[1];
	ip[2] = tmp[2];
	ip[3] = tmp[3];
	sprintf((char *)ip_str,"%d.%d.%d.%d",ip[0],ip[1],ip[2],ip[3]);
	ip_addr = inet_addr(ip_str);
	return ip_addr;
}

char *platform_get_chipid(char chipid[PLATFORM_CID_LEN])
{
	//strncpy(chipid, "unknown chipid", PLATFORM_CID_LEN);
/*
	strcpy(chipid, DEV_CHIPID);
	chipid[PLATFORM_CID_LEN - 1] = '\0';

	return chipid;
*/

	const char *dev_chipid = DEV_CHIPID;
	int length;
	length = ((PLATFORM_CID_LEN-1)> strlen(dev_chipid)) ? strlen(dev_chipid) : (PLATFORM_CID_LEN -1);
	memcpy(chipid, dev_chipid, length);
	chipid[length] = '\0';

	return chipid;
}

char *platform_get_os_version(char os_ver[STR_SHORT_LEN])
{
	const char *softver = SDK_SOFTVER;
	int length;
	length = ((STR_SHORT_LEN-1)> strlen(softver)) ? strlen(softver) : (STR_SHORT_LEN-1);
	memcpy( os_ver, softver, length);
	os_ver[length] = '\0';
	alink_printf(ALINK_INFO, "[%s] RealTek SDK version: %s\n", __FUNCTION__, os_ver);
	return os_ver;
}

int platform_config_write(const char *buffer, int length)
{
	if (buffer == NULL || length < 1) {
		return ALINK_ERR;
	}
	int ret=0;
	flash_t flash_config;
	/*Erase flash before write*/
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_erase_sector(&flash_config, CONFIG_DATA_ADDRESS);
	ret = flash_stream_write(&flash_config, CONFIG_DATA_ADDRESS, length, (u8 *)buffer);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);

	if(-1 == ret) {
		alink_err_printf("write open file fail");
		return ALINK_ERR;
	}
	alink_printf(ALINK_INFO, "[%s] write config successful, ret = %d\n", __FUNCTION__, ret );
	return ALINK_OK;
}

int platform_config_read(char *buffer, int length)
{
	int ret=0;
	flash_t flash_config;

	if (buffer== NULL || length < 1) {
		return ALINK_ERR;
	}
	//Read flash direct
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	ret = flash_stream_read(&flash_config, CONFIG_DATA_ADDRESS, length, (u8 *)buffer);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
	if(-1 == ret)
	{
		alink_err_printf("read open file fail");
		return ALINK_ERR;
	}
	alink_printf(ALINK_INFO, "[%s] %d\n",__FUNCTION__, ret);
	return ALINK_OK;
}

int platform_sys_net_is_ready(void)
{

	uint8* tmp;
	uint8 ip[4]={0};


	/*get IP address*/
	tmp= LwIP_GetIP(&xnetif[0]);

	ip[0] = tmp[0];
	ip[1] = tmp[1];
	ip[2] = tmp[2];
	ip[3] = tmp[3];
	if ((ip[0] == 192 && ip[1] == 168 && ip[2] == 1 && ip[3] == 80)
		|| (ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] == 0))  {
		alink_printf(ALINK_DEBUG, "[%s] Network is not ready, ret = 0\n", __FUNCTION__); 
	} else if(RTW_SUCCESS == wifi_is_connected_to_ap( )) {
		alink_printf(ALINK_DEBUG, "[%s] Network is ready, ret = 1\n", __FUNCTION__); 		
		return 1;
	} 
	return 0;
}

void platform_sys_reboot(void)
{
	alink_printf(ALINK_INFO, "Reboot alink !!!\r\n");
	HAL_WRITE32(SYSTEM_CTRL_BASE,REG_SOC_FUNC_EN, 
		(HAL_READ32(SYSTEM_CTRL_BASE,REG_SOC_FUNC_EN)&(~BIT27)));
	sys_reset();
}

char *platform_get_module_name(char name_str[STR_SHORT_LEN])
{
	const char *module = MODULE_TYPE;
	int length;
	memset(name_str, 0, STR_SHORT_LEN);
	length = ((STR_SHORT_LEN-1)> strlen(module)) ? strlen(module) : (STR_SHORT_LEN -1);
	memcpy(name_str, module, length);
	name_str[length] = '\0';
	alink_printf(ALINK_INFO, "[%s] RealTek Module type: %s\n", __FUNCTION__, name_str);
	return name_str;
}

