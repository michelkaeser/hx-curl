package hxcurl.easy;

/**
 * Abstract enums wrapping the various libcurl info codes.
 *
 * @link http://curl.haxx.se/libcurl/c/curl_easy_getinfo.html
 * @link https://github.com/bagder/curl/blob/ade380a7aa1241fd7a2e16ee0c44fe268b42ff9a/include/curl/curl.h#L2039-L2094
 */
@:enum
abstract CurlInfo(Int) to Int
{
    // Information
    var EFFECTIVE_URL           = (cast STRING) + 1;
    var RESPONSE_CODE           = (cast LONG)   + 2;
    var TOTAL_TIME              = (cast DOUBLE) + 3;
    var NAMELOOKUP_TIME         = (cast DOUBLE) + 4;
    var CONNECT_TIME            = (cast DOUBLE) + 5;
    var PRETRANSFER_TIME        = (cast DOUBLE) + 6;
    var SIZE_UPLOAD             = (cast DOUBLE) + 7;
    var SIZE_DOWNLOAD           = (cast DOUBLE) + 8;
    var SPEED_DOWNLOAD          = (cast DOUBLE) + 9;
    var SPEED_UPLOAD            = (cast DOUBLE) + 10;
    var HEADER_SIZE             = (cast LONG)   + 11;
    var REQUEST_SIZE            = (cast LONG)   + 12;
    var SSL_VERIFYRESULT        = (cast LONG)   + 13;
    var FILETIME                = (cast LONG)   + 14;
    var CONTENT_LENGTH_DOWNLOAD = (cast DOUBLE) + 15;
    var CONTENT_LENGTH_UPLOAD   = (cast DOUBLE) + 16;
    var STARTTRANSFER_TIME      = (cast DOUBLE) + 17;
    var CONTENT_TYPE            = (cast STRING) + 18;
    var REDIRECT_TIME           = (cast DOUBLE) + 19;
    var REDIRECT_COUNT          = (cast LONG)   + 20;
    var PRIVATE                 = (cast STRING) + 21;
    var HTTP_CONNECTCODE        = (cast LONG)   + 22;
    var HTTPAUTH_AVAIL          = (cast LONG)   + 23;
    var PROXYAUTH_AVAIL         = (cast LONG)   + 24;
    var OS_ERRNO                = (cast LONG)   + 25;
    var NUM_CONNECTS            = (cast LONG)   + 26;
    var SSL_ENGINES             = (cast SLIST)  + 27;
    var COOKIELIST              = (cast SLIST)  + 28;
    var LASTSOCKET              = (cast LONG)   + 29;
    var FTP_ENTRY_PATH          = (cast STRING) + 30;
    var REDIRECT_URL            = (cast STRING) + 31;
    var PRIMARY_IP              = (cast STRING) + 32;
    var APPCONNECT_TIME         = (cast DOUBLE) + 33;
    var CERTINFO                = (cast SLIST)  + 34;
    var CONDITION_UNMET         = (cast LONG)   + 35;
    var RTSP_SESSION_ID         = (cast STRING) + 36;
    var RTSP_CLIENT_CSEQ        = (cast LONG)   + 37;
    var RTSP_SERVER_CSEQ        = (cast LONG)   + 38;
    var RTSP_CSEQ_RECV          = (cast LONG)   + 39;
    var PRIMARY_PORT            = (cast LONG)   + 40;
    var LOCAL_IP                = (cast STRING) + 41;
    var LOCAL_PORT              = (cast LONG)   + 42;
    var TLS_SESSION             = (cast SLIST)  + 43;

    /**
     *
     */
    public static function returnType(info:CurlInfo):Int
    {
        return if (info == EFFECTIVE_URL || info == REDIRECT_URL || info == CONTENT_TYPE
          || info == PRIVATE || info == PRIMARY_IP || info == LOCAL_IP || info == FTP_ENTRY_PATH || info == RTSP_SESSION_ID) {
            0; // char*
        } else if (info == TOTAL_TIME || info == NAMELOOKUP_TIME || info == CONNECT_TIME || info == APPCONNECT_TIME
          || info == PRETRANSFER_TIME || info == STARTTRANSFER_TIME || info == REDIRECT_TIME || info == SIZE_UPLOAD
          || info == SIZE_DOWNLOAD || info == SPEED_DOWNLOAD || info == SPEED_UPLOAD || info == CONTENT_LENGTH_DOWNLOAD
          || info == CONTENT_LENGTH_UPLOAD) {
            1; // double*
        } else if (info == SSL_ENGINES || info == COOKIELIST) {
            5; // struct curl_slist*
        } else if (info == CERTINFO) {
            6; // struct curl_certinfo*
        } else if (info == TLS_SESSION) {
            7; // struct curl_tlsinfo*
        } else {
            2; // long*
        }
    }
}


/**
 * libcurl info groups offsets.
 */
@:enum
private abstract CurlInfoOffset(Int) to Int
{
    var STRING   = 0x100000;
    var LONG     = 0x200000;
    var DOUBLE   = 0x300000;
    var SLIST    = 0x400000;
    var MASK     = 0x0fffff;
    var TYPEMASK = 0xf00000;
}
