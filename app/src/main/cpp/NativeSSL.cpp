#include <jni.h>
#include <string>
#include "LogUtil.h"
#include "MD5.h"
#include "AES.h"

extern "C" {

#include "openssl/opensslv.h"
#include "openssl/crypto.h"

JNIEXPORT jstring JNICALL
Java_xyz_openhh_ssl_NativeSSL_getSSLVersion(
        JNIEnv *env,
        jobject /* this */) {
//    std::string hello = "Hello from C++";
    return env->NewStringUTF(SSLeay_version(SSLEAY_VERSION));
}

}


jstring charToJString(JNIEnv *env, char *data, size_t len) {
    jbyteArray array = env->NewByteArray(len);
    env->SetByteArrayRegion(array, 0, len, (const jbyte *) data);
    jstring strEncode = env->NewStringUTF("UTF-8");
    jclass cls = env->FindClass("java/lang/String");
    jmethodID ctor = env->GetMethodID(cls, "<init>", "([BLjava/lang/String;)V");
    jstring object = (jstring) env->NewObject(cls, ctor, array, strEncode);
    return object;
}

jstring getStrMd5(JNIEnv *env, jobject /* this */, jstring inputStr) {
    const char *input = env->GetStringUTFChars(inputStr, JNI_FALSE);
    jsize inputLen = env->GetStringLength(inputStr);
    std::string resultCString = strMd5(input, inputLen);

//    jstring result = env->NewStringUTF(resultCString.c_str());

    jstring result = charToJString(env, (char *) resultCString.c_str(), resultCString.size());
    env->ReleaseStringUTFChars(inputStr, input);
    return result;
}

jbyteArray aesEncrypt(JNIEnv *env, jobject /* this */, jbyteArray inputArray) {
    jbyte *bBuffer = env->GetByteArrayElements(inputArray, JNI_FALSE);
    unsigned char *in = (unsigned char *) bBuffer;
    size_t inLen = env->GetArrayLength(inputArray);
    unsigned char out[1024];
    memset(out, 0, 1024);
    size_t outLen;


    unsigned char key[] = "abcdefghijklmnop";

    HH::AES *aes = new HH::AES(key);
    aes->encrypt(in, inLen, out, &outLen);
    delete aes;


//    jstring result = charToJString(env, resultCString);
    jbyteArray array = env->NewByteArray(outLen);
    env->SetByteArrayRegion(array, 0, outLen, (const jbyte *) out);


    env->ReleaseByteArrayElements(inputArray, bBuffer, JNI_COMMIT);
    return array;
}

jstring aesDecrypt(JNIEnv *env, jobject /* this */, jbyteArray inputArray) {
    jbyte *bBuffer = env->GetByteArrayElements(inputArray, JNI_FALSE);
    unsigned char *in = (unsigned char *) bBuffer;
    size_t inLen = env->GetArrayLength(inputArray);
    unsigned char out[1024];
    memset(out, 0, 1024);
    size_t outLen;

    unsigned char key[] = "abcdefghijklmnop";
    HH::AES *aes = new HH::AES(key);
    aes->decrypt(in, inLen, out, &outLen);
    delete aes;

    jstring result = charToJString(env, (char *) out, outLen);


    env->ReleaseByteArrayElements(inputArray, bBuffer, JNI_COMMIT);
    return result;
}


const char *className = "xyz/openhh/ssl/NativeSSL";

static JNINativeMethod methods[] = {
        {"getStrMd5",  "(Ljava/lang/String;)Ljava/lang/String;", (void *) getStrMd5},
        {"aesEncrypt", "([B)[B",                                 (void *) aesEncrypt},
        {"aesDecrypt", "([B)Ljava/lang/String;",                 (void *) aesDecrypt}
};

jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    jclass clazz = NULL;
    JNIEnv *env = NULL;


    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        LOGE("JNI_OnLoad->GetEnv error!");
        return -1;
    }

    clazz = env->FindClass(className);
    if (!clazz) {
        LOGE("JNI_OnLoad->FindClass error!");
        return -1;
    }

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        LOGE("JNI_OnLoad->RegisterNatives error!");
        return -1;
    }

    return JNI_VERSION_1_6;
}