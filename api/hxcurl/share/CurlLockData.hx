package hxcurl.share;

/**
 * Abstract enums wrapping the various libcurl share lock data value codes.
 *
 * @link http://curl.haxx.se/libcurl/c/curl_share_setopt.html
 * @link https://github.com/bagder/curl/blob/master/include/curl/curl.h#L2125-L2137
 */
@:enum
abstract CurlLockData(Int) to Int
{
    var NONE        = 0;
    var SHARE       = 1;
    var COOKIE      = 2;
    var DNS         = 3;
    var SSL_SESSION = 4;
    var CONNECT     = 5;
}

// https://github.com/bagder/curl/blob/master/include/curl/curl.h#L2140-L2145
