package hxcurl;

/**
 * Abstract enum for the libcurl option groups offsets.
 */
@:enum
abstract CurlOptOffset(Int) to Int
{
    var LONG          = 0;
    var OBJECTPOINT   = 10000;
    var FUNCTIONPOINT = 20000;
    var OFF_T         = 30000;
}
