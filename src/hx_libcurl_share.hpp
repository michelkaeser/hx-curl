#ifndef __HX_LIBCURL_SHARE_HPP
#define __HX_LIBCURL_SHARE_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "hx_libcurl.hpp"


DEFINE_KIND(k_share_curl);

#define alloc_share_curl(v)    alloc_abstract(k_share_curl, v)
#define curl_share_error(ret)  val_throw(alloc_string(curl_share_strerror(ret)))
#define malloc_share_curl()    (SCURL*)malloc(sizeof(SCURL))
#define val_share_curl(v)      (SCURL*)val_data(v)
#define val_share_handle(v)    (val_share_curl(v))->handle
#define val_is_share_curl(v)   val_is_kind(v, k_share_curl)


/*extern */ typedef struct S_SCURL {
    bool    cleanup;
    CURLSH* handle;
} SCURL;


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_share_cleanup.html
 */
value hxcurl_share_cleanup(value curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_share_setopt.html
 */
value hxcurl_share_setopt(value curl, value option, value optval);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_share_init.html
 */
value hxcurl_share_init(void);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HX_LIBCURL_SHARE_HPP */
