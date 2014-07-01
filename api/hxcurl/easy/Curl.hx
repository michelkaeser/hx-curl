package hxcurl.easy;

#if cpp
    import cpp.Lib;
#elseif neko
    import neko.Lib;
#else
    #error "easy.Curl (and the whole hxcurl library) is only supported on C++ and Neko targets."
#end
import haxe.io.Bytes;
import haxe.io.BytesData;
import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.easy.CurlInfo;
import hxcurl.easy.CurlOpt;
import hxcurl.easy.CurlPause;
import hxstd.IllegalArgumentException;
import hxstd.IllegalStateException;

using hxcurl.CurlTools;
using StringTools;

/**
 *
 */
class Curl extends hxcurl.Curl
{
    /**
     * References to the native CURL function implementations loaded through C FFI.
     */
    private static var hxcurl_easy_cleanup:CurlHandle->Void           = Lib.load("libcurl", "hxcurl_easy_cleanup", 1);
    private static var hxcurl_easy_duphandle:CurlHandle->CurlHandle   = Lib.load("libcurl", "hxcurl_easy_duphandle", 1);
    private static var hxcurl_easy_escape:CurlHandle->String->String  = Lib.load("libcurl", "hxcurl_easy_escape", 2);
    /*private static var hxcurl_easy_getinfo_string:CurlHandle->CurlInfo->String = Lib.load("libcurl", "hxcurl_easy_getinfo_string", 2);*/
    private static var hxcurl_easy_init:Void->CurlHandle              = Lib.load("libcurl", "hxcurl_easy_init", 0);
    private static var hxcurl_easy_pause:CurlHandle->CurlPause->Void  = Lib.load("libcurl", "hxcurl_easy_pause", 2);
    private static var hxcurl_easy_perform:CurlHandle->BytesData      = Lib.load("libcurl", "hxcurl_easy_perform", 1);
    private static var hxcurl_easy_recv:CurlHandle->Int->BytesData    = Lib.load("libcurl", "hxcurl_easy_recv", 2);
    private static var hxcurl_easy_reset:CurlHandle->Void             = Lib.load("libcurl", "hxcurl_easy_reset", 1);
    private static var hxcurl_easy_send:CurlHandle->BytesData->Int->Int = Lib.load("libcurl", "hxcurl_easy_send", 3);
    private static var hxcurl_easy_setopt:CurlHandle->CurlOpt->Dynamic->Void = Lib.load("libcurl", "hxcurl_easy_setopt", 3);
    private static var hxcurl_easy_unescape:CurlHandle->String->String = Lib.load("libcurl", "hxcurl_easy_unescape", 2);


    /**
     *
     */
    public function new():Void
    {
        super();

        try {
            this.handle = Curl.hxcurl_easy_init();
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
            Curl.hxcurl_easy_cleanup(this.handle);
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
            dup.handle = Curl.hxcurl_easy_duphandle(this.handle);
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
            return Curl.hxcurl_easy_escape(this.handle, str);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    /*public function getInfo(info:CurlInfo):Dynamic
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            var ret:Dynamic = switch(info.returnType()) {
                case 0:  Curl.hxcurl_easy_getinfo_string(this.handle, info);
                default: null;
            }

            return ret;
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }*/

    /**
     *
     */
    public function pause(bitmask:CurlPause):Void
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        try {
            Curl.hxcurl_easy_pause(this.handle, bitmask);
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
            return Bytes.ofData(Curl.hxcurl_easy_perform(this.handle));
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
                read = Bytes.ofData(Curl.hxcurl_easy_recv(this.handle, bytes));
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
            Curl.hxcurl_easy_reset(this.handle);
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
            Curl.hxcurl_easy_setopt(this.handle, option, value);
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
            return Curl.hxcurl_easy_unescape(this.handle, str);
        } catch (ex:Dynamic) {
            throw new CurlException(ex);
        }
    }

    /**
     *
     */
    public function write(bytes:Bytes):Int
    {
        if (this.handle == null) {
            throw new IllegalStateException();
        }

        var sent:Int;
        if (bytes == null || bytes.length == 0) {
            sent = 0;
        } else {
            try {
                sent = Curl.hxcurl_easy_send(this.handle, bytes.getData(), bytes.length);
            } catch (ex:Dynamic) {
                throw new CurlException(ex);
            }
        }

        return sent;
    }
}
