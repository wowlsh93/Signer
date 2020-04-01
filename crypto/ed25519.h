//
// Created by hama on 20. 4. 1..
// use this -> https://github.com/jedisct1/libsodium
// EdDSA using SHA-512 and Curve25519, this variation is named Ed25519.

#ifndef SIGNER_ED25519_H
#define SIGNER_ED25519_H

#include "signer.h"
#include <sodium.h>
namespace bos::crypto {

    class Ed25519 : public Signer {

    public:
        Ed25519();
        virtual ~Ed25519();

        void keypair();
        bool sign(unsigned char *msg,unsigned int msg_len, const unsigned char *skey);
        bool verify(unsigned char *sign, unsigned char *pkey, unsigned char *msg, unsigned int msg_len);


    private:


    };
}


#endif //SIGNER_ED25519_H
