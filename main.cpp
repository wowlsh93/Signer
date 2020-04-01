#include <iostream>
#include "command/command.h"
#include <iostream>
#include <iomanip>
// mkdir build
// cd build
// cmake ..
// cmake --build .
// ./Signer

std::string hexStr2(const unsigned char *data, int len)
{
    std::stringstream ss;
    ss << std::hex;

    for( int i(0) ; i < len; ++i )
        ss << std::setw(2) << std::setfill('0') << (int)data[i];

    return ss.str();
}

void hex2bin3(const std::string& hex, uint8_t* data) {

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        (*data) = (char)strtol(byteString.c_str(), NULL, 16);
        data += 1;
    }
}

int main(int argc, const char** argv) {

    if (sodium_init() == -1) {
        std::cout << "sodium init fail" << std::endl;
        return 1;
    }

    unsigned char seed[crypto_sign_SEEDBYTES]; // (32U)

    randombytes_buf(seed,sizeof seed);

    unsigned char pk[crypto_sign_PUBLICKEYBYTES]; // 32U
    unsigned char sk[crypto_sign_SECRETKEYBYTES]; // (32U + 32U)

    crypto_sign_ed25519_seed_keypair(pk, sk, seed);


    std::cout << "pk : " << hexStr2(pk, crypto_sign_PUBLICKEYBYTES) <<  std::endl;
    std::cout << "sk : " << hexStr2(sk, crypto_sign_SECRETKEYBYTES) <<  std::endl;
    std::cout << "seed : " << hexStr2(seed, crypto_sign_SEEDBYTES) <<  std::endl;


    #define MESSAGE (const unsigned char *) "test"
    #define MESSAGE_LEN 4

    unsigned char sig[crypto_sign_BYTES];
    crypto_sign_ed25519_detached(sig, NULL, MESSAGE, MESSAGE_LEN, seed);

    std::cout << "signature : " << hexStr2(sig, crypto_sign_BYTES) <<  std::endl;

    if (crypto_sign_ed25519_verify_detached(sig, MESSAGE, MESSAGE_LEN, pk) != 0) {
        std::cout << "verify fail!! " <<  std::endl;
    }

    return 1;


    bos::CommmandFactory command_factory;
    auto command = command_factory(argv,argc);
    command->execute();

    std::cout << "exit gracefully" << std::endl;
    return 0;
}
