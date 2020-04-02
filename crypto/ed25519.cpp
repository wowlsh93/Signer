//
// Created by hama on 20. 4. 1..
//

#include "ed25519.h"
#include "../util/util.h"
#include "../util/stella_format.h"

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

        bos::util::encodeStellaAddress(pk);
        bos::util::endcodeStellaScreate(seed);
    }

    bool Ed25519::sign(unsigned char *msg, unsigned int msg_len,  unsigned char *skey) {

        unsigned char sig[crypto_sign_BYTES];
        unsigned char secrete[crypto_sign_SEEDBYTES];

        bos::util::decodeStellaScreate(skey, secrete);

        int result = crypto_sign_ed25519_detached(sig, NULL, msg, msg_len, skey);

        if (result == 0){
            std::cout << "sign : " << bos::util::hexStr(sig, crypto_sign_BYTES) <<  std::endl;
        }
        else {
            std::cout << "sign fail" <<  std::endl;
        }

        return true;
    }

    bool Ed25519::verify(std::string sign_hex, unsigned char *pkey, unsigned char *msg, unsigned int msg_len) {

        unsigned char signature[crypto_sign_BYTES];
        unsigned char address[crypto_sign_PUBLICKEYBYTES];

        bos::util::hex2bin(sign_hex, signature);
        bos::util::decodeStellaAddress(pkey, address);


        if (crypto_sign_ed25519_verify_detached(signature, msg, msg_len, address) != 0) {
            std::cout << "verify fail!! " <<  std::endl;
            return false;
        }

        return true;
    }
}