package hxcurl;

import haxe.PosInfos;
import hxstd.Exception;

/**
 * Exceptions to be thrown when Exceptions from the C FFI need to be wrapped
 * or for any other kind of errors related to libcurl.
 */
class CurlException extends Exception
{
    /**
     * @{inherit}
     */
    public function new(msg:String = "Uncaught CURL exception", ?info:PosInfos):Void
    {
        super(msg, info);
    }
}
