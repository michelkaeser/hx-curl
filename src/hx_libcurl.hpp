#ifndef __HX_LIBCURL_HPP
#define __HX_LIBCURL_HPP

#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE 1
#include <hx/CFFI.h>

extern "C"
{
    DEFINE_KIND(k_curl_handle);

    #define alloc_curl(v)    alloc_abstract(k_curl_handle, v)
    #define curl_error(ret)  val_throw(alloc_string(curl_easy_strerror(ret)))
    #define val_curl(v)      (CURL*)val_data(v)
    #define val_is_curl(v)   val_is_kind(v, k_curl_handle)
}

#endif
