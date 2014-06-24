package hxcurl.easy;

#if cpp
    import cpp.Lib;
#elseif neko
    import neko.Lib;
#else
    #error "easy.Curl (and the whole hxcurl library) is only supported on C++ and Neko targets."
#end
import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.CurlInfo;
import hxcurl.CurlOpt;
import hxcurl.CurlPause;
import hxcurl.NativeCurlException;

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
    private static var hxcurl_easy_getinfo:CurlHandle->CurlInfo->Int->Dynamic = Lib.load("libcurl", "hxcurl_easy_getinfo", 3);
    private static var hxcurl_easy_init:Void->CurlHandle              = Lib.load("libcurl", "hxcurl_easy_init", 0);
    private static var hxcurl_easy_pause:CurlHandle->CurlPause->Void  = Lib.load("libcurl", "hxcurl_easy_pause", 2);
    private static var hxcurl_easy_perform:CurlHandle->String         = Lib.load("libcurl", "hxcurl_easy_perform", 1);
    private static var hxcurl_easy_recv:CurlHandle->Int->String       = Lib.load("libcurl", "hxcurl_easy_recv", 2);
    private static var hxcurl_easy_reset:CurlHandle->Void             = Lib.load("libcurl", "hxcurl_easy_reset", 1);
    private static var hxcurl_easy_send:CurlHandle->String->Int       = Lib.load("libcurl", "hxcurl_easy_send", 2);
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
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function cleanup():Void
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            Curl.hxcurl_easy_cleanup(this.handle);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
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
            throw new NativeCurlException(ex);
        }

        return dup;
    }

    /**
     *
     */
    public function escape(str:String):String
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            return Curl.hxcurl_easy_escape(this.handle, str);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function getInfo(info:CurlInfo):Dynamic
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        // TODO: switch didn't work (Capture variables must be lower-case)
        var infoType = if (info == EFFECTIVE_URL || info == REDIRECT_URL || info == CONTENT_TYPE
          || info == PRIVATE || info == PRIMARY_IP || info == LOCAL_IP || info == FTP_ENTRY_PATH || info == RTSP_SESSION_ID) {
            0; // char*
        } else if (info == TOTAL_TIME || info == NAMELOOKUP_TIME || info == CONNECT_TIME || info == APPCONNECT_TIME
          || info == PRETRANSFER_TIME || info == STARTTRANSFER_TIME || info == REDIRECT_TIME || info == SIZE_UPLOAD
          || info == SIZE_DOWNLOAD || info == SPEED_DOWNLOAD || info == SPEED_UPLOAD || info == CONTENT_LENGTH_DOWNLOAD
          || info == CONTENT_LENGTH_UPLOAD) {
            1; // double*
        } else if (info == SSL_ENGINES || info == COOKIELIST) {
            5; // struct curl_slist*
        } else if (info == CERTINFO) {
            6; // struct curl_certinfo*
        } else if (info == TLS_SESSION) {
            7; // struct curl_tlsinfo*
        } else {
            2; // long*
        }

        try {
            return Curl.hxcurl_easy_getinfo(this.handle, info, infoType);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function pause(bitmask:CurlPause):Void
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            Curl.hxcurl_easy_pause(this.handle, bitmask);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function perform():String
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            return Curl.hxcurl_easy_perform(this.handle);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function read(bytes:Int):String
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            return Curl.hxcurl_easy_recv(this.handle, bytes);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function reset():Void
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            Curl.hxcurl_easy_reset(this.handle);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function setOption(option:CurlOpt, value:Dynamic):Void
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            Curl.hxcurl_easy_setopt(this.handle, option, value);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function unescape(str:String):String
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            return Curl.hxcurl_easy_unescape(this.handle, str);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }

    /**
     *
     */
    public function write(msg:String):Int
    {
        if (this.handle == null) {
            throw new CurlException();
        }

        try {
            return Curl.hxcurl_easy_send(this.handle, msg);
        } catch (ex:Dynamic) {
            throw new NativeCurlException(ex);
        }
    }
}
