#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\port.c"































































 



 

 
#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\intrinsics.h"








 




#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"
 
 

 


  #pragma system_include







 























 






#line 67 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"











 

#line 99 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"









#line 15 "D:\\IAR-87xx\\arm\\inc\\c\\intrinsics.h"


  #pragma system_include




 









#pragma language=save
#pragma language=extended

__intrinsic __nounwind void    __no_operation(void);

__intrinsic __nounwind void    __disable_interrupt(void);
__intrinsic __nounwind void    __enable_interrupt(void);

typedef unsigned long __istate_t;

__intrinsic __nounwind __istate_t __get_interrupt_state(void);
__intrinsic __nounwind void __set_interrupt_state(__istate_t);



 
__intrinsic __nounwind unsigned long __get_PSR( void );
__intrinsic __nounwind unsigned long __get_IPSR( void );
__intrinsic __nounwind unsigned long __get_MSP( void );
__intrinsic __nounwind void          __set_MSP( unsigned long );
__intrinsic __nounwind unsigned long __get_PSP( void );
__intrinsic __nounwind void          __set_PSP( unsigned long );
__intrinsic __nounwind unsigned long __get_PRIMASK( void );
__intrinsic __nounwind void          __set_PRIMASK( unsigned long );
__intrinsic __nounwind unsigned long __get_CONTROL( void );
__intrinsic __nounwind void          __set_CONTROL( unsigned long );



 
__intrinsic __nounwind unsigned long __get_FAULTMASK( void );
__intrinsic __nounwind void          __set_FAULTMASK(unsigned long);
__intrinsic __nounwind unsigned long __get_BASEPRI( void );
__intrinsic __nounwind void          __set_BASEPRI( unsigned long );

#line 74 "D:\\IAR-87xx\\arm\\inc\\c\\intrinsics.h"

__intrinsic __nounwind void __disable_fiq(void);
__intrinsic __nounwind void __enable_fiq(void);


 

__intrinsic __nounwind unsigned long __SWP( unsigned long, volatile unsigned long * );
__intrinsic __nounwind unsigned char __SWPB( unsigned char, volatile unsigned char * );

typedef unsigned long __ul;





 
__intrinsic __nounwind void          __MCR( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1, __ul src,
                                 unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 );
__intrinsic __nounwind unsigned long __MRC( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1,
                                 unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 );
__intrinsic __nounwind void          __MCR2( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1, __ul src,
                                  unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 );
__intrinsic __nounwind unsigned long __MRC2( unsigned __constrange(0,15) coproc, unsigned __constrange(0,8) opcode_1,
                                  unsigned __constrange(0,15) CRn, unsigned __constrange(0,15) CRm, unsigned __constrange(0,8) opcode_2 );

 
__intrinsic __nounwind void __LDC( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul const *src);
__intrinsic __nounwind void __LDCL( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul const *src);
__intrinsic __nounwind void __LDC2( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul const *src);
__intrinsic __nounwind void __LDC2L( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul const *src);

 
__intrinsic __nounwind void __STC( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul *dst);
__intrinsic __nounwind void __STCL( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul *dst);
__intrinsic __nounwind void __STC2( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul *dst);
__intrinsic __nounwind void __STC2L( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul *dst);

 
__intrinsic __nounwind void __LDC_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul const *src,
                              unsigned __constrange(0,255) option);

__intrinsic __nounwind void __LDCL_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul const *src,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __LDC2_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul const *src,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __LDC2L_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul const *src,
                                unsigned __constrange(0,255) option);

 
__intrinsic __nounwind void __STC_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul *dst,
                              unsigned __constrange(0,255) option);

__intrinsic __nounwind void __STCL_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul *dst,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __STC2_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul *dst,
                               unsigned __constrange(0,255) option);

__intrinsic __nounwind void __STC2L_noidx( unsigned __constrange(0,15) coproc, unsigned __constrange(0,15) CRn, volatile __ul *dst,
                                unsigned __constrange(0,255) option);


 
__intrinsic __nounwind unsigned long __get_APSR( void );
__intrinsic __nounwind void          __set_APSR( unsigned long );






 
__intrinsic __nounwind unsigned long __get_FPSCR( void );
__intrinsic __nounwind void __set_FPSCR( unsigned long );

 
__intrinsic __nounwind unsigned char __CLZ( unsigned long );

 

__intrinsic __nounwind signed long __QADD( signed long, signed long );
__intrinsic __nounwind signed long __QDADD( signed long, signed long );
__intrinsic __nounwind signed long __QSUB( signed long, signed long );
__intrinsic __nounwind signed long __QDSUB( signed long, signed long );

__intrinsic __nounwind signed long __QDOUBLE( signed long );

__intrinsic __nounwind int         __QFlag( void );
__intrinsic __nounwind void __reset_Q_flag( void );


__intrinsic __nounwind int         __QCFlag( void );
__intrinsic __nounwind void __reset_QC_flag( void );

__intrinsic __nounwind signed long __SMUL( signed short, signed short );

 
__intrinsic __nounwind unsigned long __REV( unsigned long );
__intrinsic __nounwind signed long __REVSH( short );

__intrinsic __nounwind unsigned long __REV16( unsigned long );
__intrinsic __nounwind unsigned long __RBIT( unsigned long );

