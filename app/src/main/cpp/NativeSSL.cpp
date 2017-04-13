#include <jni.h>
#include <string>
#include "LogUtil.h"
#include "MD5.h"

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

jstring getStrMd5(JNIEnv *env, jobject /* this */, jstring inputStr) {
    const char *input = env->GetStringUTFChars(inputStr, JNI_FALSE);
    jsize inputLen = env->GetStringLength(inputStr);
    char *buffer = strMd5(input, inputLen);

    std::string resultCString;
    resultCString.append(buffer);
    jstring result = env->NewStringUTF(resultCString.c_str());

    env->ReleaseStringUTFChars(inputStr, input);
    return result;
}

const char *className = "xyz/openhh/ssl/NativeSSL";

static JNINativeMethod methods[] = {
        {"getStrMd5", "(Ljava/lang/String;)Ljava/lang/String;", (void *) getStrMd5}
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