package hxcurl.multi;

import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.Loader;
import hxcurl.multi.CurlOpt;
import hxstd.IllegalArgumentException;
import hxstd.IllegalStateException;

using StringTools;

/**
 * Multi CURL wrapper class providing the Haxe interface for the underlaying FFI calls (to libcurl).
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
     * Constructor to initialize a new multi CURL instance.
     *
     * @throws hxcurl.CurlException if initializing a new CURL handle fails
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
     * Adds the easy CURL handle to the current instance.
     *
     * @param hxcurl.easy.Curl easyCurl the easy CURL handle to add
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function addHandle(easyCurl:hxcurl.easy.Curl):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            Curl._add_handle(this.handle, easyCurl.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Closes all connections this handle has used and possibly has kept open until now.
     *
     * Don't call this function if you intend to transfer more files.
     *
     * Attn: Make sure you removed all easy CURL's before calling this function!
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function cleanup():Void
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            Curl._cleanup(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Performs the actual work using all options set upon calling the method.
     *
     * @return Int the number of yet working easy CURL handles (0 == done)
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function perform():Int
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            return Curl._perform(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Removes the easy CURL handle from the current instance.
     *
     * @param hxcurl.easy.CURL easyCurl the easy CURL to remove
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function removeHandle(easyCurl:hxcurl.easy.Curl):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            Curl._remove_handle(this.handle, easyCurl.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Sets the instance's option 'option' to 'value'.
     *
     * The value can be pretty much everything, from callback functions to Strings etc.
     * Make sure to checkout the official libcurl documentation to see which option requires/
     * supports what kind of value.
     *
     * @param hxcurl.multi.CurlOpt option the option to set
     * @param Dynamic              value  the value to set
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function setOption(option:CurlOpt, value:Dynamic):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            Curl._setopt(this.handle, option, value);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Returns the timout one should wait before checking again if all underlaying
     * easy CURL handles are done.
     *
     * This should be called within a while() loop after perform() to check if all
     * actions have finished.
     *
     * @return Int the number of milliseconds one should wait
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function timeout():Int
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            return Curl._timeout(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }
}
