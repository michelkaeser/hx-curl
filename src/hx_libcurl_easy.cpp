#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE
#include <stdlib.h>
#include <hx/CFFI.h>
#include <curl/curl.h>

#include "hx_libcurl_easy.hpp"

extern "C" {

// http://curl.haxx.se/libcurl/c/CURLOPT_DEBUGFUNCTION.html
static int debug_callback(CURL*, curl_infotype, char*, size_t, void*);
// http://curl.haxx.se/libcurl/c/CURLOPT_HEADERFUNCTION.html
static size_t header_callback(char*, size_t, size_t, void*);
// http://curl.haxx.se/libcurl/c/CURLOPT_XFERINFOFUNCTION.html
static int progress_callback(void*, double, double, double, double);
// http://curl.haxx.se/libcurl/c/CURLOPT_READFUNCTION.html
static size_t read_callback(char*, size_t, size_t, void*);
// http://curl.haxx.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
static size_t write_callback(char*, size_t, size_t, void*);


__attribute__((constructor)) void init(void)
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

__attribute__((destructor)) void fini(void)
{
    curl_global_cleanup();
}


static int debug_callback(CURL* handle, curl_infotype type, char* data, size_t size, void* userptr)
{
    ECURL* ecurl = (ECURL*)userptr;
    buffer buf = alloc_buffer(NULL);
    buffer_append_sub(buf, data, size);
    val_call1(ecurl->callbacks->debug->get(), buffer_val(buf));

    return 0;
}


void finalize_easy_curl_abstract(value curl)
{
    if (val_is_easy_curl(curl)) {
        ECURL* ecurl = val_easy_curl(curl);
        if (ecurl != NULL) {
            if (ecurl->cleanup) {
                finalize_easy_curl_handle(ecurl->handle);
                ecurl->handle = NULL;
            }
            ecurl->cleanup = (bool)NULL;
            curl_free(ecurl->errbuf);
            ecurl->errbuf = NULL;
            finalize_easy_curl_callbacks(ecurl->callbacks);
            ecurl->callbacks = NULL;
            finalize_easy_curl_data(ecurl->data);
            ecurl->data = NULL;
            free(ecurl);
            ecurl = NULL;
        }
    }
}

void finalize_easy_curl_callbacks(ECALLBACKS* callbacks)
{
    if (callbacks != NULL) {
        if (callbacks->debug != NULL) {
            delete callbacks->debug;
            callbacks->debug = NULL;
        }
        if (callbacks->header != NULL) {
            delete callbacks->header;
            callbacks->header = NULL;
        }
        if (callbacks->progress != NULL) {
            delete callbacks->progress;
            callbacks->progress = NULL;
        }
        if (callbacks->read != NULL) {
            delete callbacks->read;
            callbacks->read = NULL;
        }
        if (callbacks->write != NULL) {
            delete callbacks->write;
            callbacks->write = NULL;
        }
    }
}

void finalize_easy_curl_data(EDATA* data)
{
    if (data != NULL) {
        if (data->debug != NULL) {
            free(data->debug);
            data->debug = NULL;
        }
        if (data->header != NULL) {
            free(data->header);
            data->header = NULL;
        }
        if (data->progress != NULL) {
            free(data->progress);
            data->progress = NULL;
        }
        if (data->read != NULL) {
            free(data->read);
            data->read = NULL;
        }
        if (data->write != NULL) {
            free(data->write);
            data->write = NULL;
        }
    }
}

void finalize_easy_curl_handle(CURL* handle)
{
    if (handle != NULL) {
        curl_easy_cleanup(handle);
    }
}


static size_t header_callback(char* buf, size_t size, size_t nitems, void* userdata)
{
    const size_t length = size * nitems;
    ECURL* ecurl = (ECURL*)userdata;
    buffer b   = alloc_buffer(NULL);
    buffer_append_sub(b, buf, length);
    val_call1(ecurl->callbacks->header->get(), buffer_val(b));

    return length;
}


value hxcurl_easy_cleanup(value curl)
{
    val_check_kind(curl, k_easy_curl);

    ECURL* ecurl = val_easy_curl(curl);
    if (ecurl->cleanup) {
        finalize_easy_curl_callbacks(ecurl->callbacks);
        finalize_easy_curl_data(ecurl->data);
        finalize_easy_curl_handle(ecurl->handle);
        ecurl->cleanup = false;
    } else {
        neko_error();
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_easy_cleanup, 1);


value hxcurl_easy_duphandle(value curl)
{
    val_check_kind(curl, k_easy_curl);

    value dval;
    ECURL* ecurl  = val_easy_curl(curl);
    CURL* dhandle = curl_easy_duphandle(ecurl->handle);
    if (dhandle == NULL) {
        neko_error();
        dval = alloc_null();
    } else {
        // TODO: illegal hardware instruction  neko Debug.n
        ECURL* dup   = malloc_easy_curl();
        memcpy(dup->callbacks, ecurl->callbacks, sizeof(ECALLBACKS));
        dup->cleanup = ecurl->cleanup;
        memcpy(dup->data, ecurl->data, sizeof(EDATA));
        dup->errbuf  = malloc_curl_errbuf();
        dup->handle  = dhandle;
        dval = alloc_easy_curl(dup);
        val_gc(dval, finalize_easy_curl_abstract);
    }

    return dval;
}
DEFINE_PRIM(hxcurl_easy_duphandle, 1);


value hxcurl_easy_escape(value curl, value str)
{
    val_check_kind(curl, k_easy_curl);
    val_check(str, string);

    value val;
    char* escaped = curl_easy_escape(val_easy_handle(curl), val_string(str), val_strlen(str));
    if (escaped == NULL) {
        neko_error();
        val = alloc_null();
    } else {
        val = alloc_string(escaped);
    }
    curl_free(escaped);

    return val;
}
DEFINE_PRIM(hxcurl_easy_escape, 2);


// value hxcurl_easy_getinfo_string(value curl, value info)
// {
//     val_check_kind(curl, k_easy_curl);
//     val_check(info, int);

//     value val;
//     char* info_val;
//     CURLcode ret = curl_easy_getinfo(val_easy_handle(curl), (CURLINFO)val_int(info), &info_val);
//     if (ret == CURLE_OK) {
//         val = alloc_string(info_val);
//     } else {
//         curl_easy_error(ret);
//         val = alloc_null();
//     }

//     return val;
// }
// DEFINE_PRIM(hxcurl_easy_getinfo_string, 2);


value hxcurl_easy_init(void)
{
    value val;
    CURL* handle = curl_easy_init();
    if (handle == NULL) {
        neko_error();
        val = alloc_null();
    } else {
        ECURL* ecurl     = malloc_easy_curl();
        ecurl->callbacks = malloc_easy_callbacks();
        ecurl->cleanup   = true;
        ecurl->data      = malloc_easy_data();
        ecurl->errbuf    = malloc_curl_errbuf();
        ecurl->handle    = handle;
        curl_easy_setopt(ecurl->handle, CURLOPT_ERRORBUFFER, ecurl->errbuf);
        val = alloc_easy_curl(ecurl);
        val_gc(val, finalize_easy_curl_abstract);
    }

    return val;
}
DEFINE_PRIM(hxcurl_easy_init, 0);


value hxcurl_easy_pause(value curl, value bitmask)
{
    val_check_kind(curl, k_easy_curl);
    val_check(bitmask, int);

    CURLcode ret = curl_easy_pause(val_easy_handle(curl), val_int(bitmask));
    if (ret != CURLE_OK) {
        curl_easy_error(ret);
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_easy_pause, 2);


value hxcurl_easy_perform(value curl)
{
    val_check_kind(curl, k_easy_curl);

    value val;
    CURLcode ret;
    ECURL* ecurl = val_easy_curl(curl);
    buffer buf   = alloc_buffer(NULL);

    ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEDATA, buf);
    if (ret == CURLE_OK) {
        ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEFUNCTION, write_callback);
        if (ret == CURLE_OK) {
            ret = curl_easy_perform(ecurl->handle);
            if (ret == CURLE_OK) {
                val = buffer_val(buf);
            }
        }
    }

    if (ret != CURLE_OK) {
        curl_easy_error(ret);
        val = alloc_null();
    }

    return val;
}
DEFINE_PRIM(hxcurl_easy_perform, 1);


value hxcurl_easy_recv(value curl, value length)
{
    val_check_kind(curl, k_easy_curl);
    val_check(length, int);

    value val;
    size_t received;
    const size_t buflen = val_int(length);
    char buf[buflen];

    CURLcode ret = curl_easy_recv(val_easy_handle(curl), buf, buflen, &received);
    if (ret == CURLE_OK) {
        buffer b = alloc_buffer(NULL);
        buffer_append_sub(b, buf, received);
        val = buffer_val(b);
    } else {
        curl_easy_error(ret);
    }

    return val;
}
DEFINE_PRIM(hxcurl_easy_recv, 2);


value hxcurl_easy_reset(value curl)
{
    val_check_kind(curl, k_easy_curl);

    ECURL* ecurl = val_easy_curl(curl);
    curl_easy_reset(ecurl->handle);
    ecurl->cleanup = true;

    return alloc_null();
}
DEFINE_PRIM(hxcurl_easy_reset, 1);


value hxcurl_easy_send(value curl, value bytes, value length)
{
    val_check_kind(curl, k_easy_curl);
    val_check(length, int);

    const char* msg;
    if (val_is_string(bytes)) { // Neko
        msg = val_string(bytes);
    } else { // C++
        buffer buf = val_to_buffer(bytes);
        msg        = buffer_data(buf);
    }

    value val;
    size_t sent;
    CURLcode ret = curl_easy_send(val_easy_handle(curl), msg, val_int(length), &sent);
    if (ret == CURLE_OK) {
        val = alloc_int(sent);
    } else {
        curl_easy_error(ret);
        val = alloc_null();
    }

    return val;
}
DEFINE_PRIM(hxcurl_easy_send, 3);


value hxcurl_easy_setopt(value curl, value curlopt, value optval)
{
    val_check_kind(curl, k_easy_curl);
    val_check(curlopt, int);

    ECURL* ecurl = val_easy_curl(curl);
    CURLcode ret;
    if (val_is_number(optval)) {
        ret = curl_easy_setopt(ecurl->handle, (CURLoption)val_int(curlopt), val_number(optval));
    } else if (val_is_string(optval)) {
        ret = curl_easy_setopt(ecurl->handle, (CURLoption)val_int(curlopt), val_string(optval));
    } else if (val_is_function(optval)) {
        switch (val_int(curlopt)) {
            case CURLOPT_DEBUGFUNCTION: {
                //val_check_function(optval, 1);
                root_set(&ecurl->callbacks->debug, optval);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_DEBUGFUNCTION, debug_callback);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_DEBUGDATA, ecurl);
                break;
            }
            case CURLOPT_HEADERFUNCTION: {
                //val_check_function(optval, 1);
                root_set(&ecurl->callbacks->header, optval);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_HEADERFUNCTION, header_callback);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_HEADERDATA, ecurl);
                break;
            }
            case CURLOPT_PROGRESSFUNCTION: {
                //val_check_function(optval, 4);
                root_set(&ecurl->callbacks->progress, optval);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_PROGRESSFUNCTION, progress_callback);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_PROGRESSDATA, ecurl);
                break;
            }
            case CURLOPT_READFUNCTION: {
                //val_check_function(optval, 4);
                root_set(&ecurl->callbacks->progress, optval);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_READFUNCTION, read_callback);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_READDATA, ecurl);
                break;
            }
            case CURLOPT_WRITEFUNCTION: {
                //val_check_function(optval, 4);
                root_set(&ecurl->callbacks->progress, optval);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEFUNCTION, write_callback);
                ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEDATA, ecurl);
                break;
            }
            default: { neko_error(); }
        }
    } else {
        neko_error(); // TODO: struct or object -> not yet implemented
    }

    if (ret != CURLE_OK) {
        curl_easy_error(ret);
    }

    return alloc_null();
}
DEFINE_PRIM(hxcurl_easy_setopt, 3);


