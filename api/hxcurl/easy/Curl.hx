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
 *
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
    public function duplicate():Curl
    {
        var dup:Curl = new Curl();
        try {
            dup.handle = Curl._duphandle(this.handle);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }

        return dup;
    }

    /**
     *
     */
    public function escape(str:String):String
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            return Curl._escape(this.handle, str);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function getInfo(info:CurlInfo):Dynamic
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            return Curl._getinfo(this.handle, info, CurlInfo.returnType(info));
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function pause(bitmask:CurlPause):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            Curl._pause(this.handle, bitmask);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function perform():Bytes
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            return Bytes.ofData(Curl._perform(this.handle));
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function read(bytes:Int = 1024):Bytes
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }
        if (bytes < 0) {
            throw new IllegalArgumentException("Cannot read a negative amount of bytes");
        }

        var read:Bytes;
        if (bytes == 0) {
            read = Bytes.alloc(0);
        } else {
            try {
                read = Bytes.ofData(Curl._recv(this.handle, bytes));
            } catch (ex:Dynamic) {
                throw new CurlException(ex);
            }
        }

        return read;
    }

    /**
     *
     */
    public function reset():Void
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            Curl._reset(this.handle);
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
    public function unescape(str:String):String
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            return Curl._unescape(this.handle, str);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function write(bytes:Null<Bytes>):Int
    {
        if (this.handle == null) {
            throw new IllegalStateException();
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
