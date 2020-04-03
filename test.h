//
// Created by hama on 20. 4. 2..
//

#ifndef SIGNER_TEST_H
#define SIGNER_TEST_H

#include <iostream>
#include <iostream>
#include <iomanip>


#include "command/command.h"

#include "util/crc16.h"
#include "util/base32.h"

std::string hexStr5(const unsigned char *data, int len)
{
    std::stringstream ss;
    ss << std::hex;

    for( int i(0) ; i < len; ++i )
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

void hex2bin5(const std::string& hex, uint8_t* data) {

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        (*data) = (char)strtol(byteString.c_str(), NULL, 16);
        data += 1;
    }
}


void test1() {

    if (sodium_init() == -1) {
        std::cout << "sodium init fail" << std::endl;
        return;
    }

    unsigned char seed[crypto_sign_SEEDBYTES]; // (32U)

    std::cout << sizeof seed << std::endl;
    randombytes_buf(seed, crypto_sign_SEEDBYTES);

    std::cout << "random : " << hexStr5(seed, crypto_sign_SEEDBYTES + 32) <<  std::endl;

    unsigned char pk[crypto_sign_PUBLICKEYBYTES]; // 32U
    unsigned char sk[crypto_sign_SECRETKEYBYTES]; // (32U + 32U)


    crypto_sign_ed25519_seed_keypair(pk, sk, seed);

//
//    unsigned char seed3[32]; // (32U)
//    for (int i = 0 ; i < 64 ; i++){
//        seed3[i] = seed[i];
//    }
//
//
//    for (int i = 32 ; i < 64 ; i++){
//        seed[i] = 0;
//    }


    std::cout << "pk : " << hexStr5(pk, crypto_sign_PUBLICKEYBYTES) <<  std::endl;
    std::cout << "sk : " << hexStr5(sk, crypto_sign_SECRETKEYBYTES) <<  std::endl;
    std::cout << "seed : " << hexStr5(seed, crypto_sign_SEEDBYTES + 32) <<  std::endl;


    #define MESSAGE (const unsigned char *) "test"
    #define MESSAGE_LEN 4

    unsigned char sig[crypto_sign_BYTES];
    crypto_sign_ed25519_detached(sig, NULL, MESSAGE, MESSAGE_LEN, seed);

    std::cout << "signature : " << hexStr5(sig, crypto_sign_BYTES) <<  std::endl;

    if (crypto_sign_ed25519_verify_detached(sig, MESSAGE, MESSAGE_LEN, pk) != 0) {
        std::cout << "verify fail!! " <<  std::endl;
    }
}


#define MESSAGE (const unsigned char *) "hello"
#define MESSAGE_LEN 5

void test2() {

//    pubkey : 4bce283c01b2103da1c451375fa472ddfc3b710fbc31dc6887a5e6fedd89cedf
//    seed : 1fa5b38bc9ddfea85901e00a66a1b6feb941dbdcfbe6681a492f5a9f070e0994
//    sig : 84756611dfc2e8b0eab7da00f18c6edf5941e8d62ff182656db1889ad1d249ae98c1159b3a29ac62b035e56b36c1df0d16a5f5784d917495bd7ccb85b40d2a03
//    data : hello

    unsigned char seed[crypto_sign_SEEDBYTES]; // (32U)
    unsigned char pk[crypto_sign_PUBLICKEYBYTES]; // 32U
    unsigned char sk[crypto_sign_SECRETKEYBYTES]; // (32U + 32U)


    hex2bin5("1fa5b38bc9ddfea85901e0bos::util::b0a66a1b6feb941dbdcfbe6681a492f5a9f070e0994", seed);
    hex2bin5("4bce283c01b2103da1c451375fa472ddfc3b710fbc31dc6887a5e6fedd89cedf", pk);
    hex2bin5("1fa5b38bc9ddfea85901e00a66a1b6feb941dbdcfbe6681a492f5a9f070e0994", seed);


    unsigned char sig[crypto_sign_BYTES];
    crypto_sign_ed25519_detached(sig, NULL, MESSAGE, MESSAGE_LEN, seed);

    std::cout << "signature : " << hexStr5(sig, crypto_sign_BYTES) <<  std::endl;

    if (crypto_sign_ed25519_verify_detached(sig, MESSAGE, MESSAGE_LEN, pk) != 0) {
        std::cout << "verify fail!! " <<  std::endl;
    }

}


