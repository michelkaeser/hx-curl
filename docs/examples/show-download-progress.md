# Example

> Show download progress

```haxe
class Debug
{
    public static function main():Void
    {
        var curl = new hxcurl.easy.Curl();

        curl.setOption(hxcurl.easy.CurlOpt.URL, "ftp://ftp.rz.uni-wuerzburg.de/pub/MIRROR/opensuse/distribution/13.1/iso/openSUSE-13.1-Rescue-CD-x86_64.iso");
        curl.setOption(hxcurl.easy.CurlOpt.NOPROGRESS, 0);
        curl.setOption(hxcurl.easy.CurlOpt.PROGRESSFUNCTION, function(dltot:Float, dlnow:Float, ultot:Float, ulnow:Float):Int {
            if (dltot != 0) {
                Sys.println("Downloaded " + dlnow + " of " + dltot + " bytes.");
            }

            return 0; // 0 == all OK, continue to download
        });

        var result = curl.perform();
        Sys.println(result.toString());

        curl.cleanup();
    }
}
```