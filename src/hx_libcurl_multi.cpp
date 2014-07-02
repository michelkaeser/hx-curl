#define  NEKO_COMPATIBLE
#include <stdlib.h>
#include <hx/CFFI.h>
#include <curl/curl.h>

#include "hx_libcurl_multi.hpp"
#include "hx_libcurl_easy.hpp"

extern "C" {

DEFINE_KIND(k_multi_curl);


void finalize_multi_curl_abstract(value val)
{
    if (val_is_multi_curl(val)) {
        MCURL* mcurl = val_multi_curl(val);
        if (mcurl != NULL) {
            if (mcurl->cleanup) {
                finalize_multi_curl_handle(mcurl->handle);
                mcurl->handle = NULL;
            }
            mcurl->cleanup = (bool)NULL;
            free(mcurl);
            mcurl = NULL;
        }
    }
}

void finalize_multi_curl_callbacks(MCALLBACKS* callbacks)
{
    if (callbacks != NULL) {
        if (callbacks->socket != NULL) {
            delete callbacks->socket;
            callbacks->socket = NULL;
        }
        if (callbacks->timer != NULL) {
            delete callbacks->timer;
            callbacks->timer = NULL;
        }
    }
}

void finalize_multi_curl_handle(CURLM* handle)
{
    if (handle != NULL) {
        curl_multi_cleanup(handle);
    }
}


value hxcurl_multi_add_handle(value multi_curl, value easy_curl)
{
    val_check_kind(multi_curl, k_multi_curl);
    val_check_kind(multi_curl, k_easy_curl);

    CURLMcode ret = curl_multi_add_handle(val_multi_handle(multi_curl), val_easy_handle(easy_curl));
    if (ret != CURLM_OK) {
        curl_multi_error(ret);
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_multi_add_handle, 2);


value hxcurl_multi_cleanup(value curl)
{
    val_check_kind(curl, k_multi_curl);

    MCURL* mcurl = val_multi_curl(curl);
    if (mcurl->cleanup) {
        finalize_multi_curl_callbacks(mcurl->callbacks);
        CURLMcode ret = curl_multi_cleanup(mcurl->handle);
        if (ret == CURLM_OK) {
            mcurl->cleanup = false;
        } else {
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
        MCURL* mcurl     = malloc_multi_curl();
        mcurl->callbacks = malloc_multi_callbacks();
        mcurl->cleanup   = true;
        mcurl->handle    = handle;
        val = alloc_multi_curl(mcurl);
        val_gc(val, finalize_multi_curl_abstract);
    }

    return val;
}
DEFINE_PRIM(hxcurl_multi_init, 0);


value hxcurl_multi_perform(value curl)
{
    val_check_kind(curl, k_multi_curl);

    value val;
    int running_handles;
    CURLMcode ret = curl_multi_perform(val_multi_handle(curl), &running_handles);
    if (ret == CURLM_OK) {
        val = alloc_int(running_handles);
    } else {
        curl_multi_error(ret);
        val = alloc_null();
    }

    return val;
}
DEFINE_PRIM(hxcurl_multi_perform, 1);


value hxcurl_multi_remove_handle(value multi_curl, value easy_curl)
{
    val_check_kind(multi_curl, k_multi_curl);
    val_check_kind(multi_curl, k_easy_curl);

    CURLMcode ret = curl_multi_remove_handle(val_multi_handle(multi_curl), val_easy_handle(easy_curl));
    if (ret != CURLM_OK) {
        curl_multi_error(ret);
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_multi_remove_handle, 2);


value hxcurl_multi_setopt(value curl, value curlopt, value optval)
{
    val_check_kind(curl, k_multi_curl);
    val_check(curlopt, int);

    MCURL* mcurl = val_multi_curl(curl);
    CURLMcode ret;
    switch (val_int(curlopt)) {
        case CURLMOPT_SOCKETDATA: {
            mcurl->data->socket = optval;
            ret = CURLM_OK;
            break;
        }
        case CURLMOPT_SOCKETFUNCTION: {
            root_set(&mcurl->callbacks->socket, optval);
            //ret = curl_multi_setopt(mcurl->handle, CURLMOPT_SOCKETFUNCTION, socket_callback);
            if (ret == CURLM_OK) {
                ret = curl_multi_setopt(mcurl->handle, CURLMOPT_SOCKETDATA, mcurl);
            }
            break;
        }
        case CURLMOPT_TIMERDATA: {
            mcurl->data->timer = optval;
            ret = CURLM_OK;
            break;
        }
        case CURLMOPT_TIMERFUNCTION: {
            root_set(&mcurl->callbacks->timer, optval);
            //ret = curl_multi_setopt(mcurl->handle, CURLMOPT_TIMERFUNCTION, timeout_callback);
            if (ret == CURLE_OK) {
                ret = curl_multi_setopt(mcurl->handle, CURLMOPT_TIMERDATA, mcurl);
            }
            break;
        }
        default: {
            // TODO
            #define VAL_FLOAT  1
            #define VAL_INT    0xFF
            #define VAL_STRING 3

            switch (val_type(optval)) {
                case VAL_FLOAT: {
                    ret = curl_multi_setopt(mcurl->handle, (CURLMoption)val_int(curlopt), val_float(optval));
                    break;
                }
                case VAL_INT: {
                    ret = curl_multi_setopt(mcurl->handle, (CURLMoption)val_int(curlopt), val_int(optval));
                    break;
                }
                case VAL_STRING: {
                    ret = curl_multi_setopt(mcurl->handle, (CURLMoption)val_int(curlopt), val_string(optval));
                    break;
                }
                default: { neko_error(); }
            }
        }
    }

    if (ret != CURLM_OK) {
        curl_multi_error(ret);
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_multi_setopt, 3);


value hxcurl_multi_timeout(value curl)
{
    val_check_kind(curl, k_multi_curl);

    value val;
    long timeout;
    CURLMcode ret = curl_multi_timeout(val_multi_handle(curl), &timeout);
    if (ret == CURLM_OK) {
        val = alloc_int(timeout);
    } else {
        curl_multi_error(ret);
        val = alloc_null();
    }

    return val;
}
DEFINE_PRIM(hxcurl_multi_timeout, 1);

} // extern "C"
