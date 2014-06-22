package hxcurl;

/**
 *
 */
@:enum
abstract CurlOpt(Int) from Int to Int
{
    // Behavior options
    var VERBOSE
    var HEADER
    var NOPROGRESS
    var NOSIGNAL
    var WILDCARDMATCH

    // Callback options
    var WRITEFUNCTION
    var WRITEDATA
    var READFUNCTION
    var READDATA
    var IOCTLFUNCTION
    var IOCTLDATA
    var SEEKFUNCTION
    var SEEKDATA
    var SOCKOPTFUNCTION
    var SOCKOPTDATA
    var OPENSOCKETFUNCTION
    var OPENSOCKETDATA
    var CLOSESOCKETFUNCTION
    var CLOSESOCKETDATA
    var PROGRESSFUNCTION
    var PROGRESSDATA
    var XFERINFOFUNCTION
    var XFERINFODATA
    var HEADERFUNCTION
    var HEADERDATA
    var DEBUGFUNCTION
    var DEBUGDATA
    var SSL_CTX_FUNCTION
    var SSL_CTX_DATA
    var CONV_TO_NETWORK_FUNCTION
    var CONV_FROM_NETWORK_FUNCTION
    var CONV_FROM_UTF8_FUNCTION
    var INTERLEAVEFUNCTION
    var INTERLEAVEDATA
    var CHUNK_BGN_FUNCTION
    var CHUNK_END_FUNCTION
    var CHUNK_DATA
    var FNMATCH_FUNCTION
    var FNMATCH_DATA

    // Error options
    var ERRORBUFFER
    var STDERR
    var FAILONERROR

    // Network options
    var URL
    var PROTOCOLS
    var REDIR_PROTOCOLS
    var PROXY
    var PROXYPORT
    var PROXYTYPE
    var NOPROXY
    var HTTPPROXYTUNNEL
    var SOCKS5_GSSAPI_SERVICE
    var SOCKS5_GSSAPI_NEC
    var INTERFACE
    var LOCALPORT
    var LOCALPORTRANGE
    var DNS_CACHE_TIMEOUT
    var DNS_USE_GLOBAL_CACHE
    var BUFFERSIZE
    var PORT
    var TCP_NODELAY
    var ADDRESS_SCOPE
    var TCP_KEEPALIVE
    var TCP_KEEPIDLE
    var TCP_KEEPINTVL

    // Authentication options
    var NETRC
    var NETRC_FILE
    var USERPWD
    var PROXYUSERPWD
    var USERNAME
    var PASSWORD
    var LOGIN_OPTIONS
    var PROXYUSERNAME
    var PROXYPASSWORD
    var HTTPAUTH
    var TLSAUTH_USERNAME
    var TLSAUTH_PASSWORD
    var PROXYAUTH
    var SASL_IR
    var XOAUTH2_BEARER

    // HTTP options
    var AUTOREFERER
    var ACCEPT_ENCODING
    var TRANSFER_ENCODING
    var FOLLOWLOCATION
    var UNRESTRICTED_AUTH
    var MAXREDIRS
    var POSTREDIR
    var PUT
    var POST
    var POSTFIELDS
    var POSTFIELDSIZE
    var POSTFIELDSIZE_LARGE
    var COPYPOSTFIELDS
    var HTTPPOST
    var REFERER
    var USERAGENT
    var HTTPHEADER
    var HEADEROPT
    var PROXYHEADER
    var HTTP200ALIASES
    var COOKIE
    var COOKIEFILE
    var COOKIEJAR
    var COOKIESESSION
    var COOKIELIST
    var HTTPGET
    var HTTP_VERSION
    var IGNORE_CONTENT_LENGTH
    var HTTP_CONTENT_DECODING
    var HTTP_TRANSFER_DECODING
    var EXPECT_100_TIMEOUT_MS

    // SMTP options
    var MAIL_FROM
    var MAIL_RCPT
    var MAIL_AUTH

    // TFTP options
    var TFTP_BLKSIZE

    // FTP options
    var FTPPORT
    var QUOTE
    var POSTQUOTE
    var PREQUOTE
    var DIRLISTONLY
    var APPEND
    var FTP_USE_EPRT
    var FTP_USE_EPSV
    var FTP_USE_PRET
    var FTP_CREATE_MISSING_DIRS
    var FTP_RESPONSE_TIMEOUT
    var FTP_ALTERNATIVE_TO_USER
    var FTP_SKIP_PASV_IP
    var FTPSSLAUTH
    var FTP_SSL_CCC
    var FTP_ACCOUNT
    var FTP_FILEMETHOD

    // RTSP options
    var RTSP_REQUEST
    var RTSP_SESSION_ID
    var RTSP_STREAM_URI
    var RTSP_TRANSPORT
    var RTSP_CLIENT_CSEQ
    var RTSP_SERVER_CSEQ

    // Protocol options
    var TRANSFERTEXT
    var PROXY_TRANSFER_MODE
    var CRLF
    var RANGE
    var RESUME_FROM
    var RESUME_FROM_LARGE
    var CUSTOMREQUEST
    var FILETIME
    var NOBODY
    var INFILESIZE
    var INFILESIZE_LARGE
    var UPLOAD
    var MAXFILESIZE
    var MAXFILESIZE_LARGE
    var TIMECONDITION
    var TIMEVALUE

    // Connect options
    var TIMEOUT
    var TIMEOUT_MS
    var LOW_SPEED_LIMIT
    var LOW_SPEED_TIME
    var MAX_SEND_SPEED_LARGE
    var MAX_RECV_SPEED_LARGE
    var MAXCONNECTS
    var FRESH_CONNECT
    var FORBID_REUSE
    var CONNECTTIMEOUT
    var CONNECTTIMEOUT_MS
    var IPRESOLVE
    var CONNECT_ONLY
    var USE_SSL
    var RESOLVE
    var DNS_INTERFACE
    var DNS_LOCAL_IP4
    var DNS_LOCAL_IP6
    var ACCEPTTIMEOUT_MS

    // SSL and security options
    var SSLCERT
    var SSLCERTTYPE
    var SSLKEY
    var SSLKEYTYPE
    var KEYPASSWD
    var SSL_ENABLE_ALPN
    var SSL_ENABLE_NPN
    var SSLENGINE
    var SSLENGINE_DEFAULT
    var SSLVERSION
    var SSL_VERIFYPEER
    var CAINFO
    var ISSUERCERT
    var CAPATH
    var CRLFILE
    var SSL_VERIFYHOST
    var CERTINFO
    var RANDOM_FILE
    var EGDSOCKET
    var SSL_CIPHER_LIST
    var SSL_SESSIONID_CACHE
    var SSL_OPTIONS
    var KRBLEVEL
    var GSSAPI_DELEGATION

    // SSH options
    var SSH_AUTH_TYPES
    var SSH_HOST_PUBLIC_KEY_MD5
    var SSH_PUBLIC_KEYFILE
    var SSH_PRIVATE_KEYFILE
    var SSH_KNOWNHOSTS
    var SSH_KEYFUNCTION
    var SSH_KEYDATA

    // Other options
    var PRIVATE
    var SHARE
    var NEW_FILE_PERMS
    var NEW_DIRECTORY_PERMS

    // Telnet options
    var TELNETOPTIONS
}
