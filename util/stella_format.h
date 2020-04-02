//
// Created by hama on 20. 4. 2..
//

#ifndef SIGNER_STELLA_FORMAT_H
#define SIGNER_STELLA_FORMAT_H

namespace bos::util {

    void encodeStellaAddress(unsigned char * in);
    void decodeStellaAddress(unsigned char * in, unsigned char * out);
    void endcodeStellaScreate(unsigned char * in);
    void decodeStellaScreate(unsigned char * in, unsigned char * out);
}

#endif //SIGNER_STELLA_FORMAT_H
