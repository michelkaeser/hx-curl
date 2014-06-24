package hxcurl;

/**
 *
 */
@:enum
abstract CurlStruct(Int) to Int
{
    var CERTINFO = 0;
    var SLIST    = 1;
    var TLSINFO  = 2;
}
