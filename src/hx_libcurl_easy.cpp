#include "hx_libcurl_easy.hpp"

extern "C"
{
    void finalize_curl_handle(CURL* curl)
    {
        if (curl != NULL) {
            curl_easy_cleanup(curl);
        }
    }


    // http://curl.haxx.se/libcurl/c/curl_easy_cleanup.html
    static value hxcurl_easy_cleanup(value val)
    {
        val_check_kind(val, k_curl_struct);

        struct S_CURL* curl = val_curl_struct(val);
        if (curl->cleanup) {
            finalize_curl_handle(curl->handle);
            curl->cleanup = false;
        } else {
            neko_error();
        }

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_duphandle.html
    static value hxcurl_easy_duphandle(value val)
    {
        val_check_kind(val, k_curl_struct);

        value dval;
        struct S_CURL* curl = val_curl_struct(val);
        CURL* dhandle = curl_easy_duphandle(curl->handle);
        if (dhandle == NULL) {
            neko_error();
            dval = alloc_null();
        } else {
            struct S_CURL* dup = malloc_curl_struct();
            dup->cleanup = curl->cleanup;
            dup->handle  = dhandle;
            dval = alloc_curl_struct(dup);
            val_gc(dval, finalize_curl_struct);
        }

        return dval;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_escape.html
    static value hxcurl_easy_escape(value curl, value str)
    {
        val_check_kind(curl, k_curl_struct);
        val_check(str, string);

        value val;
        char* escaped = curl_easy_escape((val_curl_struct(curl))->handle, val_string(str), val_strlen(str));
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
            struct S_CURL* curl = malloc_curl_struct();
            curl->cleanup = true;
            curl->handle  = handle;
            val = alloc_curl_struct(curl);
            val_gc(val, finalize_curl_struct);
        }

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_pause.html
    static value hxcurl_easy_pause(value curl, value bitmask)
    {
        val_check_kind(curl, k_curl_struct);
        val_check(bitmask, int);

        CURLcode ret = curl_easy_pause((val_curl_struct(curl))->handle, val_int(bitmask));
        if (ret != 0) {
            curl_easy_error(ret);
        }

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_perform.html
    static value hxcurl_easy_perform(value curl)
    {
        val_check_kind(curl, k_curl_struct);

        CURLcode ret = curl_easy_perform((val_curl_struct(curl))->handle);
        if (ret != 0) {
            curl_easy_error(ret);
        }

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_recv.html
    static value hxcurl_easy_recv(value curl, value length)
    {
        val_check_kind(curl, k_curl_struct);
        val_check(length, int);

        value val;
        const size_t buflen = val_int(length);
        size_t received;
        char buffer[buflen];
        CURLcode ret = curl_easy_recv((val_curl_struct(curl))->handle, &buffer, buflen, &received);
        if (ret != 0) {
            curl_easy_error(ret);
        } else {
            val = alloc_string(buffer);
        }
        curl_free(buffer);

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_reset.html
    static value hxcurl_easy_reset(value val)
    {
        val_check_kind(val, k_curl_struct);

        struct S_CURL* curl = val_curl_struct(val);
        curl_easy_reset(curl->handle);
        curl->cleanup = true;

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_send.html
    static value hxcurl_easy_send(value curl, value msg)
    {
        val_check_kind(curl, k_curl_struct);
        val_check(msg, string);

        value val;
        size_t sent;
        CURLcode ret = curl_easy_send((val_curl_struct(curl))->handle, val_string(msg), val_strlen(msg), &sent);
        if (ret != 0) {
            curl_easy_error(ret);
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
    static value hxcurl_easy_unescape(value curl, value str)
    {
        val_check_kind(curl, k_curl_struct);
        val_check(str, string);

        value val;
        char* unescaped = curl_easy_unescape((val_curl_struct(curl))->handle, val_string(str), val_strlen(str), NULL);
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
