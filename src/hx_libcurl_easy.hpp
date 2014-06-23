#ifndef __HX_LIBCURL_EASY_HPP
#define __HX_LIBCURL_EASY_HPP

#include "hx_libcurl.hpp"

#ifdef __cplusplus
extern "C" {
#endif
    #define curl_easy_error(ret)  val_throw(alloc_string(curl_easy_strerror(ret)))

    static value hxcurl_easy_cleanup(value);
    // static value hxcurl_easy_duphandle(value);
    // static value hxcurl_easy_escape(value, value);
    // static value hxcurl_easy_getinfo(...);
    static value hxcurl_easy_init();
    // static value hxcurl_easy_pause(value, value);
    // static value hxcurl_easy_perform(value);
    // static value hxcurl_easy_recv(value, value);
    // static value hxcurl_easy_reset(value);
    // static value hxcurl_easy_send(value, value);
    // static value hxcurl_easy_setopt(value handle, value opt, value val);
    // static value hxcurl_easy_unescape(value, value);
#ifdef __cplusplus
}
#endif

#endif
