//
// Created by Duke on 17-4-13.
//

#ifndef ANDROIDSSL_MD5_H
#define ANDROIDSSL_MD5_H
extern "C" {
#include <openssl/md5.h>
}

class MD5 {

};

char *strMd5(const char *input, size_t len);

#endif //ANDROIDSSL_MD5_H