value hxcurl_easy_unescape(value curl, value str)
{
    val_check_kind(curl, k_easy_curl);
    val_check(str, string);

    value val;
    char* unescaped = curl_easy_unescape(val_easy_handle(curl), val_string(str), val_strlen(str), NULL);
    if (unescaped == NULL) {
        neko_error();
        val = alloc_null();
    } else {
        val = alloc_string(unescaped);
    }
    curl_free(unescaped);

    return val;
}
DEFINE_PRIM(hxcurl_easy_unescape, 2);


static int progress_callback(void* clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
    ECURL* ecurl = (ECURL*)clientp;
    value arr    = alloc_array(4);
    value* args  = val_array_value(arr);

    // TODO: int64?
    args[0] = alloc_int(dltotal);
    args[1] = alloc_int(dlnow);
    args[2] = alloc_int(ultotal);
    args[3] = alloc_int(ulnow);

    val_callN(ecurl->callbacks->progress->get(), args, 4);

    return 0;
}


static size_t read_callback(char* buffer, size_t size, size_t nitems, void* instream)
{
    return 0;
    // fill buffer with size * nitems bytes from instream
}


static size_t write_callback(char* str, size_t size, size_t nmemb, void* userdata)
{
    const size_t length = size * nmemb;
    // ECURL* ecurl = (ECURL*)userdata;
    // buffer buf   = alloc_buffer(NULL);
    // buffer_append_sub(buf, str, length);
    // val_call1(ecurl->callbacks->write->get(), buffer_val(buf));

    buffer buf = (buffer)userdata;
    if (length > 0) {
        buffer_append_sub(buf, str, length);
    }

    return length;
}

} // extern "C"
