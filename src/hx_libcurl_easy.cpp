#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE
#include <stdlib.h>
#include <hx/CFFI.h>
#include <curl/curl.h>

#include "hx_libcurl_easy.hpp"

extern "C" {

static value hxcurl_easy_getinfo_double(value, value);
static value hxcurl_easy_getinfo_long(value, value);
static value hxcurl_easy_getinfo_string(value, value);

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
static size_t write_callback_default(char*, size_t, size_t, void*);


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

    value ret;
    if (ecurl->data->debug == NULL) {
        ret = val_call1(ecurl->callbacks->debug->get(), buffer_val(buf));
    } else {
        ret = val_call2(ecurl->callbacks->debug->get(), buffer_val(buf), ecurl->data->debug);
    }

    return val_int(ret);
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
            // TODO: illegal hardware instruction or segmentation fault
            finalize_easy_curl_callbacks(ecurl->callbacks);
            ecurl->callbacks = NULL;
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

    value ret;
    if (ecurl->data->header == NULL) {
        ret = val_call1(ecurl->callbacks->header->get(), buffer_val(b));
    } else {
        ret = val_call2(ecurl->callbacks->header->get(), buffer_val(b), ecurl->data->header);
    }

    return val_int(ret);
}


value hxcurl_easy_cleanup(value curl)
{
    val_check_kind(curl, k_easy_curl);

    ECURL* ecurl = val_easy_curl(curl);
    if (ecurl->cleanup) {
        finalize_easy_curl_callbacks(ecurl->callbacks);
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
        ECURL* dup     = malloc_easy_curl();
        dup->callbacks = malloc_easy_callbacks();
        memcpy(dup->callbacks, ecurl->callbacks, sizeof(ECALLBACKS));
        dup->cleanup = ecurl->cleanup;
        dup->data    = malloc_easy_data();
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


value hxcurl_easy_getinfo(value curl, value info, value type)
{
    val_check_kind(curl, k_easy_curl);
    val_check(info, int);
    val_check(type, int);

    value val;
    switch (val_int(type)) {
        case 0: {
            val = hxcurl_easy_getinfo_string(curl, info);
            break;
        }
        case 1: {
            val = hxcurl_easy_getinfo_double(curl, info);
            break;
        }
        case 2: {
            val = hxcurl_easy_getinfo_long(curl, info);
            break;
        }
        default: {
            // TODO: implement the three struct info types
            neko_error();
            val = alloc_null();
        }
    }

    return val;
}
DEFINE_PRIM(hxcurl_easy_getinfo, 3);

static value hxcurl_easy_getinfo_double(value curl, value info)
{
    value val;
    double info_val;
    CURLcode ret = curl_easy_getinfo(val_easy_handle(curl), (CURLINFO)val_int(info), &info_val);
    if (ret == CURLE_OK) {
        val = alloc_float(info_val);
    } else {
        curl_easy_error(ret);
        val = alloc_null();
    }

    return val;
}

static value hxcurl_easy_getinfo_long(value curl, value info)
{
    value val;
    long info_val;
    CURLcode ret = curl_easy_getinfo(val_easy_handle(curl), (CURLINFO)val_int(info), &info_val);
    if (ret == CURLE_OK) {
        val = alloc_int(info_val);
    } else {
        curl_easy_error(ret);
        val = alloc_null();
    }

    return val;
}

static value hxcurl_easy_getinfo_string(value curl, value info)
{
    value val;
    char* info_val;
    CURLcode ret = curl_easy_getinfo(val_easy_handle(curl), (CURLINFO)val_int(info), &info_val);
    if (ret == CURLE_OK) {
        val = alloc_string(info_val);
    } else {
        curl_easy_error(ret);
        val = alloc_null();
    }

    return val;
}


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
    CURLcode ret = CURLE_OK;
    buffer buf   = alloc_buffer(NULL);
    ECURL* ecurl = val_easy_curl(curl);

    if (ecurl->callbacks->write == NULL) {
        if (ecurl->data->write == NULL) {
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEDATA, buf);
        } else {
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEDATA, /* TODO: ecurl->data->write */ buf);
        }
        if (ret == CURLE_OK) {
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEFUNCTION, write_callback_default);
        }
    }

    if (ret == CURLE_OK) {
        ret = curl_easy_perform(ecurl->handle);
        if (ret == CURLE_OK) {
            val = buffer_val(buf);
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
    switch (val_int(curlopt)) {
        case CURLOPT_DEBUGDATA: {
            ecurl->data->debug = optval;
            ret = CURLE_OK;
            break;
        }
        case CURLOPT_DEBUGFUNCTION: {
            root_set(&ecurl->callbacks->debug, optval);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_DEBUGFUNCTION, debug_callback);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_DEBUGDATA, ecurl);
            break;
        }
        case CURLOPT_HEADERDATA: {
            ecurl->data->header = optval;
            ret = CURLE_OK;
            break;
        }
        case CURLOPT_HEADERFUNCTION: {
            root_set(&ecurl->callbacks->header, optval);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_HEADERFUNCTION, header_callback);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_HEADERDATA, ecurl);
            break;
        }
        case CURLOPT_PROGRESSDATA: {
            ecurl->data->progress = optval;
            ret = CURLE_OK;
            break;
        }
        case CURLOPT_PROGRESSFUNCTION: {
            root_set(&ecurl->callbacks->progress, optval);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_PROGRESSFUNCTION, progress_callback);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_PROGRESSDATA, ecurl);
            break;
        }
        case CURLOPT_READDATA: {
            ecurl->data->read = optval;
            ret = CURLE_OK;
            break;
        }
        case CURLOPT_READFUNCTION: {
            root_set(&ecurl->callbacks->progress, optval);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_READFUNCTION, read_callback);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_READDATA, ecurl);
            break;
        }
        case CURLOPT_WRITEDATA: {
            ecurl->data->write = optval;
            ret = CURLE_OK;
            break;
        }
        case CURLOPT_WRITEFUNCTION: {
            root_set(&ecurl->callbacks->write, optval);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEFUNCTION, write_callback);
            ret = curl_easy_setopt(ecurl->handle, CURLOPT_WRITEDATA, ecurl);
            break;
        }
        default: {
            switch (val_type(optval)) {
                case VAL_FLOAT: {
                    ret = curl_easy_setopt(ecurl->handle, (CURLoption)val_int(curlopt), val_float(optval));
                    break;
                }
                case VAL_INT: {
                    ret = curl_easy_setopt(ecurl->handle, (CURLoption)val_int(curlopt), val_int(optval));
                    break;
                }
                case VAL_STRING: {
                    ret = curl_easy_setopt(ecurl->handle, (CURLoption)val_int(curlopt), val_string(optval));
                    break;
                }
                default: { neko_error(); }
            }
        }
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

    value arr;
    if (ecurl->data->progress == NULL) {
        arr = alloc_array(4);
    } else {
        arr = alloc_array(5);
    }
    value* args  = val_array_value(arr);
    args[0] = alloc_float(dltotal);
    args[1] = alloc_float(dlnow);
    args[2] = alloc_float(ultotal);
    args[3] = alloc_float(ulnow);

    value ret;
    if (ecurl->data->progress == NULL) {
        ret = val_callN(ecurl->callbacks->progress->get(), args, 4);
    } else {
        args[4] = ecurl->data->progress;
        ret = val_callN(ecurl->callbacks->progress->get(), args, 5);
    }

    return val_int(ret);
}


static size_t read_callback(char* buffer, size_t size, size_t nitems, void* instream)
{
    return 0;
    // fill buffer with size * nitems bytes from instream
}


static size_t write_callback(char* str, size_t size, size_t nmemb, void* userdata)
{
    const size_t length = size * nmemb;
    ECURL* ecurl = (ECURL*)userdata;
    int written;
    if (length > 0) {
        value ret;
        buffer buf = alloc_buffer(NULL);
        buffer_append_sub(buf, str, length);
        if (ecurl->data->write == NULL) {
            ret = val_call1(ecurl->callbacks->write->get(), buffer_val(buf));
        } else {
            ret = val_call2(ecurl->callbacks->write->get(), buffer_val(buf), ecurl->data->write);
        }
        written = val_int(ret);
    } else {
        written = length;
    }

    return written;
}


static size_t write_callback_default(char* str, size_t size, size_t nmemb, void* userdata)
{
    const size_t length = size * nmemb;
    buffer buf = (buffer)userdata;
    if (length > 0) {
        buffer_append_sub(buf, str, length);
    }

    return length;
}

} // extern "C"
