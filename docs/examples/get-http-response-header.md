# Example

> Get HTTP(S) response headers

```haxe
class Debug
{
    public static function main():Void
    {
        var curl = new hxcurl.easy.Curl();

        curl.setOption(hxcurl.easy.CurlOpt.URL, "https://www.google.com");
        curl.setOption(hxcurl.easy.CurlOpt.HEADER, 1);
        curl.setOption(hxcurl.easy.CurlOpt.NOBODY, 1);

        var result = curl.perform();
        Sys.println(result.toString());

        curl.cleanup();
    }
}
```