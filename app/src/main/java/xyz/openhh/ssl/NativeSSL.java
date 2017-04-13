package xyz.openhh.ssl;

/**
 * Created by Duke
 */

public class NativeSSL {


    static {
        System.loadLibrary("hhssl");
    }


    public static native String getSSLVersion();

    public static native String getStrMd5(String inputStr);
}
