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

    public static native String getFileMd5(String fileName);


    //AES
    public static native byte[] aesEncrypt(byte[] data);

    public static native String aesDecrypt(byte[] data);
}
