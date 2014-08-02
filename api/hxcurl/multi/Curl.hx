package hxcurl.multi;

import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.Loader;
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
    private static var _add_handle:CurlHandle->CurlHandle->Void    = Loader.load("hx_curl_multi_add_handle", 2);
    private static var _cleanup:CurlHandle->Void                   = Loader.load("hx_curl_multi_cleanup", 1);
    private static var _init:Void->CurlHandle                      = Loader.load("hx_curl_multi_init", 0);
    private static var _perform:CurlHandle->Int                    = Loader.load("hx_curl_multi_perform", 1);
    private static var _remove_handle:CurlHandle->CurlHandle->Void = Loader.load("hx_curl_multi_remove_handle", 2);
    private static var _setopt:CurlHandle->CurlOpt->Dynamic->Void  = Loader.load("hx_curl_multi_setopt", 3);
    private static var _timeout:CurlHandle->Int                    = Loader.load("hx_curl_multi_timeout", 1);


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
    public function addHandle(easyCurl:hxcurl.easy.Curl):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            Curl._add_handle(this.handle, easyCurl.handle);
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
    public function perform():Int
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            return Curl._perform(this.handle);
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
            Curl._remove_handle(this.handle, easyCurl.handle);
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

    /**
     *
     */
    public function timeout():Int
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            return Curl._timeout(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }
}
