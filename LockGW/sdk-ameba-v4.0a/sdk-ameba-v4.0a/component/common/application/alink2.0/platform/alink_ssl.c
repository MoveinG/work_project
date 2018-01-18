
#ifdef PLATFORM_LINUX
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#endif

#include "alink2.0/include/alink_platform.h"

#if CONFIG_USE_POLARSSL


#define CONFIG_SSL	 	1

#if CONFIG_SSL
#include "polarssl/config.h"
#include "polarssl/net.h"
#include "polarssl/ssl.h"
#include "polarssl/error.h"
#include "polarssl/memory.h"
#endif

/*Data structure definition*/

typedef struct _alink_ssl_t {
	ssl_context ctx;
} alink_ssl_t;


#define SSL_VERIFY_CLIENT_CA

ssl_context *g_ssl = NULL;
long alink_fd = -1;

pthread_mutex_t mutex;

static int my_verify( void *data, x509_crt *crt, int depth, int *flags ) 
 { 
	char buf[1024]; 
	((void) data); 

	alink_printf(ALINK_INFO, "Verify requested for (Depth %d):\n", depth ); 
	x509_crt_info( buf, sizeof( buf ) - 1, "", crt ); 

	if( ( (*flags) & BADCERT_EXPIRED ) != 0 ) 
		alink_err_printf("server certificate has expired\n" ); 

	if( ( (*flags) & BADCERT_REVOKED ) != 0 ) 
		alink_err_printf("! server certificate has been revoked\n" ); 

	if( ( (*flags) & BADCERT_CN_MISMATCH ) != 0 ) 
		alink_err_printf("! CN mismatch\n" ); 

	if( ( (*flags) & BADCERT_NOT_TRUSTED ) != 0 ) 
		alink_err_printf("! self-signed or not signed by a trusted CA\n" ); 

	if( ( (*flags) & BADCRL_NOT_TRUSTED ) != 0 ) 
		alink_err_printf("! CRL not trusted\n" ); 

	if( ( (*flags) & BADCRL_EXPIRED ) != 0 ) 
		alink_err_printf("! CRL expired\n" ); 

	if( ( (*flags) & BADCERT_OTHER ) != 0 ) 
		alink_err_printf("! other (unknown) flag\n" ); 

	if ( ( *flags ) == 0 ) 
		alink_printf(ALINK_INFO, "This certificate has no flags\n" ); 

	return 0; 
 } 

#define DEBUG_LEVEL   3

#ifdef POLARSSL_DEBUG_C
static void my_debug(void *ctx, int level, const char *str)
{
	if(level <= DEBUG_LEVEL) {
		printf("\n\r%s", str);
	}
}
#endif

static int _ssl_random(void *p_rng, unsigned char *output, size_t output_len)
{
	rtw_get_random_bytes(output, output_len);
	return 0;
}

