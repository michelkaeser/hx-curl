#ifndef __HX_LIBCURL_HPP
#define __HX_LIBCURL_HPP

#define  IMPLEMENT_API
#define  NEKO_COMPATIBLE 1
#include <stdlib.h>
#include <hx/CFFI.h>
#include <curl/curl.h>

#ifdef __cplusplus
extern "C" {
#endif
    //####################################################
    // KIND DEFINITIONS
    //####################################################
    DEFINE_KIND(k_curl_struct);
    // CURL(INFO) structs
    DEFINE_KIND(k_curl_certinfo);
    DEFINE_KIND(k_curl_slist);
    DEFINE_KIND(k_curl_tlsinfo);


    //####################################################
    // TYPEDEFS
    //####################################################
    // typedef for the struct we bring up to C++/Neko
    /*extern */ typedef struct S_CURL {
        bool  cleanup;
        char* errbuf;
        CURL* handle;
    } SCURL;

    // typedef for the union used e.g. in getinfo()
    /*extern */ typedef union U_INFOTYPES {
        char*  c;
        double d;
        long   l;
        struct curl_certinfo* certinfo;
        struct curl_slist*    slist;
        struct curl_tlsinfo*  tlsinfo;
    } UInfoTypes;


    //####################################################
    // HELPER MACROS
    //####################################################
    #define alloc_curl_struct(v)     alloc_abstract(k_curl_struct, v)
    #define malloc_curl_struct()     (SCURL*)malloc(sizeof(SCURL))
    #define val_curl_struct(v)       (SCURL*)val_data(v)
    #define val_is_curl_struct(v)    val_is_kind(v, k_curl_struct)
    // CURL(INFO) structs
    #define alloc_curl_certinfo(v)   alloc_abstract(k_curl_certinfo, v)
    #define alloc_curl_slist(v)      alloc_abstract(k_curl_slist, v)
    #define alloc_curl_tlsinfo(v)    alloc_abstract(k_curl_tlsinfo, v)
    #define val_curl_certinfo(v)     (struct curl_certinfo*)val_data(v)
    #define val_curl_slist(v)        (struct curl_slist*)val_data(v)
    #define val_curl_tlsinfo(v)      (struct curl_tlsinfo*)val_data(v)
    #define val_is_curl_certinfo(v)  val_is_kind(v, k_curl_certinfo)
    #define val_is_curl_slist(v)     val_is_kind(v, k_curl_slist)
    #define val_is_curl_tlsinfo(v)   val_is_kind(v, k_curl_tlsinfo)


    //####################################################
    // HELPER FUNCTIONS
    //####################################################
    // TODO
    inline value curl_certinfo_to_val(struct curl_certinfo* info)
    {
        value val = alloc_null();
        // if (info == NULL) {
        //     val = alloc_null();
        // } else {
        //     int length = info->num_of_certs;
        //     val = alloc_array(length);
        //     for (int i = 0; i < length; ++length) {
        //         struct curl_slist* slist;
        //         for (slist = info->certinfo[i]; slist; slist = slist->next) {
        //             val_array_set_i(val, i, alloc_string(slist->data));
        //         }
        //     }
        // }

        return val;
    }

    // TODO
    inline value curl_slist_to_val(struct curl_slist* slist)
    {
        value val = alloc_null();
        // if (slist == NULL) {
        //     val = alloc_null();
        // } else {
        //     buffer buf = alloc_buffer(NULL);
        //     while (slist->next != NULL) {
        //         buffer_append(buf, slist->data);
        //         buffer_append(buf, "\\.\\");
        //     }
        //
        //     val = buffer_to_string(buf);
        // }

        return val;
    }

    inline value curl_tlsinfo_to_val(struct curl_tlsinfo* tlsinfo)
    {
        if (tlsinfo == NULL) {
            return alloc_null();
        } else {
            return alloc_null();
        }
    }

    // Helper function to allocate an error buffer to be set with setopt
    inline char* malloc_curl_errbuf(void)
    {
        char* errbuf = (char*)malloc(sizeof(char) * (CURL_ERROR_SIZE + 1));
        errbuf[CURL_ERROR_SIZE] = '\0';

        return errbuf;
    }


    //####################################################
    // GC FUNCTIONS
    //####################################################
    // GC finalizer to free 'CURL*' called by finalize_curl_struct
    extern void finalize_curl_handle(CURL*);
    // GC finalizer to free 'S_CURL' called when a 'k_curl_struct' gets garbage collected
    inline void finalize_curl_struct(value val)
    {
        if (val_is_curl_struct(val)) {
            SCURL* curl = val_curl_struct(val);
            if (curl->cleanup) {
                finalize_curl_handle(curl->handle);
                curl->handle = NULL;
            }
            curl->cleanup = (bool)NULL;
            curl_free(curl->errbuf);
            curl->errbuf = NULL;
            free(curl);
            curl = NULL;
        }
    }
#ifdef __cplusplus
}
#endif

#endif
