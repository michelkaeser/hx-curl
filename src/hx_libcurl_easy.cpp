#include "hx_libcurl_easy.hpp"
#include "hx_libcurl.hpp"
#include <curl/curl.h>

extern "C"
{
    // http://curl.haxx.se/libcurl/c/curl_easy_cleanup.html
    static value hxcurl_easy_cleanup(value handle)
    {
        val_check_kind(handle, k_curl_handle);
        finalize_curl_handle(handle);

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_duphandle.html
    static value hxcurl_easy_duphandle(value handle)
    {
        val_check_kind(handle, k_curl_handle);

        value val;
        CURL* dup = curl_easy_duphandle(val_curl(handle));
        if (dup == NULL) {
            neko_error();
            val = alloc_null();
        } else {
            val = alloc_curl(dup);
            val_gc(val, finalize_curl_handle);
        }

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_escape.html
    static value hxcurl_easy_escape(value handle, value str)
    {
        val_check_kind(handle, k_curl_handle);
        val_check(str, string);

        value val;
        char* escaped = curl_easy_escape(val_curl(handle), val_string(str), val_strlen(str));
        if (escaped == NULL) {
            neko_error();
            val = alloc_null();
        } else {
            val = alloc_string(escaped);
            curl_free(escaped);
        }

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_getinfo.html
    // static value hxcurl_easy_getinfo(...)
    // {
    // }

    // http://curl.haxx.se/libcurl/c/curl_easy_init.html
    static value hxcurl_easy_init()
    {
        value val;
        CURL* handle = curl_easy_init();
        if (handle == NULL) {
            neko_error();
            val = alloc_null();
        } else {
            val = alloc_curl(handle);
            val_gc(val, finalize_curl_handle);
        }

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_pause.html
    static value hxcurl_easy_pause(value handle, value bitmask)
    {
        val_check_kind(handle, k_curl_handle);
        val_check(bitmask, int);

        CURLcode ret = curl_easy_pause(val_curl(handle), val_int(bitmask));
        if (ret != 0) {
            curl_error(ret);
        }

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_perform.html
    static value hxcurl_easy_perform(value handle)
    {
        val_check_kind(handle, k_curl_handle);

        CURLcode ret = curl_easy_perform(val_curl(handle));
        if (ret != 0) {
            curl_error(ret);
        }

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_recv.html
    // static value hxcurl_easy_recv()
    // {
    // }

    // http://curl.haxx.se/libcurl/c/curl_easy_reset.html
    static value hxcurl_easy_reset(value handle)
    {
        val_check_kind(handle, k_curl_handle);
        curl_easy_reset(val_curl(handle));

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_send.html
    // static value hxcurl_easy_send()
    // {
    // }

    // http://curl.haxx.se/libcurl/c/curl_easy_setopt.html
    // static value hxcurl_easy_setopt(...)
    // {
    // }

    // http://curl.haxx.se/libcurl/c/curl_easy_unescape.html
    // static value hxcurl_easy_unescape(...)
    // {
    // }
}

DEFINE_PRIM(hxcurl_easy_cleanup, 1);
DEFINE_PRIM(hxcurl_easy_duphandle, 1);
// DEFINE_PRIM(hxcurl_easy_getinfo, X);
DEFINE_PRIM(hxcurl_easy_escape, 2);
DEFINE_PRIM(hxcurl_easy_init, 0);
DEFINE_PRIM(hxcurl_easy_pause, 2);
DEFINE_PRIM(hxcurl_easy_perform, 1);
// DEFINE_PRIM(hxcurl_easy_recv, X);
DEFINE_PRIM(hxcurl_easy_reset, 1);
// DEFINE_PRIM(hxcurl_easy_send, X);
// DEFINE_PRIM(hxcurl_easy_setopt, X);
// DEFINE_PRIM(hxcurl_easy_unescape, X);