__intrinsic __nounwind unsigned char  __LDREXB( volatile unsigned char const * );
__intrinsic __nounwind unsigned short __LDREXH( volatile unsigned short const * );
__intrinsic __nounwind unsigned long  __LDREX ( volatile unsigned long const * );
__intrinsic __nounwind unsigned long long __LDREXD( volatile unsigned long long const * );

__intrinsic __nounwind unsigned long  __STREXB( unsigned char, volatile unsigned char * );
__intrinsic __nounwind unsigned long  __STREXH( unsigned short, volatile unsigned short * );
__intrinsic __nounwind unsigned long  __STREX ( unsigned long, volatile unsigned long * );
__intrinsic __nounwind unsigned long  __STREXD( unsigned long long, volatile unsigned long long * );

__intrinsic __nounwind void __CLREX( void );

__intrinsic __nounwind void __SEV( void );
__intrinsic __nounwind void __WFE( void );
__intrinsic __nounwind void __WFI( void );
__intrinsic __nounwind void __YIELD( void );

__intrinsic __nounwind void __PLI( volatile void const * );
__intrinsic __nounwind void __PLD( volatile void const * );
__intrinsic __nounwind void __PLDW( volatile void const * );

__intrinsic __nounwind   signed long __SSAT     (unsigned long val,
                                      unsigned int __constrange( 1, 32 ) sat );
__intrinsic __nounwind unsigned long __USAT     (unsigned long val,
                                      unsigned int __constrange( 0, 31 ) sat );




 
__intrinsic __nounwind unsigned long __SEL( unsigned long op1, unsigned long op2 );

