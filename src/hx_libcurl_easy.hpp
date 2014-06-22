#ifndef __HX_LIBCURL_EASY_HPP
#define __HX_LIBCURL_EASY_HPP

#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE 1
#include <hx/CFFI.h>

extern "C"
{
    static value hxcurl_easy_cleanup(value handle);
    static value hxcurl_easy_duphandle(value handle);
    static value hxcurl_easy_escape(value handle, value str);
    // static value hxcurl_easy_getinfo(...);
    static value hxcurl_easy_init();
    static value hxcurl_easy_pause(value handle, value bitmask);
    static value hxcurl_easy_perform(value handle);
    // static value hxcurl_easy_recv();
    static value hxcurl_easy_reset(value handle);
    // static value hxcurl_easy_send();
    // static value hxcurl_easy_setopt(...);
}

#endif
