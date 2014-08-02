package hxcurl.share;

import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.Loader;
import hxcurl.share.CurlOpt;
import hxstd.IllegalStateException;

/**
 *
 */
class Curl extends hxcurl.Curl
{
    /**
     * References to the native CURL function implementations loaded through C FFI.
     */
    private static var _cleanup:CurlHandle->Void                  = Loader.load("hx_curl_share_cleanup", 1);
    private static var _init:Void->CurlHandle                     = Loader.load("hx_curl_share_init", 0);
    private static var _setopt:CurlHandle->CurlOpt->Dynamic->Void = Loader.load("hx_curl_share_setopt", 3);


    /**
     *
     */
    public function new():Void
    {
        super();

        try {
            this.handle = Curl._init();
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function cleanup():Void
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            Curl._cleanup(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function setOption(option:CurlOpt, value:Dynamic):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            Curl._setopt(this.handle, option, value);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }
}
