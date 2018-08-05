#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>

//add by levi 2018-01-17
#include "timers.h"
TimerHandle_t ioTimerHandle;
extern void myTimerCallback(TimerHandle_t);
//end levi

extern void console_init(void);

//1111
//2222

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	if ( rtl_cryptoEngine_init() != 0 ) {
		DiagPrintf("crypto engine init failed\r\n");
	}

	/* Initialize log uart and at command service */
	//console_init();	
	ReRegisterPlatformLogUart();

	/* pre-processor of application example */
	pre_example_entry();

	/* wlan intialization */
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	wlan_network();
#endif

        //add by levi 2018-01-17
        ioTimerHandle = xTimerCreate("myTimer",
                                     100*1,
                                     pdTRUE,
                                     NULL,
                                     myTimerCallback);
        if(ioTimerHandle == NULL)
          DiagPrintf("\r\nmy timer create fail\n");
        //end levi

	/* Execute application example */
	example_entry();

    	/*Enable Schedule, Start Kernel*/
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#else
	RtlConsolTaskRom(NULL);
#endif
}
