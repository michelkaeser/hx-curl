#ifndef __HX_LIBCURL_MULTI_HPP
#define __HX_LIBCURL_MULTI_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "hx_libcurl.hpp"


DEFINE_KIND(k_multi_curl);

#define alloc_multi_curl(v)    alloc_abstract(k_multi_curl, v)
#define curl_multi_error(ret)  val_throw(alloc_string(curl_multi_strerror(ret)))
#define malloc_multi_curl()    (MCURL*)malloc(sizeof(MCURL))
#define val_multi_curl(v)      (MCURL*)val_data(v)
#define val_multi_handle(v)    (val_multi_curl(v))->handle
#define val_is_multi_curl(v)   val_is_kind(v, k_multi_curl)


/*extern */ typedef struct S_MCURL {
    bool   cleanup;
    CURLM* handle;
} MCURL;


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_add_handle.html
 */
value hxcurl_multi_add_handle(value multi_curl, value easy_curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_assign.html
 */
value hxcurl_multi_assign(value curl, ...);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_cleanup.html
 */
value hxcurl_multi_cleanup(value curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_fdset.html
 */
value hxcurl_multi_fdset(...);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_info_read.html
 */
value hxcurl_multi_info_read(...);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_init.html
 */
value hxcurl_multi_init(void);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_perform.html
 */
value hxcurl_multi_perform(value curl, value running);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_remove_handle.html
 */
value hxcurl_multi_remove_handle(value multi_curl, value easy_curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_setopt.html
 */
value hxcurl_multi_setopt(value curl, value option, value optval);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_socket.html
 */
value hxcurl_multi_socket(...);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_socket_action.html
 */
value hxcurl_multi_socket_action(...);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_timeout.html
 */
value hxcurl_multi_timeout(value curl, value timeout);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_multi_timeout.html
 */
value hxcurl_multi_wait(...);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HX_LIBCURL_MULTI_HPP */
