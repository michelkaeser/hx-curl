#ifndef __HX_LIBCURL_SHARE_HPP
#define __HX_LIBCURL_SHARE_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "hx_libcurl.hpp"


DECLARE_KIND(k_share_curl);

#define alloc_share_curl(v)    alloc_abstract(k_share_curl, v)
#define curl_share_error(ret)  val_throw(alloc_string(curl_share_strerror(ret)))
#define malloc_share_curl()    (SCURL*)alloc_private(sizeof(SCURL))
#define val_share_curl(v)      (SCURL*)val_data(v)
#define val_share_handle(v)    (val_share_curl(v))->handle
#define val_is_share_curl(v)   val_is_kind(v, k_share_curl)


/* extern */ typedef struct S_SCALLBACKS {
    AutoGCRoot* lock;
    AutoGCRoot* unlock;
} SCALLBACKS;

/*extern */ typedef struct S_SCURL {
    SCALLBACKS* callbacks;
    bool        cleanup;
    value       data;
    CURLSH*     handle;
} SCURL;


/*
 *
 */
void finalize_share_curl_abstract(value curl);


/*
 *
 */
void finalize_share_curl_callbacks(SCALLBACKS* callbacks);


/*
 *
 */
void finalize_share_curl_handle(CURLSH* handle);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_share_cleanup.html
 */
value hxcurl_share_cleanup(value curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_share_setopt.html
 */
value hxcurl_share_setopt(value curl, value curlopt, value optval);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_share_init.html
 */
value hxcurl_share_init(void);


/*
 *
 */
inline SCALLBACKS* malloc_share_callbacks(void)
{
    extern void* memcpy(void* dest, const void* src, size_t count);

    const SCALLBACKS callbacks = { NULL, NULL };
    SCALLBACKS* mcallbacks = (SCALLBACKS*)alloc_private(sizeof(SCALLBACKS));
    memcpy(mcallbacks, &callbacks, sizeof(SCALLBACKS));

    return mcallbacks;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HX_LIBCURL_SHARE_HPP */
