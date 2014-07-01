package hxcurl.share;

/**
 * Abstract enums wrapping the various libcurl share lock data value codes.
 *
 * @link http://curl.haxx.se/libcurl/c/curl_share_setopt.html
 * @link https://github.com/bagder/curl/blob/master/include/curl/curl.h#L2140-L2145
 */
@:enum
abstract CurlLockAccess(Int) to Int
{
    var NONE        = 0;
    var SHARE       = 1;
    var SINGLE      = 2;
}
