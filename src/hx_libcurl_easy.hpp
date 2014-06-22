#ifndef __HX_LIBCURL_EASY_HPP
#define __HX_LIBCURL_EASY_HPP

#include "hx_libcurl.hpp"
#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE 1
#include <hx/CFFI.h>

extern "C"
{
    static void  finalize_easy_handle(value handle);

    static value hxcurl_easy_cleanup(value handle);
    static value hxcurl_easy_duphandle(value handle);
    static value hxcurl_easy_escape(value handle, value str);
    // static value hxcurl_easy_getinfo(...);
    static value hxcurl_easy_init();
    static value hxcurl_easy_pause(value handle, value bitmask);
    static value hxcurl_easy_perform(value handle);
    static value hxcurl_easy_recv(value handle, value length);
    static value hxcurl_easy_reset(value handle);
    static value hxcurl_easy_send(value handle, value msg);
    // static value hxcurl_easy_setopt(value handle, value opt, value val);
    static value hxcurl_easy_unescape(value handle, value str);
}

#endif
