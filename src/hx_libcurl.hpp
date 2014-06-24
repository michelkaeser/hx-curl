#ifndef __HX_LIBCURL_HPP
#define __HX_LIBCURL_HPP

#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE 1
#include <stdlib.h>
#include <hx/CFFI.h>
#include <curl/curl.h>

#ifdef __cplusplus
extern "C" {
#endif
    DEFINE_KIND(k_curl_struct);

    #define alloc_curl_struct(v)   alloc_abstract(k_curl_struct, v)
    #define malloc_curl_struct()   (SCURL*)malloc(sizeof(SCURL))
    #define val_curl_struct(v)     (SCURL*)val_data(v)
    #define val_is_curl_struct(v)  val_is_kind(v, k_curl_struct)

    typedef struct S_CURL {
        bool  cleanup;
        CURL* handle;
    } SCURL;


    // GC finalizer to free 'CURL*' called by finalize_curl_struct
    extern void finalize_curl_handle(CURL*);
    // GC finalizer to free 'S_CURL' called when a 'k_curl_struct' gets garbage collected
    inline void finalize_curl_struct(value val)
    {
        if (val_is_curl_struct(val)) {
            SCURL* curl = val_curl_struct(val);
            if (curl->cleanup) {
                finalize_curl_handle(curl->handle);
                curl->handle = NULL;
            }
            curl->cleanup = (bool)NULL;
            free(curl);
            curl = NULL;
        }
        free(val);
        val = NULL;
    }
#ifdef __cplusplus
}
#endif

#endif
