# Example

> Download public accessible file via FTP or HTTP(S)

```haxe
class Debug
{
    public static function main():Void
    {
        var curl = new hxcurl.easy.Curl();

        curl.setOption(hxcurl.easy.CurlOpt.URL, "ftp://ftp.rz.uni-wuerzburg.de/pub/linux/debian/README");

        var result = curl.perform();
        Sys.println(result.toString());

        curl.cleanup();
    }
}
```