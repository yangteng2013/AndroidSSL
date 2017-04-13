//
// Created by Duke on 17-4-13.
//

#include <stdio.h>
#include <string.h>
#include "MD5.h"


char *strMd5(const char *input, size_t len) {
    MD5_CTX ctx;
    unsigned char md5[16] = {0};
    char buff[33] = {'\0'};
    char tmp[3] = {'\0'};
    int i;

    MD5_Init(&ctx);

    MD5_Update(&ctx, input, len);

    MD5_Final(md5, &ctx);

    for (i = 0; i < 16; i++) {
        sprintf(tmp, "%02x", md5[i]);
        strcat(buff, tmp);
    }
    //printf("%s\n",buff);


    return buff;
}