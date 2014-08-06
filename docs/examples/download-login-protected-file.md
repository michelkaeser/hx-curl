# Example

> Download login protected file via FTP or HTTP(S)

```haxe
class Debug
{
    public static function main():Void
    {
        var curl = new hxcurl.easy.Curl();

        curl.setOption(hxcurl.easy.CurlOpt.URL, "ftp://some.password.protected.site/sitemap.xml");
        curl.setOption(hxcurl.easy.CurlOpt.USERNAME, "username");
        curl.setOption(hxcurl.easy.CurlOpt.PASSWORD, "password");

        var result = curl.perform();
        Sys.println(result.toString());

        curl.cleanup();
    }
}
```