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
    var SOCKETFUNCTION              = (cast FUNCTIONPOINT) + 1;
    var SOCKETDATA                  = (cast OBJECTPOINT)   + 2;
    var PIPELINING                  = (cast LONG)          + 3;
    var TIMERFUNCTION               = (cast FUNCTIONPOINT) + 4;
    var TIMERDATA                   = (cast OBJECTPOINT)   + 5;
    var MAXCONNECTS                 = (cast LONG)          + 6;
    var MAX_HOST_CONNECTIONS        = (cast LONG)          + 7;
    var MAX_PIPELINE_LENGTH         = (cast LONG)          + 8;
    var CONTENT_LENGTH_PENALTY_SIZE = (cast OFF_T)         + 9;
    var CHUNK_LENGTH_PENALTY_SIZE   = (cast OFF_T)         + 10;
    var PIPELINING_SITE_BL          = (cast OBJECTPOINT)   + 11;
    var PIPELINING_SERVER_BL        = (cast OBJECTPOINT)   + 12;
    var MAX_TOTAL_CONNECTIONS       = (cast LONG)          + 13;
}
