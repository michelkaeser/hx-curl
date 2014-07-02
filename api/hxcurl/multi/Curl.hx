package hxcurl.multi;

#if cpp
    import cpp.Lib;
#elseif neko
    import neko.Lib;
#else
    #error "multi.Curl (and the whole hxcurl library) is only supported on C++ and Neko targets."
#end
import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.multi.CurlOpt;
import hxstd.IllegalArgumentException;
import hxstd.IllegalStateException;

using StringTools;

/**
 *
 */
class Curl extends hxcurl.Curl
{
    /**
     * References to the native CURL function implementations loaded through C FFI.
     */
    private static var hxcurl_multi_add_handle:CurlHandle->CurlHandle->Void = Lib.load("libcurl", "hxcurl_multi_add_handle", 2);
    private static var hxcurl_multi_cleanup:CurlHandle->Void = Lib.load("libcurl", "hxcurl_multi_cleanup", 1);
    private static var hxcurl_multi_init:Void->CurlHandle    = Lib.load("libcurl", "hxcurl_multi_init", 0);
    private static var hxcurl_multi_perform:CurlHandle->Int  = Lib.load("libcurl", "hxcurl_multi_perform", 1);
    private static var hxcurl_multi_remove_handle:CurlHandle->CurlHandle->Void = Lib.load("libcurl", "hxcurl_multi_remove_handle", 2);
    private static var hxcurl_multi_setopt:CurlHandle->CurlOpt->Dynamic->Void = Lib.load("libcurl", "hxcurl_multi_setopt", 3);
    private static var hxcurl_multi_timeout:CurlHandle->Int  = Lib.load("libcurl", "hxcurl_multi_timeout", 1);


    /**
     *
     */
    public function new():Void
    {
        super();

        try {
            this.handle = Curl.hxcurl_multi_init();
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function addHandle(easyCurl:hxcurl.easy.Curl):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            Curl.hxcurl_multi_add_handle(this.handle, easyCurl.handle);
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
            Curl.hxcurl_multi_cleanup(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function perform():Int
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            return Curl.hxcurl_multi_perform(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function removeHandle(easyCurl:hxcurl.easy.Curl):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            Curl.hxcurl_multi_remove_handle(this.handle, easyCurl.handle);
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
            Curl.hxcurl_multi_setopt(this.handle, option, value);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function timeout():Int
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            return Curl.hxcurl_multi_timeout(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }
}
