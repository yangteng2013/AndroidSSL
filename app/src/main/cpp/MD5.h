//
// Created by Duke
//

#ifndef ANDROIDSSL_MD5_H
#define ANDROIDSSL_MD5_H

#include <string>

extern "C" {
#include <openssl/md5.h>
}

class MD5 {

};

std::string strMd5(const char *input, size_t len);

#endif //ANDROIDSSL_MD5_H
