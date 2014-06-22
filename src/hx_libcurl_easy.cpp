#include "hx_libcurl_easy.hpp"
#include <curl/curl.h>

extern "C"
{
    static void finalize_easy_handle(value handle)
    {
        curl_easy_cleanup(val_curl(handle));
    }


    // http://curl.haxx.se/libcurl/c/curl_easy_cleanup.html
    static value hxcurl_easy_cleanup(value handle)
    {
        val_check_kind(handle, k_curl_handle);
        finalize_easy_handle(handle);

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
            val_gc(val, finalize_easy_handle);
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
        }
        curl_free(escaped);

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
            val_gc(val, finalize_easy_handle);
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
    static value hxcurl_easy_recv(value handle, value length)
    {
        val_check_kind(handle, k_curl_handle);

        value val;
        size_t received;
        char buffer[val_int(length)];
        CURLcode ret = curl_easy_recv(val_curl(handle), &buffer, val_int(length), &received);
        if (ret != 0) {
            curl_error(ret);
        } else {
            val = alloc_string(buffer);
        }
        curl_free(buffer);

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_reset.html
    static value hxcurl_easy_reset(value handle)
    {
        val_check_kind(handle, k_curl_handle);
        curl_easy_reset(val_curl(handle));

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_send.html
    static value hxcurl_easy_send(value handle, value msg)
    {
        val_check_kind(handle, k_curl_handle);
        val_check(msg, string);

        value val;
        size_t sent;
        CURLcode ret = curl_easy_send(val_curl(handle), val_string(msg), val_strlen(msg), &sent);
        if (ret != 0) {
            curl_error(ret);
            val = alloc_null();
        } else {
            val = alloc_int(sent);
        }

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_setopt.html
    // TODO: define val type
    // static value hxcurl_easy_setopt(value handle, value opt, value val)
    // {
    //     val_check_kind(handle, k_curl_handle);
    //     val_check(opt, int);

    //     CURLcode ret = curl_easy_setopt(val_curl(handle), val_int(opt), val);
    //     if (ret != 0) {
    //         curl_error(ret);
    //     }

    //     return alloc_null();
    // }

    // http://curl.haxx.se/libcurl/c/curl_easy_unescape.html
    static value hxcurl_easy_unescape(value handle, value str)
    {
        val_check_kind(handle, k_curl_handle);
        val_check(str, string);

        value val;
        char* unescaped = curl_easy_unescape(val_curl(handle), val_string(str), val_strlen(str), NULL);
        if (unescaped == NULL) {
            neko_error();
            val = alloc_null();
        } else {
            val = alloc_string(unescaped);
        }
        curl_free(unescaped);

        return val;
    }
}

DEFINE_PRIM(hxcurl_easy_cleanup, 1);
DEFINE_PRIM(hxcurl_easy_duphandle, 1);
// DEFINE_PRIM(hxcurl_easy_getinfo, X);
DEFINE_PRIM(hxcurl_easy_escape, 2);
DEFINE_PRIM(hxcurl_easy_init, 0);
DEFINE_PRIM(hxcurl_easy_pause, 2);
DEFINE_PRIM(hxcurl_easy_perform, 1);
DEFINE_PRIM(hxcurl_easy_recv, 2);
DEFINE_PRIM(hxcurl_easy_reset, 1);
DEFINE_PRIM(hxcurl_easy_send, 2);
// DEFINE_PRIM(hxcurl_easy_setopt, 3);
DEFINE_PRIM(hxcurl_easy_unescape, 2);
