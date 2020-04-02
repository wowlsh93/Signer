//
// Created by hama on 20. 4. 2..
//

#ifndef SIGNER_BASE32_H
#define SIGNER_BASE32_H

#include <string.h>

namespace bos::util {

    struct Base32 {
        static bool Decode32(unsigned char *in, int inLen, unsigned char *out);

        static bool Encode32(unsigned char *in, int inLen, unsigned char *out);

        static int GetDecode32Length(int bytes);

        static int GetEncode32Length(int bytes);

        static bool Map32(unsigned char *inout32, int inout32Len, unsigned char *alpha32);

        static bool Unmap32(unsigned char *inout32, int inout32Len, unsigned char *alpha32);
    };
}

#endif //SIGNER_BASE32_H