__intrinsic __nounwind unsigned long __SADD8    (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SADD16   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SSUB8    (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SSUB16   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SADDSUBX (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SSUBADDX (unsigned long pair1, unsigned long pair2);

__intrinsic __nounwind unsigned long __SHADD8   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SHADD16  (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SHSUB8   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SHSUB16  (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SHADDSUBX(unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __SHSUBADDX(unsigned long pair1, unsigned long pair2);

__intrinsic __nounwind unsigned long __QADD8    (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __QADD16   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __QSUB8    (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __QSUB16   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __QADDSUBX (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __QSUBADDX (unsigned long pair1, unsigned long pair2);

__intrinsic __nounwind unsigned long __UADD8    (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UADD16   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __USUB8    (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __USUB16   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UADDSUBX (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __USUBADDX (unsigned long pair1, unsigned long pair2);

__intrinsic __nounwind unsigned long __UHADD8   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UHADD16  (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UHSUB8   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UHSUB16  (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UHADDSUBX(unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UHSUBADDX(unsigned long pair1, unsigned long pair2);

__intrinsic __nounwind unsigned long __UQADD8   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UQADD16  (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UQSUB8   (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UQSUB16  (unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UQADDSUBX(unsigned long pair1, unsigned long pair2);
__intrinsic __nounwind unsigned long __UQSUBADDX(unsigned long pair1, unsigned long pair2);

__intrinsic __nounwind unsigned long __USAD8(unsigned long x, unsigned long y );
__intrinsic __nounwind unsigned long __USADA8(unsigned long x, unsigned long y,
                                   unsigned long acc );

__intrinsic __nounwind unsigned long __SSAT16   (unsigned long pair,
                                      unsigned int __constrange( 1, 16 ) sat );
__intrinsic __nounwind unsigned long __USAT16   (unsigned long pair,
                                      unsigned int __constrange( 0, 15 ) sat );

__intrinsic __nounwind long __SMUAD (unsigned long x, unsigned long y);
__intrinsic __nounwind long __SMUSD (unsigned long x, unsigned long y);
__intrinsic __nounwind long __SMUADX(unsigned long x, unsigned long y);
__intrinsic __nounwind long __SMUSDX(unsigned long x, unsigned long y);

__intrinsic __nounwind long __SMLAD (unsigned long x, unsigned long y, long sum);
__intrinsic __nounwind long __SMLSD (unsigned long x, unsigned long y, long sum);
__intrinsic __nounwind long __SMLADX(unsigned long x, unsigned long y, long sum);
__intrinsic __nounwind long __SMLSDX(unsigned long x, unsigned long y, long sum);

__intrinsic __nounwind long long __SMLALD (unsigned long pair1,
                                 unsigned long pair2,
                                 long long acc);

__intrinsic __nounwind long long __SMLALDX(unsigned long pair1,
                                 unsigned long pair2,
                                 long long acc);

__intrinsic __nounwind long long __SMLSLD (unsigned long pair1,
                                 unsigned long pair2,
                                 long long acc);

__intrinsic __nounwind long long __SMLSLDX(unsigned long pair1,
                                 unsigned long pair2,
                                 long long acc);

__intrinsic __nounwind unsigned long __PKHBT(unsigned long x,
                                  unsigned long y,
                                  unsigned __constrange(0,31) count);
__intrinsic __nounwind unsigned long __PKHTB(unsigned long x,
                                  unsigned long y,
                                  unsigned __constrange(0,32) count);

__intrinsic __nounwind long __SMLABB(unsigned long x, unsigned long y, long acc);
__intrinsic __nounwind long __SMLABT(unsigned long x, unsigned long y, long acc);
__intrinsic __nounwind long __SMLATB(unsigned long x, unsigned long y, long acc);
__intrinsic __nounwind long __SMLATT(unsigned long x, unsigned long y, long acc);

__intrinsic __nounwind long __SMLAWB(long x, unsigned long y, long acc);
__intrinsic __nounwind long __SMLAWT(long x, unsigned long y, long acc);

__intrinsic __nounwind long __SMMLA (long x, long y, long acc);
__intrinsic __nounwind long __SMMLAR(long x, long y, long acc);
__intrinsic __nounwind long __SMMLS (long x, long y, long acc);
__intrinsic __nounwind long __SMMLSR(long x, long y, long acc);

__intrinsic __nounwind long __SMMUL (long x, long y);
__intrinsic __nounwind long __SMMULR(long x, long y);

__intrinsic __nounwind long __SMULBB(unsigned long x, unsigned long y);
__intrinsic __nounwind long __SMULBT(unsigned long x, unsigned long y);
__intrinsic __nounwind long __SMULTB(unsigned long x, unsigned long y);
__intrinsic __nounwind long __SMULTT(unsigned long x, unsigned long y);

__intrinsic __nounwind long __SMULWB(long x, unsigned long y);
__intrinsic __nounwind long __SMULWT(long x, unsigned long y);

__intrinsic __nounwind long __SXTAB (long x, unsigned long y);
__intrinsic __nounwind long __SXTAH (long x, unsigned long y);
__intrinsic __nounwind unsigned long __UXTAB (unsigned long x, unsigned long y);
__intrinsic __nounwind unsigned long __UXTAH (unsigned long x, unsigned long y);

__intrinsic __nounwind unsigned long long __UMAAL(unsigned long x,
                                       unsigned long y,
                                       unsigned long a,
                                       unsigned long b);

__intrinsic __nounwind long long __SMLALBB(unsigned long x,
                                 unsigned long y,
                                 long long acc);

__intrinsic __nounwind long long __SMLALBT(unsigned long x,
                                 unsigned long y,
                                 long long acc);

__intrinsic __nounwind long long __SMLALTB(unsigned long x,
                                 unsigned long y,
                                 long long acc);

__intrinsic __nounwind long long __SMLALTT(unsigned long x,
                                 unsigned long y,
                                 long long acc);

__intrinsic __nounwind unsigned long __UXTB16(unsigned long x);
__intrinsic __nounwind unsigned long __UXTAB16(unsigned long acc, unsigned long x);

__intrinsic __nounwind unsigned long __SXTB16(unsigned long x);
__intrinsic __nounwind unsigned long __SXTAB16(unsigned long acc, unsigned long x);

__intrinsic __nounwind unsigned long __SASX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __SSAX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __SHASX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __SHSAX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __QASX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __QSAX(unsigned long, unsigned long) ;

__intrinsic __nounwind unsigned long __UASX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __USAX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __UHASX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __UHSAX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __UQASX(unsigned long, unsigned long) ;
__intrinsic __nounwind unsigned long __UQSAX(unsigned long, unsigned long) ;


 
__intrinsic __nounwind void __DMB(void);
__intrinsic __nounwind void __DSB(void);
__intrinsic __nounwind void __ISB(void);




#pragma language=restore





#line 72 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\port.c"

 
#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"































































 






 
#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\stddef.h"
 
 




  #pragma system_include


#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"
 
 

 


  #pragma system_include







 























 






#line 67 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"

#line 11 "D:\\IAR-87xx\\arm\\inc\\c\\stddef.h"
#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"
 
 





  #pragma system_include


#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"
 
 

 


  #pragma system_include







 























 






#line 67 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"

#line 12 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

                 









  


                 




















 


   
#line 59 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"





#line 70 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

                 
#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"



























 





  #pragma system_include


 
#line 1 "D:\\IAR-87xx\\arm\\INC\\c\\DLib_Config_Normal.h"
 
 





  #pragma system_include


 

#line 40 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"
   
#line 47 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"

 
#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Product.h"




   #pragma system_include







 




 


 



 



 


 




 
#line 45 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Product.h"

 


 


 






 




 


 


 
#line 99 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Product.h"







#line 51 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"











 












 
























 













 























































































































 






 














 
























 


















 
















 








 















 

#line 351 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"













 













 












 














 












 












 












 












 

















 

















 






















 















 








 














 

#line 566 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"












 












 












 












 












 












 












 












 












 










 







 












 







 








 



















































 
















 




#line 812 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"





 

#line 826 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"


   
#line 836 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"

#line 844 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"
  







 









 








 







 






 

#line 899 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"




 







 






 















 

   
#line 943 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"









 

  #pragma language = save 
  #pragma language = extended





  #pragma language = restore










 








 







 
#line 997 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Defaults.h"





 







#line 73 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"











                 




















 
#line 147 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"





                 


 




 
 
#line 170 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

 




 






 






 
#line 233 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"











                 
#line 292 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"









#line 308 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"








#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\xencoding_limits.h"
 
 





  #pragma system_include


#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"
 
 

 


  #pragma system_include







 























 






#line 67 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"

#line 12 "D:\\IAR-87xx\\arm\\inc\\c\\xencoding_limits.h"
#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"
 
 

#line 707 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"




 
#line 13 "D:\\IAR-87xx\\arm\\inc\\c\\xencoding_limits.h"

                                 


#line 24 "D:\\IAR-87xx\\arm\\inc\\c\\xencoding_limits.h"




#line 42 "D:\\IAR-87xx\\arm\\inc\\c\\xencoding_limits.h"

                                 














#line 317 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"



                 

                 
#line 335 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

                 
#line 360 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

                 
                 




#line 382 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"


                 

                                 







  #pragma language=save
  #pragma language=extended
  typedef long long _Longlong;
  typedef unsigned long long _ULonglong;
  #pragma language=restore
#line 405 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"






  typedef unsigned short int _Wchart;
  typedef unsigned short int _Wintt;


#line 424 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

#line 432 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

                 


typedef signed int  _Ptrdifft;
typedef unsigned int     _Sizet;

 


                 
#line 454 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"
  typedef _VA_LIST __Va_list;



__intrinsic __nounwind void __iar_Atexit(void (*)(void));



  typedef struct
  {        
    unsigned int _Wchar;
    unsigned int _State;
  } _Mbstatet;
#line 477 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"










typedef struct
{        

  _Longlong _Off;     



  _Mbstatet _Wstate;
} _Fpost;







                 

#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Threads.h"













 





  #pragma system_include






 






















































































 

 



#line 157 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Threads.h"

  
 

   





  


#line 176 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Threads.h"





#line 187 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Threads.h"





  #pragma language=save 
  #pragma language=extended
  __intrinsic __nounwind void __iar_dlib_perthread_initialize(void  *);
  __intrinsic __nounwind void  *__iar_dlib_perthread_allocate(void);
  __intrinsic __nounwind void __iar_dlib_perthread_destroy(void);
  __intrinsic __nounwind void __iar_dlib_perthread_deallocate(void  *);









  #pragma segment = "__DLIB_PERTHREAD" 
  #pragma segment = "__DLIB_PERTHREAD_init" 


























#line 242 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Threads.h"

   
  void  *__iar_dlib_perthread_access(void  *);
  #pragma language=restore



























     
  









   






  





  
  typedef void *__iar_Rmtx;
  

  
  __intrinsic __nounwind void __iar_system_Mtxinit(__iar_Rmtx *m);
  __intrinsic __nounwind void __iar_system_Mtxdst(__iar_Rmtx *m);
  __intrinsic __nounwind void __iar_system_Mtxlock(__iar_Rmtx *m);
  __intrinsic __nounwind void __iar_system_Mtxunlock(__iar_Rmtx *m);

  __intrinsic __nounwind void __iar_file_Mtxinit(__iar_Rmtx *m);
  __intrinsic __nounwind void __iar_file_Mtxdst(__iar_Rmtx *m);
  __intrinsic __nounwind void __iar_file_Mtxlock(__iar_Rmtx *m);
  __intrinsic __nounwind void __iar_file_Mtxunlock(__iar_Rmtx *m);

  
 
  __intrinsic __nounwind void __iar_clearlocks(void);


#line 323 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Threads.h"

  





  

#line 341 "D:\\IAR-87xx\\arm\\inc\\c\\DLib_Threads.h"

  typedef unsigned _Once_t;



  













#line 506 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

#line 516 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

                 
#line 524 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"


                 

  
  
    
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Locale(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_StaticGuard(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock(unsigned int);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Locale(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_StaticGuard(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock(unsigned int);

  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Initdynamicfilelock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Dstdynamicfilelock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Lockdynamicfilelock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlockdynamicfilelock(__iar_Rmtx *);
  
  
#line 564 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

                 
#line 572 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

#line 690 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"

                 





#line 705 "D:\\IAR-87xx\\arm\\inc\\c\\yvals.h"






 
#line 12 "D:\\IAR-87xx\\arm\\inc\\c\\stddef.h"
#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\ysizet.h"
 
 





  #pragma system_include


#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"
 
 

 


  #pragma system_include







 























 






#line 67 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"

#line 12 "D:\\IAR-87xx\\arm\\inc\\c\\ysizet.h"



                 




typedef _Sizet size_t;




typedef unsigned int __data_size_t;











#line 13 "D:\\IAR-87xx\\arm\\inc\\c\\stddef.h"



                 








                 




  typedef _Ptrdifft ptrdiff_t;




  typedef _Wchart wchar_t;




#line 49 "D:\\IAR-87xx\\arm\\inc\\c\\stddef.h"





 
#line 73 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"













 
#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\stdint.h"
 
 




  #pragma system_include


#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"
 
 

 


  #pragma system_include







 























 






#line 67 "D:\\IAR-87xx\\arm\\inc\\c\\ycheck.h"

#line 11 "D:\\IAR-87xx\\arm\\inc\\c\\stdint.h"



 

  typedef signed char   int8_t;
  typedef unsigned char uint8_t;



  typedef signed short int   int16_t;
  typedef unsigned short int uint16_t;



  typedef signed int   int32_t;
  typedef unsigned int uint32_t;



  #pragma language=save
  #pragma language=extended
  typedef signed long long int   int64_t;
  typedef unsigned long long int uint64_t;
  #pragma language=restore



 
typedef signed char   int_least8_t;
typedef unsigned char uint_least8_t;

typedef signed short int   int_least16_t;
typedef unsigned short int uint_least16_t;

typedef signed int   int_least32_t;
typedef unsigned int uint_least32_t;

 

  #pragma language=save
  #pragma language=extended
  typedef signed long long int int_least64_t;
  #pragma language=restore


  #pragma language=save
  #pragma language=extended
  typedef unsigned long long int uint_least64_t;
  #pragma language=restore




 
typedef signed int   int_fast8_t;
typedef unsigned int uint_fast8_t;

typedef signed int   int_fast16_t;
typedef unsigned int uint_fast16_t;

typedef signed int   int_fast32_t;
typedef unsigned int uint_fast32_t;


  #pragma language=save
  #pragma language=extended
  typedef signed long long int int_fast64_t;
  #pragma language=restore


  #pragma language=save
  #pragma language=extended
  typedef unsigned long long int uint_fast64_t;
  #pragma language=restore


 
#pragma language=save
#pragma language=extended
typedef signed long long int   intmax_t;
typedef unsigned long long int uintmax_t;
#pragma language=restore


 
typedef signed long int   intptr_t;
typedef unsigned long int uintptr_t;

 



typedef int __data_intptr_t; typedef unsigned int __data_uintptr_t;


 






























































































 

































#line 258 "D:\\IAR-87xx\\arm\\inc\\c\\stdint.h"




 
#line 88 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"





 
#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\inc\\FreeRTOSConfig.h"


































































 

#line 1 "D:\\IAR-87xx\\arm\\inc\\c\\stdint.h"
 
 
#line 235 "D:\\IAR-87xx\\arm\\inc\\c\\stdint.h"

#line 258 "D:\\IAR-87xx\\arm\\inc\\c\\stdint.h"




 
#line 73 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\inc\\FreeRTOSConfig.h"
extern uint32_t SystemCoreClock; 
#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\inc\\platform_autoconf.h"


 




 



 








 
#line 32 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\inc\\platform_autoconf.h"



 
#line 42 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\inc\\platform_autoconf.h"



 
#line 52 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\inc\\platform_autoconf.h"



 
#line 62 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\inc\\platform_autoconf.h"



 





 





 





 





 





 





 





 





 





 





 




 





 







 





 






 





 




 




 




 







 




 




 




 






 




 




 




 




 








 
#line 76 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\inc\\FreeRTOSConfig.h"











 

#line 108 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\inc\\FreeRTOSConfig.h"






#line 127 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\inc\\FreeRTOSConfig.h"







extern void freertos_pre_sleep_processing(unsigned int *expected_idle_time);
extern void freertos_post_sleep_processing(unsigned int *expected_idle_time);
extern int  freertos_ready_to_sleep();

 


 


 




 






                                                        



 





 
#line 176 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\inc\\FreeRTOSConfig.h"

 
#line 184 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\inc\\FreeRTOSConfig.h"



 





 




 


 





#line 95 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"

 
#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\projdefs.h"































































 







 
typedef void (*TaskFunction_t)( void * );

 










 








#line 98 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"

 
#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\portable.h"































































 



 







 










































































































































































#line 254 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\portable.h"

#line 262 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\portable.h"







#line 276 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\portable.h"











































 
#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\portmacro.h"































































 

















 

 
#line 92 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\portmacro.h"

typedef uint32_t StackType_t;
typedef long BaseType_t;
typedef unsigned long UBaseType_t;





	typedef uint32_t TickType_t;


 

 



 

 
extern void vPortYield( void );





 

 






	 




	 



	 





 

 
extern void vPortEnterCritical( void );
extern void vPortExitCritical( void );
extern uint32_t ulPortSetInterruptMask( void );
extern void vPortClearInterruptMask( uint32_t ulNewMask );

#line 157 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\portmacro.h"
 

 

	extern void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime );



 



 


 






 




 
#pragma diag_suppress=Pe191
#pragma diag_suppress=Pa082







#line 322 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\portable.h"






























#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\mpu_wrappers.h"































































 





 
#line 144 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\mpu_wrappers.h"










#line 353 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\portable.h"






 



	StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters ) ;


 
typedef struct HeapRegion
{
	uint8_t *pucStartAddress;
	size_t xSizeInBytes;
} HeapRegion_t;











 
void vPortDefineHeapRegions( const HeapRegion_t * const pxHeapRegions );




 
void *pvPortMalloc( size_t xSize ) ;
void vPortFree( void *pv ) ;
void vPortInitialiseBlocks( void ) ;
size_t xPortGetFreeHeapSize( void ) ;
size_t xPortGetMinimumEverFreeHeapSize( void ) ;




 
BaseType_t xPortStartScheduler( void ) ;





 
void vPortEndScheduler( void ) ;







 











#line 101 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"





 















































































































































#line 256 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"

 


























































 

	
 




	
 




	
 




	
 














	
 




	



 




	


 




	


 




	


 







 





























































































































































































































#line 633 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"






























































































 




#line 748 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\FreeRTOS.h"

	
 












#line 75 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\port.c"
#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\task.h"































































 









#line 1 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\list.h"































































 



























 
































 









 
struct xLIST_ITEM
{
	 TickType_t xItemValue;			 
	struct xLIST_ITEM *  pxNext;		 
	struct xLIST_ITEM *  pxPrevious;	 
	void * pvOwner;										 
	void *  pvContainer;				 
};
typedef struct xLIST_ITEM ListItem_t;					 

struct xMINI_LIST_ITEM
{
	 TickType_t xItemValue;
	struct xLIST_ITEM *  pxNext;
	struct xLIST_ITEM *  pxPrevious;
};
typedef struct xMINI_LIST_ITEM MiniListItem_t;



 
typedef struct xLIST
{
	 UBaseType_t uxNumberOfItems;
	ListItem_t *  pxIndex;		 
	MiniListItem_t xListEnd;						 
} List_t;







 








 








 









 








 







 







 







 








 




 





















 
#line 280 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\list.h"

















 










 







 






 











 
void vListInitialise( List_t * const pxList );









 
void vListInitialiseItem( ListItem_t * const pxItem );











 
void vListInsert( List_t * const pxList, ListItem_t * const pxNewListItem );



















 
void vListInsertEnd( List_t * const pxList, ListItem_t * const pxNewListItem );













 
UBaseType_t uxListRemove( ListItem_t * const pxItemToRemove );







#line 75 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\task.h"







 















 
typedef void * TaskHandle_t;




 
typedef BaseType_t (*TaskHookFunction_t)( void * );

 
typedef enum
{
	eRunning = 0,	 
	eReady,			 
	eBlocked,		 
	eSuspended,		 
	eDeleted		 
} eTaskState;



 
typedef struct xTIME_OUT
{
	BaseType_t xOverflowCount;
	TickType_t  xTimeOnEntering;
} TimeOut_t;



 
typedef struct xMEMORY_REGION
{
	void *pvBaseAddress;
	uint32_t ulLengthInBytes;
	uint32_t ulParameters;
} MemoryRegion_t;



 
typedef struct xTASK_PARAMETERS
{
	TaskFunction_t pvTaskCode;
	const char * const pcName;	 
	uint16_t usStackDepth;
	void *pvParameters;
	UBaseType_t uxPriority;
	StackType_t *puxStackBuffer;
	MemoryRegion_t xRegions[ 1 ];
} TaskParameters_t;


 
typedef struct xTASK_STATUS
{
	TaskHandle_t xHandle;			 
	const char *pcTaskName;			   
	UBaseType_t xTaskNumber;		 
	eTaskState eCurrentState;		 
	UBaseType_t uxCurrentPriority;	 
	UBaseType_t uxBasePriority;		 
	uint32_t ulRunTimeCounter;		 



	uint16_t usStackHighWaterMark;	 
} TaskStatus_t;

 
typedef enum
{
	eAbortSleep = 0,		 
	eStandardSleep,			 
	eNoTasksWaitingTimeout	 
} eSleepModeStatus;






 









 













 













 









 









 




 







 
















































































 




































































 















































 
void vTaskAllocateMPURegions( TaskHandle_t xTask, const MemoryRegion_t * const pxRegions ) ;







































 
void vTaskDelete( TaskHandle_t xTaskToDelete ) ;



 














































 
void vTaskDelay( const TickType_t xTicksToDelay ) ;

























































 
void vTaskDelayUntil( TickType_t * const pxPreviousWakeTime, const TickType_t xTimeIncrement ) ;













































 
UBaseType_t uxTaskPriorityGet( TaskHandle_t xTask ) ;
















 
eTaskState eTaskGetState( TaskHandle_t xTask ) ;








































 
void vTaskPrioritySet( TaskHandle_t xTask, UBaseType_t uxNewPriority ) ;

















































 
void vTaskSuspend( TaskHandle_t xTaskToSuspend ) ;















































 
void vTaskResume( TaskHandle_t xTaskToResume ) ;



























 
BaseType_t xTaskResumeFromISR( TaskHandle_t xTaskToResume ) ;



 



























 
void vTaskStartScheduler( void ) ;






















































 
void vTaskEndScheduler( void ) ;

















































 
void vTaskSuspendAll( void ) ;




















































 
BaseType_t xTaskResumeAll( void ) ;



 









 
TickType_t xTaskGetTickCount( void ) ;














 
TickType_t xTaskGetTickCountFromISR( void ) ;












 
UBaseType_t uxTaskGetNumberOfTasks( void ) ;












 
char *pcTaskGetTaskName( TaskHandle_t xTaskToQuery ) ;  



















 
UBaseType_t uxTaskGetStackHighWaterMark( TaskHandle_t xTask ) ;






 
#line 1141 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\project\\realtek_amebaz_va0_example\\EWARM-RELEASE\\..\\..\\..\\component\\os\\freertos\\freertos_v8.1.2\\Source\\include\\task.h"











 
BaseType_t xTaskCallApplicationTaskHook( TaskHandle_t xTask, void *pvParameter ) ;







 
TaskHandle_t xTaskGetIdleTaskHandle( void );

































































































 
UBaseType_t uxTaskGetSystemState( TaskStatus_t * const pxTaskStatusArray, const UBaseType_t uxArraySize, uint32_t * const pulTotalRunTime );













































 
void vTaskList( char * pcWriteBuffer ) ;  




















































 
void vTaskGetRunTimeStats( char *pcWriteBuffer ) ;  



 















 
BaseType_t xTaskIncrementTick( void ) ;































 
void vTaskPlaceOnEventList( List_t * const pxEventList, const TickType_t xTicksToWait ) ;
void vTaskPlaceOnUnorderedEventList( List_t * pxEventList, const TickType_t xItemValue, const TickType_t xTicksToWait ) ;











 
void vTaskPlaceOnEventListRestricted( List_t * const pxEventList, const TickType_t xTicksToWait ) ;
























 
BaseType_t xTaskRemoveFromEventList( const List_t * const pxEventList ) ;
BaseType_t xTaskRemoveFromUnorderedEventList( ListItem_t * pxEventListItem, const TickType_t xItemValue ) ;








 
void vTaskSwitchContext( void ) ;




 
TickType_t uxTaskResetEventItemValue( void ) ;



 
TaskHandle_t xTaskGetCurrentTaskHandle( void ) ;



 
void vTaskSetTimeOutState( TimeOut_t * const pxTimeOut ) ;




 
BaseType_t xTaskCheckForTimeOut( TimeOut_t * const pxTimeOut, TickType_t * const pxTicksToWait ) ;




 
void vTaskMissedYield( void ) ;




 
BaseType_t xTaskGetSchedulerState( void ) ;




 
void vTaskPriorityInherit( TaskHandle_t const pxMutexHolder ) ;




 
BaseType_t xTaskPriorityDisinherit( TaskHandle_t const pxMutexHolder ) ;




 
BaseType_t xTaskGenericCreate( TaskFunction_t pxTaskCode, const char * const pcName, const uint16_t usStackDepth, void * const pvParameters, UBaseType_t uxPriority, TaskHandle_t * const pxCreatedTask, StackType_t * const puxStackBuffer, const MemoryRegion_t * const xRegions ) ;  



 
UBaseType_t uxTaskGetTaskNumber( TaskHandle_t xTask ) ;




 
void vTaskSetTaskNumber( TaskHandle_t xTask, const UBaseType_t uxHandle ) ;








 
void vTaskStepTick( const TickType_t xTicksToJump ) ;














 
eSleepModeStatus eTaskConfirmSleepModeStatus( void ) ;




 
void *pvTaskIncrementMutexHeldCount( void );








#line 76 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\port.c"














	
 



 




 









 
#line 119 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\port.c"

 


 



 



 




 




 
static UBaseType_t uxCriticalNesting = 0xaaaaaaaa;





 
void vPortSetupTimerInterrupt( void );



 
void xPortSysTickHandler( void );



 
extern void vPortStartFirstTask( void );



 
extern void vPortEnableVFP( void );



 
static void prvTaskExitError( void );

 



 

	static uint32_t ulTimerCountsForOneTick = 0;





 

	static uint32_t xMaximumPossibleSuppressedTicks = 0;





 

	static uint32_t ulStoppedTimerCompensation = 0;






 






 



 
StackType_t *pxPortInitialiseStack( StackType_t *pxTopOfStack, TaskFunction_t pxCode, void *pvParameters )
{
	
 

	
 
	pxTopOfStack--;

	*pxTopOfStack = ( 0x01000000 );	 
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) pxCode;	 
	pxTopOfStack--;
	*pxTopOfStack = ( StackType_t ) prvTaskExitError;	 

	 
	pxTopOfStack -= 5;	 
	*pxTopOfStack = ( StackType_t ) pvParameters;	 

	
 
	pxTopOfStack--;
	*pxTopOfStack = ( 0xfffffffd );

	pxTopOfStack -= 8;	 

	return pxTopOfStack;
}
 

static void prvTaskExitError( void )
{
	




 
	;
	ulPortSetInterruptMask();
	for( ;; );
}
 



 
BaseType_t xPortStartScheduler( void )
{
#line 304 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\port.c"

	 
	( * ( ( volatile uint32_t * ) 0xe000ed20 ) ) |= ( ( ( uint32_t ) ( 0x0f << (8 - 4) ) ) << 16UL );
	( * ( ( volatile uint32_t * ) 0xe000ed20 ) ) |= ( ( ( uint32_t ) ( 0x0f << (8 - 4) ) ) << 24UL );

	
 
	vPortSetupTimerInterrupt();

	 
	uxCriticalNesting = 0;

	 
	vPortEnableVFP();

	 
	*( ( ( volatile uint32_t * ) 0xe000ef34 ) ) |= ( 0x3UL << 30UL );

	 
	vPortStartFirstTask();

	 
	return 0;
}
 

void vPortEndScheduler( void )
{
	
 
	;
}
 

void vPortYield( void )
{
	 
	( * ( ( volatile uint32_t * ) 0xe000ed04 ) ) = ( 1UL << 28UL );

	
 
	__DSB();
	__ISB();
}
 

void vPortEnterCritical( void )
{
	ulPortSetInterruptMask();
	uxCriticalNesting++;
	__DSB();
	__ISB();
	
	



 
	if( uxCriticalNesting == 1 )
	{
		;
	}
}
 

void vPortExitCritical( void )
{
	;
	uxCriticalNesting--;
	if( uxCriticalNesting == 0 )
	{
		vPortClearInterruptMask( 0 );
	}
}
 

void xPortSysTickHandler( void )
{
	


 
	( void ) ulPortSetInterruptMask();
	{
		 
		if( xTaskIncrementTick() != ( ( BaseType_t ) 0 ) )
		{
			
 
			( * ( ( volatile uint32_t * ) 0xe000ed04 ) ) = ( 1UL << 28UL );
		}
	}
	vPortClearInterruptMask( 0 );
}
 



	__weak void vPortSuppressTicksAndSleep( TickType_t xExpectedIdleTime )
	{
	uint32_t ulReloadValue, ulCompleteTickPeriods, ulCompletedSysTickDecrements, ulSysTickCTRL;
	TickType_t xModifiableIdleTime;

		 
		if( xExpectedIdleTime > xMaximumPossibleSuppressedTicks )
		{
			xExpectedIdleTime = xMaximumPossibleSuppressedTicks;
		}

		


 
		( * ( ( volatile uint32_t * ) 0xe000e010 ) ) &= ~( 1UL << 0UL );

		

 
		ulReloadValue = ( * ( ( volatile uint32_t * ) 0xe000e018 ) ) + ( ulTimerCountsForOneTick * ( xExpectedIdleTime - 1UL ) );
		if( ulReloadValue > ulStoppedTimerCompensation )
		{
			ulReloadValue -= ulStoppedTimerCompensation;
		}

		
 
		__disable_interrupt();

		
 
		if( eTaskConfirmSleepModeStatus() == eAbortSleep )
		{
			
 
			( * ( ( volatile uint32_t * ) 0xe000e014 ) ) = ( * ( ( volatile uint32_t * ) 0xe000e018 ) );

			 
			( * ( ( volatile uint32_t * ) 0xe000e010 ) ) |= ( 1UL << 0UL );

			
 
			( * ( ( volatile uint32_t * ) 0xe000e014 ) ) = ulTimerCountsForOneTick - 1UL;

			
 
			__enable_interrupt();
		}
		else
		{
			 
			( * ( ( volatile uint32_t * ) 0xe000e014 ) ) = ulReloadValue;

			
 
			( * ( ( volatile uint32_t * ) 0xe000e018 ) ) = 0UL;

			 
			( * ( ( volatile uint32_t * ) 0xe000e010 ) ) |= ( 1UL << 0UL );

			



 
			xModifiableIdleTime = xExpectedIdleTime;
			( freertos_pre_sleep_processing(&xModifiableIdleTime) );
			if( xModifiableIdleTime > 0 )
			{
				__DSB();
				__WFI();
				__ISB();
			}
			( freertos_post_sleep_processing(&xExpectedIdleTime) );

			


 
			ulSysTickCTRL = ( * ( ( volatile uint32_t * ) 0xe000e010 ) );
			( * ( ( volatile uint32_t * ) 0xe000e010 ) ) = ( ulSysTickCTRL & ~( 1UL << 0UL ) );

			
 
			__enable_interrupt();

			if( ( ulSysTickCTRL & ( 1UL << 16UL ) ) != 0 )
			{
				uint32_t ulCalculatedLoadValue;

				


 
				ulCalculatedLoadValue = ( ulTimerCountsForOneTick - 1UL ) - ( ulReloadValue - ( * ( ( volatile uint32_t * ) 0xe000e018 ) ) );

				

 
				if( ( ulCalculatedLoadValue < ulStoppedTimerCompensation ) || ( ulCalculatedLoadValue > ulTimerCountsForOneTick ) )
				{
					ulCalculatedLoadValue = ( ulTimerCountsForOneTick - 1UL );
				}

				( * ( ( volatile uint32_t * ) 0xe000e014 ) ) = ulCalculatedLoadValue;

				



 
				ulCompleteTickPeriods = xExpectedIdleTime - 1UL;
			}
			else
			{
				


 
				ulCompletedSysTickDecrements = ( xExpectedIdleTime * ulTimerCountsForOneTick ) - ( * ( ( volatile uint32_t * ) 0xe000e018 ) );

				
 
				ulCompleteTickPeriods = ulCompletedSysTickDecrements / ulTimerCountsForOneTick;

				
 
				( * ( ( volatile uint32_t * ) 0xe000e014 ) ) = ( ( ulCompleteTickPeriods + 1 ) * ulTimerCountsForOneTick ) - ulCompletedSysTickDecrements;
			}

			



 
			( * ( ( volatile uint32_t * ) 0xe000e018 ) ) = 0UL;
			vPortEnterCritical();
			{
				( * ( ( volatile uint32_t * ) 0xe000e010 ) ) |= ( 1UL << 0UL );
				vTaskStepTick( ulCompleteTickPeriods );
				( * ( ( volatile uint32_t * ) 0xe000e014 ) ) = ulTimerCountsForOneTick - 1UL;
			}
			vPortExitCritical();
		}
	}


 




 
__weak void vPortSetupTimerInterrupt( void )
{
	 

	{
		ulTimerCountsForOneTick = ( 32768 / ( ( uint32_t ) 1000 ) );
		xMaximumPossibleSuppressedTicks = ( 0xffffffUL ) / ulTimerCountsForOneTick;
		ulStoppedTimerCompensation = ( 45UL ) / ( ( SystemCoreClock ) / 32768 );
	}


	 
	( * ( ( volatile uint32_t * ) 0xe000e014 ) ) = ( 32768 / ( ( uint32_t ) 1000 ) ) - 1UL;
	( * ( ( volatile uint32_t * ) 0xe000e010 ) ) = ( ( 0 ) | ( 1UL << 1UL ) | ( 1UL << 0UL ) );
}
 

#line 632 "E:\\Lock-GW\\project\\00007829-sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\sdk-ameba-v4.0a\\component\\os\\freertos\\freertos_v8.1.2\\Source\\portable\\IAR\\ARM_CM4F\\port.c"

 
void vApplicationIdleHook( void )
{
	
 
}

void vApplicationStackOverflowHook( TaskHandle_t pxTask, signed char *pcTaskName )
{
	
 

	printf("\n\r[%s] STACK OVERFLOW - TaskName(%s)\n\r", __FUNCTION__, pcTaskName);
	for( ;; );
}



















