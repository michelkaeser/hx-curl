# Example

> Writing into a custom BytesBuffer

```haxe
class Debug
{
    public static function main():Void
    {
        var curl = new hxcurl.easy.Curl();
        var buff = new haxe.io.BytesBuffer();

        curl.setOption(hxcurl.easy.CurlOpt.URL, "ftp://ftp.rz.uni-wuerzburg.de/pub/MIRROR/opensuse/distribution/13.1/iso/openSUSE-13.1-Rescue-CD-x86_64.iso");
        curl.setOption(hxcurl.easy.CurlOpt.WRITEFUNCTION, function(data:haxe.io.BytesData):Int {
            var bytes = haxe.io.Bytes.ofData(data);
            buff.add(bytes);

            return bytes.length; // number of bytes toke care of
        });


        curl.perform();
        Sys.println(buff.getBytes().toString());

        curl.cleanup();
    }
}
```