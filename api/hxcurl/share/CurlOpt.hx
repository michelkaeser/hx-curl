package hxcurl;

/**
 * Abstract enums wrapping the various libcurl share option codes.
 *
 * @link http://curl.haxx.se/libcurl/c/curl_share_setopt.html
 * @link https://github.com/bagder/curl/blob/master/include/curl/curl.h#L2167-L2176
 */
@:enum
abstract CurlOpt(Int) to Int
{
    var NONE       = 0;
    var SHARE      = 1;
    var UNSHARE    = 2;
    var LOCKFUNC   = 3;
    var UNLOCKFUNC = 4;
    var USERDATA   = 5;
}
