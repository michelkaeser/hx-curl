package hxcurl;

import hxcurl.easy.CurlInfo;

/**
 *
 */
class CurlTools
{
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
