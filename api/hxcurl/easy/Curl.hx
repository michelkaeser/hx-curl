package hxcurl.easy;

#if cpp
    import cpp.Lib;
#elseif neko
    import neko.Lib;
#else
    #error "Curl (and the whole hxcurl library) is only supported on C++ and Neko targets."
#end
import hxcurl.CurlHandle;
import hxcurl.CurlException;
import hxcurl.NativeCurlException;

/**
 *
 */
class Curl extends hxcurl.Curl
{
    /**
     * References to the native CURL function implementations loaded through C FFI.
     */
    private static var hxcurl_easy_cleanup:CurlHandle->Void            = Lib.load("libcurl", "hxcurl_easy_cleanup", 1);
    private static var hxcurl_easy_duphandle:CurlHandle->CurlHandle    = Lib.load("libcurl", "hxcurl_easy_duphandle", 1);
    private static var hxcurl_easy_escape:CurlHandle->String->String   = Lib.load("libcurl", "hxcurl_easy_escape", 2);
    private static var hxcurl_easy_init:Void->CurlHandle               = Lib.load("libcurl", "hxcurl_easy_init", 0);
    private static var hxcurl_easy_pause:CurlHandle->Int->Void         = Lib.load("libcurl", "hxcurl_easy_pause", 2);
    private static var hxcurl_easy_perform:CurlHandle->Void            = Lib.load("libcurl", "hxcurl_easy_perform", 1);
    private static var hxcurl_easy_recv:CurlHandle->Int->String        = Lib.load("libcurl", "hxcurl_easy_recv", 2);
    private static var hxcurl_easy_reset:CurlHandle->Void              = Lib.load("libcurl", "hxcurl_easy_reset", 1);
    private static var hxcurl_easy_send:CurlHandle->String->Int        = Lib.load("libcurl", "hxcurl_easy_send", 2);
    private static var hxcurl_easy_unescape:CurlHandle->String->String = Lib.load("libcurl", "hxcurl_easy_unescape", 2);


    /**
     * Constructor to initialize a new Curl instance.
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
}
