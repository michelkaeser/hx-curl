package hxcurl.easy;

import haxe.io.Bytes;
import haxe.io.BytesData;
import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.Loader;
import hxcurl.easy.CurlInfo;
import hxcurl.easy.CurlOpt;
import hxcurl.easy.CurlPause;
import hxstd.IllegalArgumentException;
import hxstd.IllegalStateException;

using StringTools;

/**
 * Easy CURL wrapper class providing the Haxe interface for the underlaying FFI calls (to libcurl).
 */
class Curl extends hxcurl.Curl
{
    /**
     * References to the native CURL function implementations loaded through C FFI.
     */
    private static var _cleanup:CurlHandle->Void                   = Loader.load("hx_curl_easy_cleanup", 1);
    private static var _duphandle:CurlHandle->CurlHandle           = Loader.load("hx_curl_easy_duphandle", 1);
    private static var _escape:CurlHandle->String->String          = Loader.load("hx_curl_easy_escape", 2);
    private static var _getinfo:CurlHandle->CurlInfo->Int->Dynamic = Loader.load("hx_curl_easy_getinfo", 3);
    private static var _init:Void->CurlHandle                      = Loader.load("hx_curl_easy_init", 0);
    private static var _pause:CurlHandle->CurlPause->Void          = Loader.load("hx_curl_easy_pause", 2);
    private static var _perform:CurlHandle->BytesData              = Loader.load("hx_curl_easy_perform", 1);
    private static var _recv:CurlHandle->Int->BytesData            = Loader.load("hx_curl_easy_recv", 2);
    private static var _reset:CurlHandle->Void                     = Loader.load("hx_curl_easy_reset", 1);
    private static var _send:CurlHandle->BytesData->Int->Int       = Loader.load("hx_curl_easy_send", 3);
    private static var _setopt:CurlHandle->CurlOpt->Dynamic->Void  = Loader.load("hx_curl_easy_setopt", 3);
    private static var _unescape:CurlHandle->String->String        = Loader.load("hx_curl_easy_unescape", 2);


    /**
     * Constructor to initialize a new easy CURL instance.
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
            this.handle = null;
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Duplicates the current instance.
     *
     * @return hxcurl.easy.Curl the duplicated CURL
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function duplicate():Curl
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        var dup:Curl = new Curl();
        try {
            dup.handle = Curl._duphandle(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }

        return dup;
    }

    /**
     * Escapes the provided String so it can safely be transfered over a CURL session.
     *
     * @return String the escaped String
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function escape(str:String):String
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            return Curl._escape(this.handle, str);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Returns the requested CURL information (e.g. time needed to perform an action).
     *
     * This method should only be called AFTER .perform() has been called.
     *
     * @param hxcurl.easy.CurlInfo info the information to get
     *
     * @return Dynamic
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function getInfo(info:CurlInfo):Dynamic
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            return Curl._getinfo(this.handle, info, CurlInfo.returnType(info));
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Tells the CURL handle to pause itself (or its actions).
     *
     * @param hxcurl.easy.CurlPause bitmask controls what should be paused
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function pause(bitmask:CurlPause):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            Curl._pause(this.handle, bitmask);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Performs the actual work using all options set upon calling the method.
     *
     * @return haxe.io.Bytes
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function perform():Bytes
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            return Bytes.ofData(Curl._perform(this.handle));
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Reads up to nbytes Bytes from the instance's input stream.
     *
     * @param Int nbytes the number of Bytes to read
     *
     * @return haxe.io.Bytes the read Bytes
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function read(nbytes:Int = 1024):Bytes
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }
        if (nbytes < 0) {
            throw new IllegalArgumentException("Cannot read a negative amount of bytes");
        }

        var read:Bytes;
        if (nbytes == 0) {
            read = Bytes.alloc(0);
        } else {
            try {
                read = Bytes.ofData(Curl._recv(this.handle, nbytes));
            } catch (ex:Dynamic) {
                throw new CurlException(ex);
            }
        }

        return read;
    }

    /**
     * Resets the CURL handle so it behaves as it would have been newly initialized.
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function reset():Void
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            Curl._reset(this.handle);
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
     * @param hxcurl.easy.CurlOpt option the option to set
     * @param Dynamic             value  the value to set
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
     * Unescapes the escaped String.
     *
     * @param String str the String to unescape
     *
     * @return String the unescaped String
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function unescape(str:String):String
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        try {
            return Curl._unescape(this.handle, str);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     * Writes the Bytes to the instance's output stream.
     *
     * @param Null<haxe.io.Bytes> bytes the Bytes to write
     *
     * @return Int the number of written Bytes
     *
     * @throws hxstd.IllegalStateException if the instance has already been cleaned
     * @throws hxcurl.CurlException        if the FFI call raises an error
     */
    public function write(bytes:Null<Bytes>):Int
    {
        if (this.handle == null) {
            throw new IllegalStateException("CURL handle not available");
        }

        var sent:Int;
        if (bytes == null || bytes.length == 0) {
            sent = 0;
        } else {
            try {
                sent = Curl._send(this.handle, bytes.getData(), bytes.length);
            } catch (ex:Dynamic) {
                throw new CurlException(ex);
            }
        }

        return sent;
    }
}
