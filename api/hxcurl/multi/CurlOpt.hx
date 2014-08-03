package hxcurl.multi;

import hxcurl.CurlOptOffset;

/**
 * Abstract enums wrapping the various libcurl multi option codes.
 *
 * @link http://curl.haxx.se/libcurl/c/curl_multi_setopt.html
 * @link https://github.com/bagder/curl/blob/master/include/curl/multi.h#L324-L369
 */
@:enum
abstract CurlOpt(Int) to Int
{
    var SOCKETFUNCTION              = (cast CurlOptOffset.FUNCTIONPOINT) + 1;
    var SOCKETDATA                  = (cast CurlOptOffset.OBJECTPOINT)   + 2;
    var PIPELINING                  = (cast CurlOptOffset.LONG)          + 3;
    var TIMERFUNCTION               = (cast CurlOptOffset.FUNCTIONPOINT) + 4;
    var TIMERDATA                   = (cast CurlOptOffset.OBJECTPOINT)   + 5;
    var MAXCONNECTS                 = (cast CurlOptOffset.LONG)          + 6;
    var MAX_HOST_CONNECTIONS        = (cast CurlOptOffset.LONG)          + 7;
    var MAX_PIPELINE_LENGTH         = (cast CurlOptOffset.LONG)          + 8;
    var CONTENT_LENGTH_PENALTY_SIZE = (cast CurlOptOffset.OFF_T)         + 9;
    var CHUNK_LENGTH_PENALTY_SIZE   = (cast CurlOptOffset.OFF_T)         + 10;
    var PIPELINING_SITE_BL          = (cast CurlOptOffset.OBJECTPOINT)   + 11;
    var PIPELINING_SERVER_BL        = (cast CurlOptOffset.OBJECTPOINT)   + 12;
    var MAX_TOTAL_CONNECTIONS       = (cast CurlOptOffset.LONG)          + 13;
}
