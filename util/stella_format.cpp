//
// Created by hama on 20. 4. 2..
//

#include "stella_format.h"

#include <iostream>
#include <iomanip>

#include "crc16.h"
#include "base32.h"

namespace bos::util {

    void encodeStellaAddress(unsigned char * in) {

        // add G
        unsigned char pkG[32 + 1];
        memcpy(&pkG[1], in, 32);
        pkG[0] = 50;

        // checksum (two byte) by CRC16-CCITT
        uint16_t crcPk = bos::util::crc16((char*)pkG, 33);

        unsigned char pkGCheckSum[32 + 1 + 2];
        memcpy(&pkGCheckSum[0], pkG, 33);

        pkGCheckSum[33] = static_cast<unsigned char>(crcPk & 0xFF);
        crcPk >>= 8;
        pkGCheckSum[34] = static_cast<unsigned char>(crcPk & 0xFF);

        //convert to base32
        unsigned char pkGBase32[56];
        unsigned char seedBase32[56];

        bos::util::Base32::Encode32(pkGCheckSum,35,pkGBase32);
        std::string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"); // Most libraries use RFC4648.

        bos::util::Base32::Map32(pkGBase32, 56, (unsigned char*) ALPHABET.c_str());

        std::string address ((char*) pkGBase32,56);

        std::cout << "Address(public key):  " << address <<  std::endl;

    }

    void decodeStellaAddress(unsigned char * in, unsigned char * out){

        // base32 -> decode
        std::string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"); // Most libraries use RFC4648.

        bos::util::Base32::Unmap32(in, 56, (unsigned char*) ALPHABET.c_str());

        unsigned char checkSum[32 + 1 + 2];
        bos::util::Base32::Decode32(in,56,checkSum);

        // remove crc , G, S
        memcpy(out, &checkSum[1], 32);

    }

    void endcodeStellaScreate(unsigned char * in){
        // add S
        unsigned char seedS[32 + 1];
        memcpy(&seedS[1], in, 32);
        seedS[0] = 150;

        // checksum (two byte) by CRC16-CCITT
        uint16_t crcSeed = bos::util::crc16((char*)seedS, 33);

        unsigned char seedCheckSum[32 + 1 + 2];

        memcpy(&seedCheckSum[0], seedS, 33);

        seedCheckSum[33] = static_cast<unsigned char>(crcSeed & 0xFF);
        crcSeed >>= 8;
        seedCheckSum[34] = static_cast<unsigned char>(crcSeed & 0xFF);

        //convert to base32
        unsigned char seedBase32[56];
        bos::util::Base32::Encode32(seedCheckSum,35,seedBase32);
        std::string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"); // Most libraries use RFC4648.

        bos::util::Base32::Map32(seedBase32, 56, (unsigned char*)  ALPHABET.c_str());

        std::string seed ((char*) seedBase32,56);
        std::cout << "Seed:  " <<  seed  <<  std::endl;

    }

    void decodeStellaScreate(unsigned char * in, unsigned char * out){

        // base32 -> decode
        std::string ALPHABET("ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"); // Most libraries use RFC4648.

        bos::util::Base32::Unmap32(in, 56, (unsigned char*) ALPHABET.c_str());

        unsigned char checkSum[32 + 1 + 2];
        bos::util::Base32::Decode32(in,56,checkSum);

        // remove crc , G, S
        memcpy(out, &checkSum[1], 32);


    }

}
