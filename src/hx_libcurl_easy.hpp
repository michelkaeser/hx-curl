#ifndef __HX_LIBCURL_EASY_HPP
#define __HX_LIBCURL_EASY_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "hx_libcurl.hpp"


DECLARE_KIND(k_easy_curl);

#define alloc_easy_curl(v)      alloc_abstract(k_easy_curl, v)
#define curl_easy_error(ret)    val_throw(alloc_string(curl_easy_strerror(ret)))
#define malloc_easy_curl()      (ECURL*)alloc_private(sizeof(ECURL))
#define val_easy_curl(v)        (ECURL*)val_data(v)
#define val_easy_handle(v)      (val_easy_curl(v))->handle
#define val_is_easy_curl(v)     val_is_kind(v, k_easy_curl)


/* extern */ typedef struct S_ECALLBACKS {
    AutoGCRoot* debug;
    AutoGCRoot* header;
    AutoGCRoot* progress;
    AutoGCRoot* read;
    AutoGCRoot* write;
} ECALLBACKS;

// TODO: see https://github.com/HaxeFoundation/neko/issues/33
/* extern */ typedef struct S_EDATA {
    value debug;
    value header;
    value progress;
    value read;
    value write;
} EDATA;

/*extern */ typedef struct S_ECURL {
    ECALLBACKS* callbacks;
    bool        cleanup;
    EDATA*      data;
    char*       errbuf;
    CURL*       handle;
} ECURL;


/*
 *
 */
void finalize_easy_curl_abstract(value curl);


/*
 *
 */
void finalize_easy_curl_callbacks(ECALLBACKS* callbacks);


/*
 *
 */
void finalize_easy_curl_handle(CURL* handle);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_cleanup.html
 */
value hxcurl_easy_cleanup(value curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_duphandle.html
 */
value hxcurl_easy_duphandle(value curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_escape.html
 */
value hxcurl_easy_escape(value curl, value str);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_getinfo.html
 */
value hxcurl_easy_getinfo(value curl, value info, value type);

/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_init.html
 */
value hxcurl_easy_init(void);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_pause.html
 */
value hxcurl_easy_pause(value curl, value bitmask);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_perform.html
 */
value hxcurl_easy_perform(value curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_recv.html
 */
value hxcurl_easy_recv(value curl, value length);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_reset.html
 */
value hxcurl_easy_reset(value curl);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_send.html
 */
value hxcurl_easy_send(value curl, value bytes, value length);


/*
 *
 * See: See: http://curl.haxx.se/libcurl/c/curl_easy_setopt.html
 */
value hxcurl_easy_setopt(value curl, value option, value optval);


/*
 *
 * See: http://curl.haxx.se/libcurl/c/curl_easy_unescape.html
 */
value hxcurl_easy_unescape(value curl, value str);


/*
 *
 */
inline ECALLBACKS* malloc_easy_callbacks(void)
{
    extern void* memcpy(void* dest, const void* src, size_t count);

    const ECALLBACKS callbacks = { NULL, NULL, NULL, NULL, NULL };
    ECALLBACKS* mcallbacks = (ECALLBACKS*)alloc_private(sizeof(ECALLBACKS));
    memcpy(mcallbacks, &callbacks, sizeof(ECALLBACKS));

    return mcallbacks;
}


/*
 *
 */
inline EDATA* malloc_easy_data(void)
{
    extern void* memcpy(void* dest, const void* src, size_t count);

    const EDATA data = { NULL, NULL, NULL, NULL, NULL };
    EDATA* mdata = (EDATA*)alloc_private(sizeof(EDATA));
    memcpy(mdata, &data, sizeof(EDATA));

    return mdata;
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* __HX_LIBCURL_EASY_HPP */
