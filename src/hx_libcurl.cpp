#include "hx_libcurl.hpp"
#include <curl/curl.h>

extern "C"
{
    void finalize_curl_handle(value handle)
    {
        curl_easy_cleanup(val_curl(handle));
    }
}
