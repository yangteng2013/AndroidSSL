package xyz.openhh.ssl;

import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;


public class AES {

    private final static String KEY = "abcdefghijklmnop";

    public static byte[] encrypt(String sSrc) {

        String key = KEY;//必须16位
        SecretKeySpec skeySpec = new SecretKeySpec(key.getBytes(), "AES");
        try {
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, skeySpec);
            return cipher.doFinal(sSrc.getBytes("UTF-8"));
        } catch (Exception e) {
            e.printStackTrace();
        }

        return null;
    }


    public static String decrypt(byte[] data) {

        String key = KEY;//必须16位
        SecretKeySpec skeySpec = new SecretKeySpec(key.getBytes(), "AES");
        try {
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.DECRYPT_MODE, skeySpec);
            return new String(cipher.doFinal(data), "UTF-8");
        } catch (Exception e) {
            e.printStackTrace();
        }

        return null;
    }
}
