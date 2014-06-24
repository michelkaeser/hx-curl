package hxcurl;

/**
 * Abstract enums wrapping the various libcurl pause codes.
 *
 * @link http://curl.haxx.se/libcurl/c/curl_easy_pause.html
 * @link https://github.com/bagder/curl/blob/ade380a7aa1241fd7a2e16ee0c44fe268b42ff9a/include/curl/curl.h#L2288-L2297
 */
@:enum
abstract CurlPause(Int) from Int to Int
{
    // Information
    var CONT      = 0; // CurlPauseOffset.RECV_CONT | CurlPauseOffset.SEND_CONT;
    var RECV      = 1; // 1 << 0;
    var SEND      = 4; // 1 << 2;
    var ALL       = 5; // CurlPause.RECV | CurlPause.SEND;
}


/**
 * libcurl pause offsets.
 */
@:enum
private abstract CurlPauseOffset(Int) to Int
{
    var RECV_CONT = 0;
    var SEND_CONT = 0;
}
