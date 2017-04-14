//
// Created by Duke
//

#ifndef ANDROIDSSL_AES_H
#define ANDROIDSSL_AES_H


#include <string>

extern "C" {
#include "openssl/aes.h"
#include <openssl/evp.h>
};

#include "LogUtil.h"

namespace HH {

    class AES {
    public:
        AES(const unsigned char *key);

        ~AES();

        std::string encrypt(std::string msg);

        std::string decrypt(std::string msg);

    private:
        const unsigned char *key;

    };
}

#endif //ANDROIDSSL_AES_H
