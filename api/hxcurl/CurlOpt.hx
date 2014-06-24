package hxcurl;

/**
 * Abstract enums wrapping the various libcurl option codes.
 *
 * @link http://curl.haxx.se/libcurl/c/curl_easy_setopt.html
 * @link https://github.com/bagder/curl/blob/ade380a7aa1241fd7a2e16ee0c44fe268b42ff9a/include/curl/curl.h
 */
@:enum
abstract CurlOpt(Int) to Int
{
    var WRITEDATA                  = (cast CurlOptOffset.OBJECTPOINT)   + 1;
    var URL                        = (cast CurlOptOffset.OBJECTPOINT)   + 2;
    var PORT                       = (cast CurlOptOffset.LONG)          + 3;
    var PROXY                      = (cast CurlOptOffset.OBJECTPOINT)   + 4;
    var USERPWD                    = (cast CurlOptOffset.OBJECTPOINT)   + 5;
    var PROXYUSERPWD               = (cast CurlOptOffset.OBJECTPOINT)   + 6;
    var RANGE                      = (cast CurlOptOffset.OBJECTPOINT)   + 7;
    var READDATA                   = (cast CurlOptOffset.OBJECTPOINT)   + 9;
    var ERRORBUFFER                = (cast CurlOptOffset.OBJECTPOINT)   + 10;
    var WRITEFUNCTION              = (cast CurlOptOffset.FUNCTIONPOINT) + 11;
    var READFUNCTION               = (cast CurlOptOffset.FUNCTIONPOINT) + 12;
    var TIMEOUT                    = (cast CurlOptOffset.LONG)          + 13;
    var INFILESIZE                 = (cast CurlOptOffset.LONG)          + 14;
    var POSTFIELDS                 = (cast CurlOptOffset.OBJECTPOINT)   + 15;
    var REFERER                    = (cast CurlOptOffset.OBJECTPOINT)   + 16;
    var FTPPORT                    = (cast CurlOptOffset.OBJECTPOINT)   + 17;
    var USERAGENT                  = (cast CurlOptOffset.OBJECTPOINT)   + 18;
    var LOW_SPEED_LIMIT            = (cast CurlOptOffset.LONG)          + 19;
    var LOW_SPEED_TIME             = (cast CurlOptOffset.LONG)          + 20;
    var RESUME_FROM                = (cast CurlOptOffset.LONG)          + 21;
    var COOKIE                     = (cast CurlOptOffset.OBJECTPOINT)   + 22;
    var HTTPHEADER                 = (cast CurlOptOffset.OBJECTPOINT)   + 23;
    var HTTPPOST                   = (cast CurlOptOffset.OBJECTPOINT)   + 24;
    var SSLCERT                    = (cast CurlOptOffset.OBJECTPOINT)   + 25;
    var KEYPASSWD                  = (cast CurlOptOffset.OBJECTPOINT)   + 26;
    var CRLF                       = (cast CurlOptOffset.LONG)          + 27;
    var QUOTE                      = (cast CurlOptOffset.OBJECTPOINT)   + 28;
    var HEADERDATA                 = (cast CurlOptOffset.OBJECTPOINT)   + 29;
    var COOKIEFILE                 = (cast CurlOptOffset.OBJECTPOINT)   + 31;
    var SSLVERSION                 = (cast CurlOptOffset.LONG)          + 32;
    var TIMECONDITION              = (cast CurlOptOffset.LONG)          + 33;
    var TIMEVALUE                  = (cast CurlOptOffset.LONG)          + 34;
    var CUSTOMREQUEST              = (cast CurlOptOffset.OBJECTPOINT)   + 36;
    var STDERR                     = (cast CurlOptOffset.OBJECTPOINT)   + 37;
    var POSTQUOTE                  = (cast CurlOptOffset.OBJECTPOINT)   + 39;
    var VERBOSE                    = (cast CurlOptOffset.LONG)          + 41;
    var HEADER                     = (cast CurlOptOffset.LONG)          + 42;
    var NOPROGRESS                 = (cast CurlOptOffset.LONG)          + 43;
    var NOBODY                     = (cast CurlOptOffset.LONG)          + 44;
    var FAILONERROR                = (cast CurlOptOffset.LONG)          + 45;
    var UPLOAD                     = (cast CurlOptOffset.LONG)          + 46;
    var POST                       = (cast CurlOptOffset.LONG)          + 47;
    var DIRLISTONLY                = (cast CurlOptOffset.LONG)          + 48;
    var APPEND                     = (cast CurlOptOffset.LONG)          + 50;
    var NETRC                      = (cast CurlOptOffset.LONG)          + 51;
    var FOLLOWLOCATION             = (cast CurlOptOffset.LONG)          + 52;
    var TRANSFERTEXT               = (cast CurlOptOffset.LONG)          + 53;
    var PUT                        = (cast CurlOptOffset.LONG)          + 54;
    var PROGRESSFUNCTION           = (cast CurlOptOffset.FUNCTIONPOINT) + 56;
    var PROGRESSDATA               = (cast CurlOptOffset.OBJECTPOINT)   + 57;
    var XFERINFODATA               = CurlOpt.PROGRESSDATA;
    var AUTOREFERER                = (cast CurlOptOffset.LONG)          + 58;
    var PROXYPORT                  = (cast CurlOptOffset.LONG)          + 59;
    var POSTFIELDSIZE              = (cast CurlOptOffset.LONG)          + 60;
    var HTTPPROXYTUNNEL            = (cast CurlOptOffset.LONG)          + 61;
    var INTERFACE                  = (cast CurlOptOffset.OBJECTPOINT)   + 62;
    var KRBLEVEL                   = (cast CurlOptOffset.OBJECTPOINT)   + 63;
    var SSL_VERIFYPEER             = (cast CurlOptOffset.LONG)          + 64;
    var CAINFO                     = (cast CurlOptOffset.OBJECTPOINT)   + 65;
    var MAXREDIRS                  = (cast CurlOptOffset.LONG)          + 68;
    var FILETIME                   = (cast CurlOptOffset.LONG)          + 69;
    var TELNETOPTIONS              = (cast CurlOptOffset.OBJECTPOINT)   + 70;
    var MAXCONNECTS                = (cast CurlOptOffset.LONG)          + 71;
    var FRESH_CONNECT              = (cast CurlOptOffset.LONG)          + 74;
    var FORBID_REUSE               = (cast CurlOptOffset.LONG)          + 75;
    var RANDOM_FILE                = (cast CurlOptOffset.OBJECTPOINT)   + 76;
    var EGDSOCKET                  = (cast CurlOptOffset.OBJECTPOINT)   + 77;
    var CONNECTTIMEOUT             = (cast CurlOptOffset.LONG)          + 78;
    var HEADERFUNCTION             = (cast CurlOptOffset.FUNCTIONPOINT) + 79;
    var HTTPGET                    = (cast CurlOptOffset.LONG)          + 80;
    var SSL_VERIFYHOST             = (cast CurlOptOffset.LONG)          + 81;
    var COOKIEJAR                  = (cast CurlOptOffset.OBJECTPOINT)   + 82;
    var SSL_CIPHER_LIST            = (cast CurlOptOffset.OBJECTPOINT)   + 83;
    var HTTP_VERSION               = (cast CurlOptOffset.LONG)          + 84;
    var FTP_USE_EPSV               = (cast CurlOptOffset.LONG)          + 85;
    var SSLCERTTYPE                = (cast CurlOptOffset.OBJECTPOINT)   + 86;
    var SSLKEY                     = (cast CurlOptOffset.OBJECTPOINT)   + 87;
    var SSLKEYTYPE                 = (cast CurlOptOffset.OBJECTPOINT)   + 88;
    var SSLENGINE                  = (cast CurlOptOffset.OBJECTPOINT)   + 89;
    var SSLENGINE_DEFAULT          = (cast CurlOptOffset.LONG)          + 90;
    var DNS_USE_GLOBAL_CACHE       = (cast CurlOptOffset.LONG)          + 91;
    var DNS_CACHE_TIMEOUT          = (cast CurlOptOffset.LONG)          + 92;
    var PREQUOTE                   = (cast CurlOptOffset.OBJECTPOINT)   + 93;
    var DEBUGFUNCTION              = (cast CurlOptOffset.FUNCTIONPOINT) + 94;
    var DEBUGDATA                  = (cast CurlOptOffset.OBJECTPOINT)   + 95;
    var COOKIESESSION              = (cast CurlOptOffset.LONG)          + 96;
    var CAPATH                     = (cast CurlOptOffset.OBJECTPOINT)   + 97;
    var BUFFERSIZE                 = (cast CurlOptOffset.LONG)          + 98;
    var NOSIGNAL                   = (cast CurlOptOffset.LONG)          + 99;
    var SHARE                      = (cast CurlOptOffset.OBJECTPOINT)   + 100;
    var PROXYTYPE                  = (cast CurlOptOffset.LONG)          + 101;
    var ACCEPT_ENCODING            = (cast CurlOptOffset.OBJECTPOINT)   + 102;
    var PRIVATE                    = (cast CurlOptOffset.OBJECTPOINT)   + 103;
    var HTTP200ALIASES             = (cast CurlOptOffset.OBJECTPOINT)   + 104;
    var UNRESTRICTED_AUTH          = (cast CurlOptOffset.LONG)          + 105;
    var FTP_USE_EPRT               = (cast CurlOptOffset.LONG)          + 106;
    var HTTPAUTH                   = (cast CurlOptOffset.LONG)          + 107;
    var SSL_CTX_FUNCTION           = (cast CurlOptOffset.FUNCTIONPOINT) + 108;
    var SSL_CTX_DATA               = (cast CurlOptOffset.OBJECTPOINT)   + 109;
    var FTP_CREATE_MISSING_DIRS    = (cast CurlOptOffset.LONG)          + 110;
    var PROXYAUTH                  = (cast CurlOptOffset.LONG)          + 111;
    var FTP_RESPONSE_TIMEOUT       = (cast CurlOptOffset.LONG)          + 112;
    var IPRESOLVE                  = (cast CurlOptOffset.LONG)          + 113;
    var MAXFILESIZE                = (cast CurlOptOffset.LONG)          + 114;
    var INFILESIZE_LARGE           = (cast CurlOptOffset.OFF_T)         + 115;
    var RESUME_FROM_LARGE          = (cast CurlOptOffset.OFF_T)         + 116;
    var MAXFILESIZE_LARGE          = (cast CurlOptOffset.OFF_T)         + 117;
    var NETRC_FILE                 = (cast CurlOptOffset.OBJECTPOINT)   + 118;
    var USE_SSL                    = (cast CurlOptOffset.LONG)          + 119;
    var POSTFIELDSIZE_LARGE        = (cast CurlOptOffset.OFF_T)         + 120;
    var TCP_NODELAY                = (cast CurlOptOffset.LONG)          + 121;
    var FTPSSLAUTH                 = (cast CurlOptOffset.LONG)          + 129;
    var IOCTLFUNCTION              = (cast CurlOptOffset.FUNCTIONPOINT) + 130;
    var IOCTLDATA                  = (cast CurlOptOffset.OBJECTPOINT)   + 131;
    var FTP_ACCOUNT                = (cast CurlOptOffset.OBJECTPOINT)   + 134;
    var COOKIELIST                 = (cast CurlOptOffset.OBJECTPOINT)   + 135;
    var IGNORE_CONTENT_LENGTH      = (cast CurlOptOffset.LONG)          + 136;
    var FTP_SKIP_PASV_IP           = (cast CurlOptOffset.LONG)          + 137;
    var FTP_FILEMETHOD             = (cast CurlOptOffset.LONG)          + 138;
    var LOCALPORT                  = (cast CurlOptOffset.LONG)          + 139;
    var LOCALPORTRANGE             = (cast CurlOptOffset.LONG)          + 140;
    var CONNECT_ONLY               = (cast CurlOptOffset.LONG)          + 141;
    var CONV_FROM_NETWORK_FUNCTION = (cast CurlOptOffset.FUNCTIONPOINT) + 142;
    var CONV_TO_NETWORK_FUNCTION   = (cast CurlOptOffset.FUNCTIONPOINT) + 143;
    var CONV_FROM_UTF8_FUNCTION    = (cast CurlOptOffset.FUNCTIONPOINT) + 144;
    var MAX_SEND_SPEED_LARGE       = (cast CurlOptOffset.OFF_T)         + 145;
    var MAX_RECV_SPEED_LARGE       = (cast CurlOptOffset.OFF_T)         + 146;
    var FTP_ALTERNATIVE_TO_USER    = (cast CurlOptOffset.OBJECTPOINT)   + 147;
    var SOCKOPTFUNCTION            = (cast CurlOptOffset.FUNCTIONPOINT) + 148;
    var SOCKOPTDATA                = (cast CurlOptOffset.OBJECTPOINT)   + 149;
    var SSL_SESSIONID_CACHE        = (cast CurlOptOffset.LONG)          + 150;
    var SSH_AUTH_TYPES             = (cast CurlOptOffset.LONG)          + 151;
    var SSH_PUBLIC_KEYFILE         = (cast CurlOptOffset.OBJECTPOINT)   + 152;
    var SSH_PRIVATE_KEYFILE        = (cast CurlOptOffset.OBJECTPOINT)   + 153;
    var FTP_SSL_CCC                = (cast CurlOptOffset.LONG)          + 154;
    var TIMEOUT_MS                 = (cast CurlOptOffset.LONG)          + 155;
    var CONNECTTIMEOUT_MS          = (cast CurlOptOffset.LONG)          + 156;
    var HTTP_TRANSFER_DECODING     = (cast CurlOptOffset.LONG)          + 157;
    var HTTP_CONTENT_DECODING      = (cast CurlOptOffset.LONG)          + 158;
    var NEW_FILE_PERMS             = (cast CurlOptOffset.LONG)          + 159;
    var NEW_DIRECTORY_PERMS        = (cast CurlOptOffset.LONG)          + 160;
    var POSTREDIR                  = (cast CurlOptOffset.LONG)          + 161;
    var SSH_HOST_PUBLIC_KEY_MD5    = (cast CurlOptOffset.OBJECTPOINT)   + 162;
    var OPENSOCKETFUNCTION         = (cast CurlOptOffset.FUNCTIONPOINT) + 163;
    var OPENSOCKETDATA             = (cast CurlOptOffset.OBJECTPOINT)   + 164;
    var COPYPOSTFIELDS             = (cast CurlOptOffset.OBJECTPOINT)   + 165;
    var PROXY_TRANSFER_MODE        = (cast CurlOptOffset.LONG)          + 166;
    var SEEKFUNCTION               = (cast CurlOptOffset.FUNCTIONPOINT) + 167;
    var SEEKDATA                   = (cast CurlOptOffset.OBJECTPOINT)   + 168;
    var CRLFILE                    = (cast CurlOptOffset.OBJECTPOINT)   + 169;
    var ISSUERCERT                 = (cast CurlOptOffset.OBJECTPOINT)   + 170;
    var ADDRESS_SCOPE              = (cast CurlOptOffset.LONG)          + 171;
    var CERTINFO                   = (cast CurlOptOffset.LONG)          + 172;
    var USERNAME                   = (cast CurlOptOffset.OBJECTPOINT)   + 173;
    var PASSWORD                   = (cast CurlOptOffset.OBJECTPOINT)   + 174;
    var PROXYUSERNAME              = (cast CurlOptOffset.OBJECTPOINT)   + 175;
    var PROXYPASSWORD              = (cast CurlOptOffset.OBJECTPOINT)   + 176;
    var NOPROXY                    = (cast CurlOptOffset.OBJECTPOINT)   + 177;
    var TFTP_BLKSIZE               = (cast CurlOptOffset.LONG)          + 178;
    var SOCKS5_GSSAPI_SERVICE      = (cast CurlOptOffset.OBJECTPOINT)   + 179;
    var SOCKS5_GSSAPI_NEC          = (cast CurlOptOffset.LONG)          + 180;
    var PROTOCOLS                  = (cast CurlOptOffset.LONG)          + 181;
    var REDIR_PROTOCOLS            = (cast CurlOptOffset.LONG)          + 182;
    var SSH_KNOWNHOSTS             = (cast CurlOptOffset.OBJECTPOINT)   + 183;
    var SSH_KEYFUNCTION            = (cast CurlOptOffset.FUNCTIONPOINT) + 184;
    var SSH_KEYDATA                = (cast CurlOptOffset.OBJECTPOINT)   + 185;
    var MAIL_FROM                  = (cast CurlOptOffset.OBJECTPOINT)   + 186;
    var MAIL_RCPT                  = (cast CurlOptOffset.OBJECTPOINT)   + 187;
    var FTP_USE_PRET               = (cast CurlOptOffset.LONG)          + 188;
    var RTSP_REQUEST               = (cast CurlOptOffset.LONG)          + 189;
    var RTSP_SESSION_ID            = (cast CurlOptOffset.OBJECTPOINT)   + 190;
    var RTSP_STREAM_URI            = (cast CurlOptOffset.OBJECTPOINT)   + 191;
    var RTSP_TRANSPORT             = (cast CurlOptOffset.OBJECTPOINT)   + 192;
    var RTSP_CLIENT_CSEQ           = (cast CurlOptOffset.LONG)          + 193;
    var RTSP_SERVER_CSEQ           = (cast CurlOptOffset.LONG)          + 194;
    var INTERLEAVEDATA             = (cast CurlOptOffset.OBJECTPOINT)   + 195;
    var INTERLEAVEFUNCTION         = (cast CurlOptOffset.FUNCTIONPOINT) + 196;
    var WILDCARDMATCH              = (cast CurlOptOffset.LONG)          + 197;
    var CHUNK_BGN_FUNCTION         = (cast CurlOptOffset.FUNCTIONPOINT) + 198;
    var CHUNK_END_FUNCTION         = (cast CurlOptOffset.FUNCTIONPOINT) + 199;
    var FNMATCH_FUNCTION           = (cast CurlOptOffset.FUNCTIONPOINT) + 200;
    var CHUNK_DATA                 = (cast CurlOptOffset.OBJECTPOINT)   + 201;
    var FNMATCH_DATA               = (cast CurlOptOffset.OBJECTPOINT)   + 202;
    var RESOLVE                    = (cast CurlOptOffset.OBJECTPOINT)   + 203;
    var TLSAUTH_USERNAME           = (cast CurlOptOffset.OBJECTPOINT)   + 204;
    var TLSAUTH_PASSWORD           = (cast CurlOptOffset.OBJECTPOINT)   + 205;
    var TLSAUTH_TYPE               = (cast CurlOptOffset.OBJECTPOINT)   + 206;
    var TRANSFER_ENCODING          = (cast CurlOptOffset.LONG)          + 207;
    var CLOSESOCKETFUNCTION        = (cast CurlOptOffset.FUNCTIONPOINT) + 208;
    var CLOSESOCKETDATA            = (cast CurlOptOffset.OBJECTPOINT)   + 209;
    var GSSAPI_DELEGATION          = (cast CurlOptOffset.LONG)          + 210;
    var DNS_SERVERS                = (cast CurlOptOffset.OBJECTPOINT)   + 211;
    var ACCEPTTIMEOUT_MS           = (cast CurlOptOffset.LONG)          + 212;
    var TCP_KEEPALIVE              = (cast CurlOptOffset.LONG)          + 213;
    var TCP_KEEPIDLE               = (cast CurlOptOffset.LONG)          + 214;
    var TCP_KEEPINTVL              = (cast CurlOptOffset.LONG)          + 215;
    var SSL_OPTIONS                = (cast CurlOptOffset.LONG)          + 216;
    var MAIL_AUTH                  = (cast CurlOptOffset.OBJECTPOINT)   + 217;
    var SASL_IR                    = (cast CurlOptOffset.LONG)          + 218;
    var XFERINFOFUNCTION           = (cast CurlOptOffset.FUNCTIONPOINT) + 219;
    var XOAUTH2_BEARER             = (cast CurlOptOffset.OBJECTPOINT)   + 220;
    var DNS_INTERFACE              = (cast CurlOptOffset.OBJECTPOINT)   + 221;
    var DNS_LOCAL_IP4              = (cast CurlOptOffset.OBJECTPOINT)   + 222;
    var DNS_LOCAL_IP6              = (cast CurlOptOffset.OBJECTPOINT)   + 223;
    var LOGIN_OPTIONS              = (cast CurlOptOffset.OBJECTPOINT)   + 224;
    var SSL_ENABLE_NPN             = (cast CurlOptOffset.LONG)          + 225;
    var SSL_ENABLE_ALPN            = (cast CurlOptOffset.LONG)          + 226;
    var EXPECT_100_TIMEOUT_MS      = (cast CurlOptOffset.LONG)          + 227;
    var PROXYHEADER                = (cast CurlOptOffset.OBJECTPOINT)   + 228;
    var HEADEROPT                  = (cast CurlOptOffset.LONG)          + 229;
}


/**
 * libcurl option groups offsets.
 */
@:enum
private abstract CurlOptOffset(Int) to Int
{
    var LONG          = 0;
    var OBJECTPOINT   = 10000;
    var FUNCTIONPOINT = 20000;
    var OFF_T         = 30000;
}