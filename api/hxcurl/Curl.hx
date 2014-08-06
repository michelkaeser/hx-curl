package hxcurl;

import hxcurl.CurlException;
import hxcurl.CurlHandle;

/**
 * Abstract CURL class to be subclassed by concrete implementation.
 *
 * @abstract
 */
class Curl
{
    /**
     * Stores the underlaying CURL handle.
     *
     * @var Null<hxcurl.CurlHandle>
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
