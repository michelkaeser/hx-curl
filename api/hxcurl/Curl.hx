package hxcurl;

#if cpp
    import cpp.Lib;
#elseif neko
    import neko.Lib;
#else
    #error "Curl (and the whole hxcurl library) is only supported on C++ and Neko targets."
#end
import hxcurl.CurlException;
import hxcurl.CurlHandle;

/**
 *
 * @abstract
 */
class Curl
{
    /**
     * References to the native CURL function implementations loaded through C FFI.
     */
    #if neko
    // initializes the Neko API so alloc_null() etc. becomes valid
    private static var neko_init = {
        var i = Lib.load("libcurl","neko_init", 5);
        if (i != null) {
            i(function(s) return new String(s),
              function(len:Int) { var r = []; if (len > 0) r[len - 1] = null; return r; },
              null, true, false
            );
            i;
        } else {
            throw new CurlException("Could not find NekoApi @ libcurl.");
        }
    }
    #end

    /**
     * Stores the underlaying CURL handle.
     *
     * @var hxcurl.CurlHandle
     */
    private var handle:Null<CurlHandle>;


    /**
     * Constructor to initialize a new Curl instance.
     */
    private function new():Void
    {
        this.handle = null;
    }
}
