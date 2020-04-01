//
// Created by hama on 20. 4. 1..
//

#include "ed25519.h"
#include "../util/util.h"

namespace bos::crypto {


    Ed25519::Ed25519() {
        if (sodium_init() == -1) {
            std::cout << "sodium init fail" << std::endl;
        }
    }

    Ed25519::~Ed25519() {

    }

    void Ed25519::keypair() {

        unsigned char seed[crypto_sign_SEEDBYTES]; // (32U)
        randombytes_buf(seed,sizeof seed);
        unsigned char pk[crypto_sign_PUBLICKEYBYTES]; // 32U
        unsigned char sk[crypto_sign_SECRETKEYBYTES]; // (32U + 32U)
        crypto_sign_ed25519_seed_keypair(pk, sk, seed);


        std::cout << "pk : " << bos::util::hexStr(pk, crypto_sign_PUBLICKEYBYTES) <<  std::endl;
        //std::cout << "sk : " << bos::util::hexStr(sk, crypto_sign_SECRETKEYBYTES) <<  std::endl;
        std::cout << "seed : " << bos::util::hexStr(seed, crypto_sign_SEEDBYTES) <<  std::endl;


    }

    bool Ed25519::sign(unsigned char *msg, unsigned int msg_len, const unsigned char *skey) {

        unsigned char sig[crypto_sign_BYTES];

        int result = crypto_sign_ed25519_detached(sig, NULL, msg, msg_len, skey);

        if (result == 0){
            std::cout << "signature : " << bos::util::hexStr(sig, crypto_sign_BYTES) <<  std::endl;
        }
        else {
            std::cout << "sign fail" <<  std::endl;
        }

        return true;
    }

    bool Ed25519::verify(unsigned char *sign, unsigned char *pkey, unsigned char *msg, unsigned int msg_len) {

        if (crypto_sign_ed25519_verify_detached(sign, msg, msg_len, pkey) != 0) {
            std::cout << "verify fail!! " <<  std::endl;
            return false;
        }

        return true;
    }
}