# Example

> Execute multiple `perform()`s in parallel

```haxe
class Debug
{
    public static function main():Void
    {
        var ec1     = new hxcurl.easy.Curl();
        var ec1_buf = new haxe.io.BytesBuffer();
        ec1.setOption(hxcurl.easy.CurlOpt.URL, "ftp://ftp.hq.nasa.gov/robots.txt");
        ec1.setOption(hxcurl.easy.CurlOpt.WRITEFUNCTION, function(data:haxe.io.BytesData):Int {
            var bytes = haxe.io.Bytes.ofData(data);
            ec1_buf.add(bytes);

            return bytes.length;
        });

        var ec2     = new hxcurl.easy.Curl();
        var ec2_buf = new haxe.io.BytesBuffer();
        ec2.setOption(hxcurl.easy.CurlOpt.URL, "ftp://ftp.hq.nasa.gov/robots.txt");
        ec2.setOption(hxcurl.easy.CurlOpt.WRITEFUNCTION, function(data:haxe.io.BytesData):Int {
            var bytes = haxe.io.Bytes.ofData(data);
            ec2_buf.add(bytes);

            return bytes.length;
        });

        var mc = new hxcurl.multi.Curl();

        mc.addHandle(ec1);
        mc.addHandle(ec2);

        var running:Int = 0;
        var timeout:Int = 1;
        while ((running = mc.perform()) != 0) {
            // Sys.println("Running CURL operations: " + running);
            if ((timeout = mc.timeout()) >= 0) {
               Sys.sleep(timeout);
            }
        }

        mc.removeHandle(ec1);
        mc.removeHandle(ec2);

        ec1.cleanup();
        ec2.cleanup();
        mc.cleanup();

        Sys.println(ec1_buf.getBytes().toString());
        Sys.println(ec2_buf.getBytes().toString());
    }
}
```