void *platform_ssl_connect(void *tcp_fd,
        const char *server_cert,
        int server_cert_len)
{
	alink_printf(ALINK_INFO, "[%s] Start ssl connect\n", __FUNCTION__); 
	int ret = 0;
   	int retry_count = 0;
	x509_crt cacert;
//	alink_ssl_t *tls = NULL;
	ssl_context *ssl = NULL;
	alink_fd = (long)tcp_fd;
	ssl = (ssl_context *)pvPortMalloc(sizeof(ssl_context));
	if(!ssl) {
		alink_err_printf("ERROR: malloc failed\n");
		return (void *)-1;
	} else {
		memory_set_own(pvPortMalloc, vPortFree);
		memset(ssl, 0, sizeof(ssl_context));
		if (!g_ssl) {
			ret = ssl_init(ssl);
			if(ret != 0) {
				alink_err_printf("ERROR: ssl_init %d\n", ret);
				goto exit1;
			}
			mutex = (pthread_mutex_t)platform_mutex_init();
			g_ssl = ssl;
			x509_crt_init( &cacert );
			ssl_set_endpoint(ssl, SSL_IS_CLIENT);
#ifdef POLARSSL_DEBUG_C
			debug_set_threshold(DEBUG_LEVEL);
			ssl_set_dbg(ssl, my_debug, NULL);
#endif

#ifdef SSL_VERIFY_CLIENT_CA
			if(server_cert != NULL && server_cert_len != 0){
				ssl_set_authmode(ssl, SSL_VERIFY_REQUIRED);
				/*Load the trusted CA */
				x509_crt_parse(&cacert, (const unsigned char *)server_cert, server_cert_len);		
				ssl_set_ca_chain(ssl, &cacert, NULL, NULL);
				ssl_set_verify(ssl, my_verify, NULL );

			} else 
#endif
			{
				ssl_set_authmode(ssl, SSL_VERIFY_NONE);
			}

			ssl_set_rng(ssl, _ssl_random, NULL);
			ssl_set_bio(ssl, net_recv, &alink_fd, net_send, &alink_fd);
		}

		while((ret = ssl_handshake(ssl)) != 0) {
			if((ret != POLARSSL_ERR_NET_WANT_READ && ret != POLARSSL_ERR_NET_WANT_WRITE  
				&& ret != POLARSSL_ERR_NET_RECV_FAILED) || retry_count >= 20) {
				alink_err_printf(" [ret=-0x%x]SSL handshake fail!retry_count = %d\n", ret, retry_count);
				ret = -1;
				goto exit;
			}
			retry_count++;
		}
		alink_printf(ALINK_INFO, "INFO: SSL handshake success\n");	
		alink_printf(ALINK_INFO, "INFO: SSL ciphersuite: %s\n", ssl_get_ciphersuite(ssl));
		x509_crt_free( &cacert );
		return (void *) ssl;	

	}
exit:
	ssl_free(ssl);
	ssl_close_notify(ssl);
	x509_crt_free( &cacert );
	platform_mutex_destroy(mutex);
exit1:	
	vPortFree(ssl);
	ssl = NULL;
	g_ssl = NULL;
	return NULL;
}

int platform_ssl_close(void *ssl)
{
	alink_err_printf("ssl_force_close: %p", ssl);
	if (ssl != NULL) {
		ssl_close_notify(ssl);
		ssl_free(ssl);
		vPortFree(ssl);
		ssl = NULL;
	}
	g_ssl = NULL;
	if (mutex != NULL) {
		platform_mutex_destroy(mutex);
	}
	return 0;
}

int platform_ssl_recv(void *ssl, char *buf, int len)
{
	alink_printf(ALINK_DEBUG, "[%s] recv buf: %s\n", __FUNCTION__, buf); 	
	int ret = 0;
//	int total_len = 0;
	if (!ssl) {
		return -1;
	}
/*
	platform_mutex_lock(mutex);
	do { 
		ret = ssl_read(ssl, buf, len);
		if (ret <= 0) {
			break;
		} else {
		        total_len += ret;
		        buf += ret;
		        len -= ret;
		}
	} while (ssl && (len != 0));
	platform_mutex_unlock(mutex);
*/
	platform_mutex_lock(mutex);
	ret = ssl_read(ssl, buf, len);
	platform_mutex_unlock(mutex);
	
	if (ret < 0) {
		alink_err_printf(" SSL receive error, ret = %d\n", ret);
		return -1;
	}
	//printf("ssl recv %d\n", total_len);
	return ret;
//	return (ret >= 0) ? total_len: -1;
}

int platform_ssl_send(void *ssl, const char *buf, int len)
{
	alink_printf(ALINK_DEBUG, "[%s] send buf: %s\n", __FUNCTION__, buf); 	
	int ret = 0;
	if (!ssl) {
		return -1;
	}
	platform_mutex_lock(mutex);

	if (ssl) {
		ret = ssl_write(ssl, (const unsigned char *)buf, len);
	}
	platform_mutex_unlock(mutex);
	
	return (ret > 0) ? ret : -1;
}

void alink_aes_init( void *ctx )
{
	/*move the cryptoEngine from main funtion to here*/
	if ( rtl_cryptoEngine_init() != 0 ) {
	    DiagPrintf("crypto engine init failed\r\n");
	}
	memory_set_own(pvPortMalloc, vPortFree);
	aes_init(( aes_context *)ctx);
}

int alink_aes_setkey_enc( void *ctx, const unsigned char *key,
                    unsigned int keysize )
{
	return aes_setkey_enc((aes_context *)ctx, key, keysize);
}

