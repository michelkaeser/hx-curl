package hxcurl.share;

import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.Loader;
import hxcurl.share.CurlOpt;
import hxstd.IllegalStateException;

/**
 * Share CURL wrapper class providing the Haxe interface for the underlaying FFI calls (to libcurl).
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
     * Constructor to initialize a new share CURL instance.
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
     * Closes all connections this handle has used and possibly has kept open until now.
     *
     * Don't call this function if you intend to transfer more files.
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
     * Sets the instance's option 'option' to 'value'.
     *
     * The value can be pretty much everything, from callback functions to Strings etc.
     * Make sure to checkout the official libcurl documentation to see which option requires/
     * supports what kind of value.
     *
     * @param hxcurl.share.CurlOpt option the option to set
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
}
