#define  NEKO_COMPATIBLE
#include <stdlib.h>
#include <hx/CFFI.h>
#include <curl/curl.h>

#include "hxcurl/curl_share.hpp"

extern "C" {

DEFINE_KIND(k_share_curl);


static void lock_function(CURL*, curl_lock_data, curl_lock_access, void*);
static void unlock_function(CURL*, curl_lock_data, void*);


void finalize_share_curl_abstract(value curl)
{
    if (val_is_share_curl(curl)) {
        SCURL* scurl = val_share_curl(curl);
        if (scurl != NULL) {
            if (scurl->cleanup) {
                finalize_share_curl_handle(scurl->handle);
                scurl->handle = NULL;
            }
            scurl->cleanup = (bool)NULL;
            finalize_share_curl_callbacks(scurl->callbacks);
            scurl->callbacks = NULL;
        }
    }
}

void finalize_share_curl_callbacks(SCALLBACKS* callbacks)
{
    if (callbacks != NULL) {
        if (callbacks->lock != NULL) {
            delete callbacks->lock;
            callbacks->lock = NULL;
        }
        if (callbacks->unlock != NULL) {
            delete callbacks->unlock;
            callbacks->unlock = NULL;
        }
    }
}

void finalize_share_curl_handle(CURLSH* handle)
{
    if (handle != NULL) {
        curl_share_cleanup(handle);
    }
}


value hxcurl_share_cleanup(value curl)
{
    val_check_kind(curl, k_share_curl);

    SCURL* scurl = val_share_curl(curl);
    if (scurl->cleanup) {
        finalize_share_curl_callbacks(scurl->callbacks);
        finalize_share_curl_handle(scurl->handle);
        scurl->cleanup = false;
    } else {
        neko_error();
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_share_cleanup, 1);


value hxcurl_share_init(void)
{
    value val;
    CURLSH* handle = curl_share_init();
    if (handle == NULL) {
        neko_error();
        val = alloc_null();
    } else {
        SCURL* scurl     = malloc_share_curl();
        scurl->callbacks = malloc_share_callbacks();
        scurl->cleanup   = true;
        scurl->data      = alloc_null();
        scurl->handle    = handle;
        val = alloc_share_curl(scurl);
        val_gc(val, finalize_share_curl_abstract);
    }

    return val;
}
DEFINE_PRIM(hxcurl_share_init, 0);


value hxcurl_share_setopt(value curl, value curlopt, value optval)
{
    val_check_kind(curl, k_share_curl);
    val_check(curlopt, int);

    SCURL* scurl = val_share_curl(curl);
    CURLSHcode ret;
    switch (val_int(curlopt)) {
        case CURLSHOPT_LOCKFUNC: {
            root_set(&scurl->callbacks->lock, optval);
            ret = curl_share_setopt(scurl->handle, CURLSHOPT_LOCKFUNC, lock_function);
            if (ret == CURLSHE_OK) {
                ret = curl_share_setopt(scurl->handle, CURLSHOPT_USERDATA, scurl);
            }
            break;
        }
        case CURLSHOPT_UNLOCKFUNC: {
            root_set(&scurl->callbacks->unlock, optval);
            ret = curl_share_setopt(scurl->handle, CURLSHOPT_LOCKFUNC, unlock_function);
            if (ret == CURLSHE_OK) {
                ret = curl_share_setopt(scurl->handle, CURLSHOPT_USERDATA, scurl);
            }
            break;
        }
        case CURLSHOPT_USERDATA: {
            scurl->data = optval;
            break;
        }
        default: {
            val_check(optval, int);
            ret = curl_share_setopt(scurl->handle, (CURLSHoption)val_int(curlopt), val_int(optval));
        }
    }

    if (ret != CURLSHE_OK) {
        curl_share_error(ret);
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_share_setopt, 3);


static void lock_function(CURL* handle, curl_lock_data data, curl_lock_access access, void* userptr)
{
    SCURL* scurl = (SCURL*)userptr;
    if (scurl->data == alloc_null()) {
        //ret = val_call1(scurl->callbacks->lock->get(), ...);
    } else {
        //ret = val_call2(scurl->callbacks->lock->get(), ..., scurl->data);
    }
}


static void unlock_function(CURL* handle, curl_lock_data data, void* userptr)
{
    SCURL* scurl = (SCURL*)userptr;
    if (scurl->data == alloc_null()) {
        //ret = val_call1(scurl->callbacks->unlock->get(), ...);
    } else {
        //ret = val_call2(scurl->callbacks->unlock->get(), ..., scurl->data);
    }
}

} // extern "C"
