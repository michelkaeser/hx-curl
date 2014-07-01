#define  NEKO_COMPATIBLE
#include <stdlib.h>
#include <hx/CFFI.h>
#include <curl/curl.h>

#include "hx_libcurl_share.hpp"

extern "C" {

static void finalize_curl_abstract(value val)
{
    if (val_is_share_curl(val)) {
        SCURL* scurl = val_share_curl(val);
        if (scurl->cleanup) {
            finalize_curl_handle(scurl->handle);
            scurl->handle = NULL;
        }
        scurl->cleanup = (bool)NULL;
        free(scurl);
        scurl = NULL;
    }
}

static void finalize_curl_handle(void* handle)
{
    if (handle != NULL) {
        curl_easy_cleanup((CURLSH*)handle);
    }
}


value hxcurl_share_cleanup(value curl)
{
    val_check_kind(curl, k_share_curl);

    SCURL* scurl = val_share_curl(curl);
    if (scurl->cleanup) {
        curl_share_cleanup(scurl->handle);
        scurl->cleanup = false;
    } else {
        neko_error();
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_share_cleanup, 1);


value hxcurl_share_init(void)
{
    value val;
    CURLSH* handle = curl_share_init();
    if (handle == NULL) {
        neko_error();
        val = alloc_null();
    } else {
        SCURL* scurl   = malloc_share_curl();
        scurl->cleanup = true;
        scurl->handle  = handle;

        val = alloc_share_curl(scurl);
        val_gc(val, finalize_curl_abstract);
    }

    return val;
}
DEFINE_PRIM(hxcurl_share_init, 0);

} // extern "C"
