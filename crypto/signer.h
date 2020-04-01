//
// Created by hama on 20. 3. 31..
//

#ifndef SIGNER_SIGNER_H
#define SIGNER_SIGNER_H

#include <iostream>

namespace bos::crypto {


    class Signer {
        public:
            virtual void keypair() = 0;
            virtual bool sign(unsigned char *msg, unsigned int msg_len, const unsigned char *skey) = 0;
            virtual bool verify(unsigned char *sign, unsigned char *pubkey, unsigned char *msg,  unsigned int msg_len) = 0;

    };
}




#endif //SIGNER_SIGNER_H
