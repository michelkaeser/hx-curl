package hxcurl.share;

#if cpp
    import cpp.Lib;
#elseif neko
    import neko.Lib;
#else
    #error "share.Curl (and the whole hxcurl library) is only supported on C++ and Neko targets."
#end
import hxcurl.CurlHandle;
import hxcurl.CurlException;
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
    private static var hxcurl_share_cleanup:CurlHandle->Void = Lib.load("libcurl", "hxcurl_share_cleanup", 1);
    private static var hxcurl_share_init:Void->CurlHandle    = Lib.load("libcurl", "hxcurl_share_init", 0);
    private static var hxcurl_share_setopt:CurlHandle->CurlOpt->Dynamic->Void = Lib.load("libcurl", "hxcurl_share_setopt", 3);


    /**
     *
     */
    public function new():Void
    {
        super();

        try {
            this.handle = Curl.hxcurl_share_init();
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
            Curl.hxcurl_share_cleanup(this.handle);
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
            Curl.hxcurl_share_setopt(this.handle, option, value);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }
}
