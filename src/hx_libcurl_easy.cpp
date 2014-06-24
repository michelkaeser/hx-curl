#include "hx_libcurl_easy.hpp"

extern "C"
{
    //####################################################
    // INITIALIZERS / FINALIZERS
    //####################################################
    __attribute__((constructor)) void init(void)
    {
        curl_global_init(CURL_GLOBAL_DEFAULT);
    }

    __attribute__((destructor)) void fini(void)
    {
        curl_global_cleanup();
    }


    //####################################################
    // HELPER FUNCTIONS
    //####################################################
    // Write callback function for curl_easy_perform set through setopt
    static size_t write_callback(char* str, size_t size, size_t nmemb, void* userdata)
    {
        buffer buf = (buffer)userdata;
        const size_t realsize = size * nmemb;
        if (realsize > 0) {
            buffer_append_sub(buf, str, realsize);
        }

        return realsize;
    }


    //####################################################
    // GC FUNCTIONS
    //####################################################
    // GC finalizer to free 'CURL*' called by finalize_curl_struct
    void finalize_curl_handle(CURL* curl)
    {
        if (curl != NULL) {
            curl_easy_cleanup(curl);
        }
    }


    //####################################################
    // C FFI IMPLEMENTATIONS
    //####################################################
    // http://curl.haxx.se/libcurl/c/curl_easy_cleanup.html
    static value hxcurl_easy_cleanup(value val)
    {
        val_check_kind(val, k_curl_struct);

        SCURL* curl = val_curl_struct(val);
        if (curl->cleanup) {
            curl_easy_cleanup(curl->handle);
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
        SCURL* curl = val_curl_struct(val);
        CURL* dhandle = curl_easy_duphandle(curl->handle);
        if (dhandle == NULL) {
            neko_error();
            dval = alloc_null();
        } else {
            S_CURL* dup  = malloc_curl_struct();
            dup->cleanup = curl->cleanup;
            dup->errbuf  = malloc_curl_errbuf();
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
    static value hxcurl_easy_getinfo(value curl, value info, value type)
    {
        val_check_kind(curl, k_curl_struct);
        val_check(info, int);
        val_check(type, int);

        value val;
        CURLcode ret;
        UInfoTypes ptr;
        switch (val_int(type)) {
            case 0: {
                ret = curl_easy_getinfo((val_curl_struct(curl))->handle, (CURLINFO)val_int(info), &ptr.c);
                val = alloc_string(ptr.c);
                break;
            }
            case 1: {
                ret = curl_easy_getinfo((val_curl_struct(curl))->handle, (CURLINFO)val_int(info), &ptr.d);
                val = alloc_float(ptr.d);
                break;
            }
            case 2: {
                ret = curl_easy_getinfo((val_curl_struct(curl))->handle, (CURLINFO)val_int(info), &ptr.l);
                val = alloc_float(ptr.l);
                break;
            }
            case 5: {
                ret = curl_easy_getinfo((val_curl_struct(curl))->handle, (CURLINFO)val_int(info), &ptr.slist);
                val = curl_slist_to_val(ptr.slist);
                curl_slist_free_all(ptr.slist);
                break;
            }
            case 6: {
                ret = curl_easy_getinfo((val_curl_struct(curl))->handle, (CURLINFO)val_int(info), &ptr.certinfo);
                val = curl_certinfo_to_val(ptr.certinfo);
                break;
            }
            case 7: {
                ret = curl_easy_getinfo((val_curl_struct(curl))->handle, (CURLINFO)val_int(info), &ptr.tlsinfo);
                val = curl_tlsinfo_to_val(ptr.tlsinfo);
                break;
            }
            default: {
                neko_error();
                val = alloc_null();
            }
        }

        if (ret != CURLE_OK) {
            curl_easy_error(ret);
            val = alloc_null();
        }

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_init.html
    static value hxcurl_easy_init(void)
    {
        value val;
        CURL* handle = curl_easy_init();
        if (handle == NULL) {
            neko_error();
            val = alloc_null();
        } else {
            S_CURL* curl  = malloc_curl_struct();
            curl->cleanup = true;
            curl->errbuf  = malloc_curl_errbuf();
            curl->handle  = handle;

            curl_easy_setopt(curl->handle, CURLOPT_ERRORBUFFER, curl->errbuf);
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
        if (ret != CURLE_OK) {
            curl_easy_error(ret);
        }

        return alloc_null();
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_perform.html
    // TODO: what to do when we need read_callback?
    static value hxcurl_easy_perform(value curl)
    {
        val_check_kind(curl, k_curl_struct);

        SCURL* scurl = val_curl_struct(curl);
        buffer buf   = alloc_buffer(NULL);
        value val    = alloc_null();
        CURLcode ret;

        ret = curl_easy_setopt(scurl->handle, CURLOPT_WRITEDATA, buf);
        if (ret != CURLE_OK) {
            curl_easy_error(ret);
        } else {
            ret = curl_easy_setopt(scurl->handle, CURLOPT_WRITEFUNCTION, write_callback);
            if (ret != CURLE_OK) {
                curl_easy_error(ret);
            } else {
                ret = curl_easy_perform(scurl->handle);
                if (ret != CURLE_OK) {
                    curl_easy_error(ret);
                } else {
                    val = buffer_to_string(buf);
                }
            }
        }

        return val;
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
        if (ret != CURLE_OK) {
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

        SCURL* curl = val_curl_struct(val);
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
        if (ret != CURLE_OK) {
            curl_easy_error(ret);
            val = alloc_null();
        } else {
            val = alloc_int(sent);
        }

        return val;
    }

    // http://curl.haxx.se/libcurl/c/curl_easy_setopt.html
    // TODO: function callbacks, structs + objects other than string
    static value hxcurl_easy_setopt(value curl, value curlopt, value optval)
    {
        val_check_kind(curl, k_curl_struct);
        val_check(curlopt, int);

        SCURL* scurl = val_curl_struct(curl);
        CURLcode ret;
        if (val_is_number(optval)) {
            ret = curl_easy_setopt(scurl->handle, (CURLoption)val_int(curlopt), val_number(optval));
        } else if (val_is_string(optval)) {
            ret = curl_easy_setopt(scurl->handle, (CURLoption)val_int(curlopt), val_string(optval));
        } else if (val_is_object(optval)) {
            ret = curl_easy_setopt(scurl->handle, (CURLoption)val_int(curlopt), val_data(optval));
        } else {
            neko_error(); // function, not yet implemented
        }

        if (ret != CURLE_OK) {
            curl_easy_error(ret);
        }

        return alloc_null();
    }

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
DEFINE_PRIM(hxcurl_easy_getinfo, 3);
DEFINE_PRIM(hxcurl_easy_escape, 2);
DEFINE_PRIM(hxcurl_easy_init, 0);
DEFINE_PRIM(hxcurl_easy_pause, 2);
DEFINE_PRIM(hxcurl_easy_perform, 1);
DEFINE_PRIM(hxcurl_easy_recv, 2);
DEFINE_PRIM(hxcurl_easy_reset, 1);
DEFINE_PRIM(hxcurl_easy_send, 2);
DEFINE_PRIM(hxcurl_easy_setopt, 3);
DEFINE_PRIM(hxcurl_easy_unescape, 2);
