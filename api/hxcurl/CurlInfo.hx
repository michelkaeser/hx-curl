package hxcurl;

/**
 *
 */
@:enum
abstract CurlInfo(Int) from Int to Int
{
    // Information
    var EFFECTIVE_URL
    var RESPONSE_CODE
    var HTTP_CONNECTCODE
    var FILETIME
    var TOTAL_TIME
    var NAMELOOKUP_TIME
    var CONNECT_TIME
    var APPCONNECT_TIME
    var PRETRANSFER_TIME
    var STARTTRANSFER_TIME
    var REDIRECT_TIME
    var REDIRECT_COUNT
    var REDIRECT_URL
    var SIZE_UPLOAD
    var SIZE_DOWNLOAD
    var SPEED_DOWNLOAD
    var SPEED_UPLOAD
    var HEADER_SIZE
    var REQUEST_SIZE
    var SSL_VERIFYRESULT
    var SSL_ENGINES
    var CONTENT_LENGTH_DOWNLOAD
    var CONTENT_LENGTH_UPLOAD
    var CONTENT_TYPE
    var PRIVATE
    var HTTPAUTH_AVAIL
    var PROXYAUTH_AVAIL
    var OS_ERRNO
    var NUM_CONNECTS
    var PRIMARY_IP
    var PRIMARY_PORT
    var LOCAL_IP
    var LOCAL_PORT
    var COOKIELIST
    var LASTSOCKET
    var FTP_ENTRY_PATH
    var CERTINFO
    var TLS_SESSION
    var CONDITION_UNMET
    var RTSP_SESSION_ID
    var RTSP_CLIENT_CSEQ
    var RTSP_SERVER_CSEQ
    var RTSP_CSEQ_RECV

    // Times
    var NAMELOOKUP
    var CONNECT
    var APPCONNECT
    var PRETRANSFER
    var STARTTRANSFER
    var TOTAL
    var REDIRECT
}
