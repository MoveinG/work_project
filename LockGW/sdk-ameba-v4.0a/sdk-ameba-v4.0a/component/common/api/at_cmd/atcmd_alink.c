#include <stdio.h>
#include "log_service.h"
#include "cmsis_os.h"
#include <platform/platform_stdlib.h>

#if CONFIG_ALINK
extern int alink_erase_wifi_config();
extern void alink_reset_to_factory(void *arg);
extern int alink_write_device_info(int argc, unsigned char **argv);
extern void alink_set_log_level(int argc, unsigned char **argv);

void fATCA(void *arg)
{
	int argc;
	int ret = -1;
	unsigned char *argv[MAX_ARGC] = {0};
	
	if(!arg) { 
		goto USAGE;
	}
	
	argv[0] = "k/s/l/e/r";
	argc = parse_param(arg, argv);
	if (argc == 3) {
		/*Set log level: ATCA=l, trace/debug/info/warn/fatal/none
		if set wrong, set info level by default*/
		if (!strcmp(argv[1], "l")) {
			alink_set_log_level(argc, argv);
			return;
		} else {
		/* Write device key/device secret */
			ret = alink_write_device_info(argc, argv);
			if (ret) {
				goto USAGE;
			} 
			return;
		}
	} else if (argc == 2)	{
	/* Erase wifi profile or reset user account binding : "ATCA=e" or "ATCA=r" */
		if (!strcmp(argv[1], "e")) {
			alink_erase_wifi_config();
		}else if(!strcmp(argv[1], "r")) {
			alink_reset_to_factory(NULL);
		}
	}

USAGE:	
	printf("\r\n[ATCA] Write ORDERLY device's key/secret into flash, set log level or erase wifi profile");
	printf("\r\n[ATCA] Usage: ATCA=k,xxxxxxxx\t(set device key, 20-Byte long)");
	printf("\r\n[ATCA] Usage: ATCA=s,xxxxxxxx\t(set device secret, 32-Byte long)");
	printf("\r\n[ATCA] Usage: ATCA=l,xxxx\t(set log level, trace/debug/info/warn/error/fatal/none)");
	printf("\r\n[ATCA] Usage: ATCA=e\t(erase AP  profile)");
	printf("\r\n[ATCA] Usage: ATCA=r\t(reset user account binding)");
	return;	
}
#endif

void fATCx(void *arg)
{	
   printf("\r\n fATCx\r\n");
}

log_item_t at_cloud_items[ ] = {	
#if CONFIG_ALINK
	{"ATCA", fATCA,},
#endif
	{"ATC?", fATCx,},
};
void at_cloud_init(void)
{
	log_service_add_table(at_cloud_items, sizeof(at_cloud_items)/sizeof(at_cloud_items[0]));
}

#if SUPPORT_LOG_SERVICE
log_module_init(at_cloud_init);
#endif