int alink_aes_setkey_dec( void *ctx, const unsigned char *key,
                    unsigned int keysize )
{
	return aes_setkey_dec((aes_context *)ctx, key, keysize);
}

void alink_aes_free( void *ctx )
{
	aes_free(( aes_context *)ctx);
}

int alink_aes_crypt_cbc( void *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output )
{
	return aes_crypt_cbc((aes_context *)ctx, mode, length, iv, input, output);
}

void *init_aes_content()
{
	aes_context *aes_ctx = NULL;
	aes_ctx = pvPortMalloc(sizeof(aes_context));
	if(aes_ctx == NULL){
		alink_err_printf("malloc ctx failed\n");
		return  NULL;
	}
	return (void *)aes_ctx;
}

#elif CONFIG_USE_MBEDTLS /* CONFIG_USE_POLARSSL */

#include "mbedtls/config.h"
#include "mbedtls/platform.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/ssl.h"
#include "mbedtls/error.h"
#include "mbedtls/debug.h"

mbedtls_ssl_context *g_ssl = NULL;
pthread_mutex_t mutex;
long alink_fd = -1;
#define DEBUG_LEVEL   0

#define SSL_VERIFY_SERVER;
/*
 * Default profile
 */
const mbedtls_x509_crt_profile alink_mbedtls_x509_crt_profile_default =
{
	/* Hashes from SHA-1 and above */
	MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_MD5 ) |
	MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA1 ) |
	MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_RIPEMD160 ) |
	MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA224 ) |
	MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA256 ) |
	MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA384 ) |
	MBEDTLS_X509_ID_FLAG( MBEDTLS_MD_SHA512 ),
	0xFFFFFFF, /* Any PK alg    */
	0xFFFFFFF, /* Any curve     */
	2048,
};

struct mbed_tls {
	mbedtls_ssl_context ctx;         /*!< Context for mbedTLS */
	mbedtls_ssl_config conf;         /*!< Configuration for mbedTLS */
};
static void* my_calloc(size_t nelements, size_t elementSize)
{
	size_t size;
	void *ptr = NULL;

	size = nelements * elementSize;
	ptr = pvPortMalloc(size);

	if(ptr)
		memset(ptr, 0, size);
	return ptr;
}

static int _ssl_random(void *p_rng, unsigned char *output, size_t output_len)
{
	rtw_get_random_bytes(output, output_len);
	return 0;
}

