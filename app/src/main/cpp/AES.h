//
// Created by Duke
//

/*
 * 和java的"AES/ECB/PKCS5Padding"匹配

std::string在C++11里面以"\0"结尾，所以不能用std::string做容器，否则数据偶发不完整

参考：http://blog.csdn.net/yasi_xi/article/details/13997337

AES算法的块（block）的长度固定为16字节。假设一个字符串在AES加密前的长度为cleanLen，加密后的长度为cipherLen，则二者有下面的关系，其中的“/”是整除。
cipherLen = (clearLen/16 + 1) * 16
比如：（注意第二行，即使48刚好能被16整除，也要额外追加一个16字节的块）
clearLen	cipherLen
47	48
48	64
49	64
可见，对于AES算法：
1）加密后的长度>=加密前的长度
2）解密后的长度<=解密前的长度
        这对于写代码时的指导意义在于：
1）假如我们要做AES加密的字符串为“The quick brown fox jumps over the lazy dog”，它的长度（不带/0）为43字节，则我们可以计算出加密后的串的长度为 (43 / 16 + 1) * 16 = 48 字节，于是就可以申明加密后的数组如下
unsigned char ciphertextp[48];
2）假如我们知道AES加密后的串的长度为64字节，那么就可以申明解密后的数组如下
unsigned char decryptedtext[64];
 */

#ifndef ANDROIDSSL_AES_H
#define ANDROIDSSL_AES_H


#include <string>

extern "C" {
//#include "openssl/aes.h"
#include <openssl/evp.h>
};

#include "LogUtil.h"

namespace HH {

    class AES {
    public:
        AES(const unsigned char *key);

        ~AES();

        void encrypt(unsigned char *in, size_t inLen, unsigned char *out, size_t *outLen);

        void decrypt(unsigned char *in, size_t inLen, unsigned char *out, size_t *outLen);

    private:
        const unsigned char *key;
        const unsigned char *iv;

    };
}

#endif //ANDROIDSSL_AES_H