void test3(){

    if (sodium_init() == -1) {
        std::cout << "sodium init fail" << std::endl;
        return;
    }

    unsigned char seed[crypto_sign_SEEDBYTES]; // (32U)

    randombytes_buf(seed, sizeof seed);

    unsigned char pk[crypto_sign_PUBLICKEYBYTES]; // 32U
    unsigned char sk[crypto_sign_SECRETKEYBYTES]; // (32U + 32U)

    crypto_sign_ed25519_seed_keypair(&pk[0], sk, seed);


    std::cout << "pk : " << hexStr5(pk, crypto_sign_PUBLICKEYBYTES) <<  std::endl;
    std::cout << "seed : " << hexStr5(seed, crypto_sign_SEEDBYTES) <<  std::endl;



    // add G or S
    unsigned char pkG[crypto_sign_PUBLICKEYBYTES + 1]; // 32U
    unsigned char seedS[crypto_sign_SEEDBYTES + 1]; // 32U
    memcpy(&pkG[1], pk, 32);
    memcpy(&seedS[1], seed, 32);
    pkG[0] = 50;
    seedS[0] = 150;

    // checksum (two byte) by CRC16-CCITT
    uint16_t crcPk = bos::util::crc16((char*)pkG, 33);
    uint16_t crcSeed = bos::util::crc16((char*)seedS, 33);

    unsigned char pkGCheckSum[crypto_sign_PUBLICKEYBYTES + 1 + 2];
    unsigned char seedCheckSum[crypto_sign_SEEDBYTES + 1 + 2];

    memcpy(&pkGCheckSum[0], pkG, 33);
    memcpy(&seedCheckSum[0], seedS, 33);

    pkGCheckSum[33] = static_cast<unsigned char>(crcPk & 0xFF);
    crcPk >>= 8;
    pkGCheckSum[34] = static_cast<unsigned char>(crcPk & 0xFF);


    seedCheckSum[33] = static_cast<unsigned char>(crcSeed & 0xFF);
    crcSeed >>= 8;
    seedCheckSum[34] = static_cast<unsigned char>(crcSeed & 0xFF);

    //convert to base32
    unsigned char pkGBase32[56];
    unsigned char seedBase32[56];

    bos::util::Base32::Encode32(pkGCheckSum,35,pkGBase32);
    bos::util::Base32::Encode32(seedCheckSum,35,seedBase32);


    std::string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"); // Most libraries use RFC4648.


    bos::util::Base32::Map32(pkGBase32, 56, (unsigned char*) ALPHABET.c_str());
    bos::util::Base32::Map32(seedBase32, 56, (unsigned char*)  ALPHABET.c_str());

    std::string ggg ((char*) pkGBase32,56);
    std::string sss ((char*) seedBase32,56);

    std::cout << "pkGBase32Alpha:  " << ggg <<  std::endl;
    std::cout << "seedBase32Alpha:  " <<  sss  <<  std::endl;


    ///////////////////////////////////////

    // base32 -> decode

    bos::util::Base32::Unmap32(pkGBase32, 56, (unsigned char*) ALPHABET.c_str());
    bos::util::Base32::Unmap32(seedBase32, 56, (unsigned char*)  ALPHABET.c_str());

    unsigned char pkGCheckSum2[crypto_sign_PUBLICKEYBYTES + 1 + 2];
    unsigned char seedCheckSum2[crypto_sign_SEEDBYTES + 1 + 2];

    bos::util::Base32::Decode32(pkGBase32,56,pkGCheckSum2);
    bos::util::Base32::Decode32(seedBase32,56,seedCheckSum2);

    // remove crc , G, S
    unsigned char pk2[crypto_sign_PUBLICKEYBYTES]; // 32U
    unsigned char seed2[crypto_sign_SEEDBYTES]; // 32U

    memcpy(&pk2[0], &pkGCheckSum2[1], 32);
    memcpy(&seed2[0], &seedCheckSum2[1], 32);

    std::cout << "pk2 : " << hexStr5(pk2, crypto_sign_PUBLICKEYBYTES) <<  std::endl;
    std::cout << "seed2 : " << hexStr5(seed2, crypto_sign_SEEDBYTES) <<  std::endl;


    unsigned char pk3[crypto_sign_PUBLICKEYBYTES]; // 32U
    unsigned char sk3[crypto_sign_SECRETKEYBYTES]; // 64U
    crypto_sign_ed25519_seed_keypair(pk3, sk3, seed2);

    #define MESSAGE (const unsigned char *) "test"
    #define MESSAGE_LEN 4

    unsigned char sig[crypto_sign_BYTES];
    crypto_sign_ed25519_detached(sig, NULL, MESSAGE, MESSAGE_LEN, seed2);
    if (crypto_sign_ed25519_verify_detached(sig, MESSAGE, MESSAGE_LEN, pk2) != 0) {
        std::cout << "verify fail!! " <<  std::endl;
    }
}


void testall(){
    //test1();
    //test2();
    //test3();
}

#endif //SIGNER_TEST_H
