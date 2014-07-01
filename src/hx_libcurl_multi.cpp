#define  NEKO_COMPATIBLE
#include <stdlib.h>
#include <hx/CFFI.h>
#include <curl/curl.h>

#include "hx_libcurl_multi.hpp"

extern "C" {

static void finalize_curl_abstract(value val)
{
    if (val_is_multi_curl(val)) {
        MCURL* mcurl = val_multi_curl(val);
        if (mcurl->cleanup) {
            finalize_curl_handle(mcurl->handle);
            mcurl->handle = NULL;
        }
        mcurl->cleanup = (bool)NULL;
        free(mcurl);
        mcurl = NULL;
    }
}

static void finalize_curl_handle(void* handle)
{
    if (handle != NULL) {
        curl_multi_cleanup((CURLM*)handle);
    }
}


value hxcurl_multi_cleanup(value curl)
{
    val_check_kind(curl, k_multi_curl);

    MCURL* mcurl = val_multi_curl(curl);
    if (mcurl->cleanup) {
        CURLMcode ret = curl_multi_cleanup(mcurl->handle);
        mcurl->cleanup = false;
        if (ret != CURLM_OK) {
            curl_multi_error(ret);
        }
    } else {
        neko_error();
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_multi_cleanup, 1);


value hxcurl_multi_init(void)
{
    value val;
    CURLM* handle = curl_multi_init();
    if (handle == NULL) {
        neko_error();
        val = alloc_null();
    } else {
        MCURL* mcurl   = malloc_multi_curl();
        mcurl->cleanup = true;
        mcurl->handle  = handle;

        val = alloc_multi_curl(mcurl);
        val_gc(val, finalize_curl_abstract);
    }

    return val;
}
DEFINE_PRIM(hxcurl_multi_init, 0);

} // extern "C"
