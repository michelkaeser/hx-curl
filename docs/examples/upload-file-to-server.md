# Example

> Upload a file to a protected FTP server

```haxe
class Debug
{
    public static function main():Void
    {
        var curl = new hxcurl.easy.Curl();

        curl.setOption(hxcurl.easy.CurlOpt.UPLOAD, 1);
        curl.setOption(hxcurl.easy.CurlOpt.URL, "ftp://some.protected.server/hxcurl.upload");
        curl.setOption(hxcurl.easy.CurlOpt.USERNAME, "username");
        curl.setOption(hxcurl.easy.CurlOpt.PASSWORD, "password");

        var content = sys.io.File.getBytes("/path/to/local/file");
        var current = 0;
        curl.setOption(hxcurl.easy.CurlOpt.READFUNCTION, function(nbytes:Int):haxe.io.BytesData {
            var bytes:haxe.io.Bytes;
            if (nbytes > 0 && current < content.length) {
                var remaining = content.length - current;
                if ((remaining - nbytes) > 0) {
                    remaining -= nbytes;
                }
                bytes = content.sub(current, remaining);
                current += remaining;
            } else {
                bytes = haxe.io.Bytes.alloc(0);
            }

            return bytes.getData();
        });

        var result = curl.perform();
        Sys.println(result.toString());

        curl.cleanup();
    }
}
```