#include <stdio.h>
#include <string.h>
#include "alink2.0/include/product.h"

//#define CONFIG_SDS_DEMO_APP_TEST

//TODO: update these product info
#ifdef CONFIG_SDS_DEMO_APP_TEST
#define product_model           "OPENALINK_LIVING_LIGHT_SDS_TEST"
#define product_key             "1L6ueddLqnRORAQ2sGOL"
#define product_secret          "qfxCLoc1yXEk9aLdx5F74tl1pdxl0W0q7eYOvvuo"
#else
#define product_model           "RFSTARDEP_SECURITY_SMARTDOOR_LOCK_GW"
#define product_key             "cvQdUEvwXu6JXU1i60Rb"
#define product_secret          "TIkdgFUHamdu0VE4flGa0RWDVm01RkuIUwhjlIOZ"
#endif
#define product_debug_key       "dpZZEpm9eBfqzK7yVeLq"
#define product_debug_secret    "THnfRRsU5vu6g6m9X6uFyAjUWflgZ0iyGjdEneKm"
#define device_key              "IzQIAJnUP4NRM8KZlPzJ"
#define device_secret           "oOlV2uiT5YFR6zKYZLKm3lqlPHSS3cGb"

/*
char *product_get_name(char name_str[PRODUCT_NAME_LEN])
{
	const char *module = "alink_product";
	int length;
	length = ((PRODUCT_NAME_LEN-1)> strlen(module)) ? strlen(module) : (PRODUCT_NAME_LEN-1);
	return strncpy(name_str, module, length);
}
*/
extern int  alink_flash_stream_read(uint32_t address, uint32_t len, uint8_t * data);

char *product_get_name(char name_str[PRODUCT_NAME_LEN])
{
	return strncpy(name_str, "alink_product", PRODUCT_NAME_LEN);
}

char *product_get_version(char ver_str[PRODUCT_VERSION_LEN])
{
	return strncpy(ver_str, "1.0", PRODUCT_VERSION_LEN);
}

char *product_get_model(char model_str[PRODUCT_MODEL_LEN])
{
	return strncpy(model_str, product_model, PRODUCT_MODEL_LEN);
}

char *product_get_key(char key_str[PRODUCT_KEY_LEN])
{
	return strncpy(key_str, product_key, PRODUCT_KEY_LEN);
}

char *product_get_device_key(char key_str[DEVICE_KEY_LEN])
{
	char *key = NULL;
	key = key_str;
        
        //add by levi 2018-01-17
        //alink_flash_erase_sector(CONFIG_DEVICE_INFO);
        //alink_flash_stream_write(CONFIG_DEVICE_INFO, DEVICE_KEY_LEN, device_key);
        //end levi
        
	alink_flash_stream_read(CONFIG_DEVICE_INFO, DEVICE_KEY_LEN, key);
	if(*((uint32_t *)key) == ~0x0) {
		alink_printf(ALINK_WARNING, "\nDevice has no key, please write them by \"ATCA\" and then reset.");
		return NULL;
	}
	key_str[DEVICE_KEY_LEN-1] = '\0';
	return key;
}

char *product_get_device_secret(char secret_str[DEVICE_SECRET_LEN])
{
	char *secret = NULL;
	secret = secret_str;
        
        //add by levi 2018-01-17
        //alink_flash_stream_write(CONFIG_DEVICE_INFO + DEVICE_KEY_LEN, DEVICE_SECRET_LEN, device_secret);
        //end levi
        
	alink_flash_stream_read(CONFIG_DEVICE_INFO + DEVICE_KEY_LEN, DEVICE_SECRET_LEN, secret);
	if(*((uint32_t *)secret) == ~0x0) {
		alink_printf(ALINK_WARNING, "\nDevice has no secret, please write them by \"ATCA\" and then reset.");
		return NULL;
	}
	secret_str[DEVICE_SECRET_LEN-1] = '\0';
	return secret;
}

char *product_get_secret(char secret_str[PRODUCT_SECRET_LEN])
{
	return strncpy(secret_str, product_secret, PRODUCT_SECRET_LEN);
}

char *product_get_debug_key(char key_str[PRODUCT_KEY_LEN])
{
	return strncpy(key_str, product_debug_key, PRODUCT_KEY_LEN);
}

char *product_get_debug_secret(char secret_str[PRODUCT_SECRET_LEN])
{
	return strncpy(secret_str, product_debug_secret, PRODUCT_SECRET_LEN);
}

char *product_get_sn(char sn_str[PRODUCT_SN_LEN])
{
	char mac[PLATFORM_MAC_LEN];
	platform_wifi_get_mac(mac);
	return strncpy(sn_str, mac, PRODUCT_SN_LEN);
}
