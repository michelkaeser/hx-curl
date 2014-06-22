package hxcurl;

import haxe.PosInfos;
import hxcurl.CurlException;

/**
 * Exceptions to be thrown when Exceptions from the C FFI need to be wrapped
 * or for any other kind of errors related to libcurl.
 */
class NativeCurlException extends CurlException
{
    /**
     * @{inherit}
     */
    public function new(msg:String = "Exception thrown by called FF", ?info:PosInfos):Void
    {
        super(msg, info);
    }
}
