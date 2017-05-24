//
// Created by Duke
//参考：https://my.oschina.net/gesuper/blog/174035
//Evp aes ecb 默认是PKCS5Padding
//

#include "AES.h"
#include "openssl/aes.h"

using namespace HH;

AES::AES(const unsigned char *key) {
    this->key = key;

    this->iv = NULL;
}

AES::~AES() {

}

void AES::encrypt(unsigned char *in, size_t inLen, unsigned char *out, size_t *outLen) {


    int keylength = 128;

    // so i can do with this aes-cbc-128 aes-cbc-192 aes-cbc-256
    AES_KEY enc_key;
    AES_set_encrypt_key(key, keylength, &enc_key);
    AES_ecb_encrypt(in, out, &enc_key, AES_ENCRYPT);

}

void AES::decrypt(unsigned char *in, size_t inLen, unsigned char *out, size_t *outLen) {


    int keylength = 128;

    // so i can do with this aes-cbc-128 aes-cbc-192 aes-cbc-256
    AES_KEY dec_key;

    AES_set_decrypt_key(key, keylength, &dec_key);
    AES_ecb_encrypt(in, out, &dec_key, AES_DECRYPT);

}

void handleErrors(void) {
//    ERR_print_errors_fp(stderr);
//    abort();
}

//void AES::evp_encrypt(unsigned char *in, size_t inLen, unsigned char *out, size_t *outLen) {
//
//    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
//    //此init做的仅是将ctx内存 memset为0
////    EVP_CIPHER_CTX_reset(ctx);
//
//    //cipher  = EVP_aes_128_ecb();
//    //原型为int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,const EVP_CIPHER *cipher, ENGINE *impl, const unsigned char *key, const unsigned char *iv)
//    //另外对于ecb电子密码本模式来说，各分组独立加解密，前后没有关系，也用不着iv
//    EVP_EncryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv);
//
//    int outl = 0;
//    *outLen = 0;
//    //这个EVP_EncryptUpdate的实现实际就是将in按照inl的长度去加密，实现会取得该cipher的块大小（对aes_128来说是16字节）并将block-size的整数倍去加密。
//    //如果输入为50字节，则此处仅加密48字节，outl也为48字节。输入in中的最后两字节拷贝到ctx->buf缓存起来。
//    //对于inl为block_size整数倍的情形，且ctx->buf并没有以前遗留的数据时则直接加解密操作，省去很多后续工作。
//    EVP_EncryptUpdate(ctx, out, &outl, in, inLen);
//    *outLen += outl;
//    //余下最后n字节。此处进行处理。
//    //如果不支持pading，且还有数据的话就出错，否则，将block_size-待处理字节数个数个字节设置为此个数的值，如block_size=16,数据长度为4，则将后面的12字节设置为16-4=12，补齐为一个分组后加密
//    //对于前面为整分组时，如输入数据为16字节，最后再调用此Final时，不过是对16个0进行加密，此密文不用即可，也根本用不着调一下这Final。
//    int test = inLen >> 4;
//    if (inLen != test << 4) {
//        EVP_EncryptFinal_ex(ctx, out + *outLen, &outl);
//        *outLen += outl;
//    }
////    EVP_CIPHER_CTX_reset(ctx);
//    EVP_CIPHER_CTX_free(ctx);
//
//
//}
//
//void AES::evp_decrypt(unsigned char *in, size_t inLen, unsigned char *out, size_t *outLen) {
//
//    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
//    //此init做的仅是将ctx内存 memset为0
////    EVP_CIPHER_CTX_reset(ctx);
//
//    //cipher  = EVP_aes_128_ecb();
//    //原型为int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,const EVP_CIPHER *cipher, ENGINE *impl, const unsigned char *key, const unsigned char *iv)
//    //另外对于ecb电子密码本模式来说，各分组独立加解密，前后没有关系，也用不着iv
//    EVP_DecryptInit_ex(ctx, EVP_aes_128_ecb(), NULL, key, iv);
//
////    EVP_CIPHER_CTX_set_padding()
//
//    int outl = 0;
//    *outLen = 0;
//
//    EVP_DecryptUpdate(ctx, out + *outLen, &outl, in, inLen);
//    *outLen += outl;
//
//    EVP_DecryptFinal_ex(ctx, out + *outLen, &outl);
//    *outLen += outl;
//    out[*outLen] = 0;
//    EVP_CIPHER_CTX_free(ctx);
//
//}