static void mbed_ssl_debug(void *ctx, int level, const char *file, int line, const char *str)
{
	if(level <= DEBUG_LEVEL) {
		printf("\n\r%s:%d: %s\n\r", file, line, str);
	}
}
static int mbedtls_my_verify( void *data, mbedtls_x509_crt *crt, int depth, uint32_t *flags ) 
{ 
	char buf[1024]; 

	alink_printf(ALINK_INFO, "Verify requested for (Depth %d):\n", depth ); 
	mbedtls_x509_crt_info( buf, sizeof( buf ) - 1, "", crt ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_EXPIRED ) != 0 ) 
		alink_err_printf("server certificate has expired\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_REVOKED ) != 0 ) 
		alink_err_printf("! server certificate has been revoked\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_CN_MISMATCH ) != 0 ) 
		alink_err_printf("! CN mismatch\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_NOT_TRUSTED ) != 0 ) 
		alink_err_printf("! self-signed or not signed by a trusted CA\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCRL_NOT_TRUSTED ) != 0 ) 
		alink_err_printf("! CRL not trusted\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCRL_EXPIRED ) != 0 ) 
		alink_err_printf("! CRL expired\n" ); 

	if( ( (*flags) & MBEDTLS_X509_BADCERT_OTHER ) != 0 ) 
		alink_err_printf("! other (unknown) flag\n" ); 

	if ( ( *flags ) == 0 ) 
		alink_printf(ALINK_INFO, "This certificate has no flags\n" ); 

	return 0; 
 } 

#define my_free		vPortFree
void *platform_ssl_connect(_IN_ void *tcp_fd, _IN_ const char *server_cert, _IN_ int server_cert_len)
{
	alink_printf(ALINK_INFO, "[%s] Start ssl connect\n", __FUNCTION__); 
	int ret = 0;
   	int retry_count = 0;
	mbedtls_x509_crt *ca_cert = NULL;
	mbedtls_ssl_context *ssl = NULL;
	mbedtls_ssl_config *conf = NULL;
	alink_fd = (long)tcp_fd;
	struct mbed_tls *alink_tls = NULL;	
	
	mbedtls_platform_set_calloc_free(my_calloc, my_free);
	alink_tls = (struct mbed_tls *)pvPortMalloc(sizeof(struct mbed_tls));
	if(alink_tls == NULL) {
		alink_err_printf("ERROR: malloc failed\n");
		return (void *)-1;
	} else {
		memset(alink_tls, 0, sizeof(struct mbed_tls));
		ssl = &alink_tls->ctx;
		conf = &alink_tls->conf;
		if (g_ssl == NULL) {
			alink_printf(ALINK_INFO, ". Setting up the SSL/TLS structure...\n");
			mbedtls_ssl_init(ssl);
			mbedtls_ssl_config_init(conf);
			mutex = (pthread_mutex_t)platform_mutex_init();
			g_ssl = ssl;
			
#if defined(MBEDTLS_DEBUG_C)
			mbedtls_debug_set_threshold(DEBUG_LEVEL);
#endif
			if((ret = mbedtls_ssl_config_defaults(conf,
				MBEDTLS_SSL_IS_CLIENT,
				MBEDTLS_SSL_TRANSPORT_STREAM,
				MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {

				alink_err_printf(" failed\n  ! mbedtls_ssl_config_defaults returned %d\n\n", ret);
				goto err;
			}
			
#ifdef SSL_VERIFY_SERVER
			if(server_cert != NULL && server_cert_len != 0){
				ca_cert = (mbedtls_x509_crt *) mbedtls_calloc( sizeof(mbedtls_x509_crt), 1);
				if ( ca_cert == NULL ) {
					alink_err_printf("ERROR: malloc root_crt failed!");
					goto err;
				}
				mbedtls_x509_crt_init(ca_cert);
				/*Load the trusted CA */
//				printf("server_cert_len: %d, strlen(server_cert): %d\n", server_cert_len, strlen(server_cert));
				if (mbedtls_x509_crt_parse( ca_cert,  (const unsigned char *)server_cert, server_cert_len + 1) != 0) {
					alink_err_printf("parse root_crt failed!");
					goto err;
				}
				mbedtls_ssl_conf_cert_profile(conf, &alink_mbedtls_x509_crt_profile_default);
	 			mbedtls_ssl_conf_ca_chain(conf, ca_cert, NULL);
				mbedtls_ssl_conf_authmode(conf, MBEDTLS_SSL_VERIFY_REQUIRED);
				mbedtls_ssl_conf_verify(conf, mbedtls_my_verify, NULL );
				alink_printf(ALINK_INFO, "root_crt parse done\n");	

			} else 
#endif

			{
				mbedtls_ssl_conf_authmode(conf, MBEDTLS_SSL_VERIFY_NONE);

			}

			mbedtls_ssl_conf_rng(conf, _ssl_random, NULL);	
			mbedtls_ssl_set_bio(ssl, &alink_fd, mbedtls_net_send, mbedtls_net_recv, NULL);
			mbedtls_ssl_conf_dbg(conf, mbed_ssl_debug, NULL);
		}

		if((mbedtls_ssl_setup(ssl, conf)) != 0) {
			alink_err_printf("mbedtls_ssl_setup failed!");
			goto err;
		}

		/*
		 * 3. Handshake
		 */
		alink_printf(ALINK_INFO, "\n\r  . Performing the SSL/TLS handshake...");
		while((ret = mbedtls_ssl_handshake(ssl)) != 0) {
			if((ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE
				&& ret != MBEDTLS_ERR_NET_RECV_FAILED) || retry_count >= 5) {
				
				alink_err_printf(" failed\n\r  ! mbedtls_ssl_handshake returned -0x%x\n", -ret);
				goto err;
			}
			retry_count++;
		}
		alink_printf(ALINK_INFO, "INFO: SSL handshake success\n");	
		alink_printf(ALINK_INFO, "INFO: SSL ciphersuite: %s\n", mbedtls_ssl_get_ciphersuite(ssl));
		if (ca_cert) {
			mbedtls_x509_crt_free(ca_cert);
			mbedtls_free(ca_cert);
		}
		return (void *) alink_tls;			
	}
err:
	if (ca_cert) {
		mbedtls_x509_crt_free(ca_cert);
		mbedtls_free(ca_cert);
	}
	if (alink_tls) {
		mbedtls_ssl_free(&alink_tls->ctx);
		mbedtls_ssl_config_free(&alink_tls->conf);
		mbedtls_ssl_close_notify(&alink_tls->ctx);
		platform_mutex_destroy(mutex);
		vPortFree(alink_tls);
		alink_tls = NULL;
	}
	
	return NULL;
}

int platform_ssl_send(_IN_ void *ssl, _IN_ const char *buf, _IN_ int len)
{
	alink_printf(ALINK_DEBUG, "[%s] send buf: %s\n", __FUNCTION__, buf); 	
	int ret = 0;
	struct mbed_tls *alink_tls = NULL;	
	alink_tls = (struct mbed_tls *)ssl;
	if (!alink_tls) {
		return -1;
	}
	platform_mutex_lock(mutex);

	if (alink_tls) {
		ret = mbedtls_ssl_write(&alink_tls->ctx, (const unsigned char *)buf, len);
	}
	platform_mutex_unlock(mutex);
	
	return (ret > 0) ? ret : -1;
}

int platform_ssl_recv(_IN_ void *ssl, _IN_ char *buf, _IN_ int len)
{
	alink_printf(ALINK_DEBUG, "[%s] recv buf: %s\n", __FUNCTION__, buf);
	struct mbed_tls *alink_tls = NULL;
	alink_tls = (struct mbed_tls *)ssl;
	int ret = 0;
	if (!alink_tls) {
		return -1;
	}

	platform_mutex_lock(mutex);
	ret = mbedtls_ssl_read(&alink_tls->ctx, buf, len);
	platform_mutex_unlock(mutex);
	
	if (ret < 0) {
		alink_err_printf(" SSL receive error, ret = %d\n", ret);
		return -1;
	}
	return ret;
}

int platform_ssl_close(_IN_ void *ssl)
{
	struct mbed_tls *alink_tls = NULL;
	alink_tls = (struct mbed_tls *)ssl;
	if (!alink_tls) {
		return -1;
	}
	alink_err_printf("ssl_force_close: %p", alink_tls);
	if (alink_tls != NULL) {
		mbedtls_ssl_free(&alink_tls->ctx);
		mbedtls_ssl_config_free(&alink_tls->conf);
		mbedtls_ssl_close_notify(&alink_tls->ctx);
		vPortFree(alink_tls);
		alink_tls = NULL;
	}
	g_ssl = NULL;
	if (mutex != NULL) {
		platform_mutex_destroy(mutex);
	}
	return 0;
}

void alink_aes_init( void *ctx )
{
	/*move the cryptoEngine from main funtion to here*/
	if ( rtl_cryptoEngine_init() != 0 ) {
	    DiagPrintf("crypto engine init failed\r\n");
	}
	mbedtls_platform_set_calloc_free( my_calloc, my_free);
	mbedtls_aes_init((mbedtls_aes_context *)ctx);
}

int alink_aes_setkey_enc( void *ctx, const unsigned char *key,
                    	unsigned int keybits)
{
	return mbedtls_aes_setkey_enc((mbedtls_aes_context *)ctx, key, keybits);
}

int alink_aes_setkey_dec( void *ctx, const unsigned char *key,
                    unsigned int keybits )
{
	return mbedtls_aes_setkey_dec((mbedtls_aes_context *)ctx, key, keybits);
}

void alink_aes_free( void *ctx)
{
	mbedtls_aes_free((mbedtls_aes_context *)ctx );
}

int alink_aes_crypt_cbc( void *ctx,
                    int mode,
                    size_t length,
                    unsigned char iv[16],
                    const unsigned char *input,
                    unsigned char *output )
{
	return mbedtls_aes_crypt_cbc((mbedtls_aes_context *)ctx, mode, length, iv, input, output);
}


void *init_aes_content()
{
	mbedtls_aes_context *ctx = NULL;
	ctx = pvPortMalloc(sizeof(mbedtls_aes_context));
	if(ctx == NULL){
		alink_err_printf("malloc ctx failed\n");
		return  NULL;
	}
	return ctx;
}

#endif
