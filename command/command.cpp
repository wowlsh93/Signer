//
// Created by hama on 20. 3. 31..
//

#include "command.h"

void hex2bin2(const std::string& hex, uint8_t* data) {

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        std::string byteString = hex.substr(i, 2);
        (*data) = (char)strtol(byteString.c_str(), NULL, 16);
        data += 1;
    }
}

namespace bos {

    /***
    command: ./signer sign $SEED $DATA
    example: ./signer sign SDSBQZ7BD2XZZPEUFWS7WQGB7BFUI7TCH474S6C5OQTNBICD7AZ2FDN6 "I love BOSAGORA"
    result: CED308BE013B95030752DD223F960DEC02735201F4E238274959ABA09C36D3542E01A0CBD2A342E349DD934A8D51564A08A8ADF9D92487E4D3362D83E9C6890D49206C6F766520424F5341474F5241
    ***/

    // sign 1fa5b38bc9ddfea85901e00a66a1b6feb941dbdcfbe6681a492f5a9f070e0994 hello

    void SignCommand::execute() {
            std::cout << "SignCommand execute!!" << std::endl;
            unsigned char seed[crypto_sign_SEEDBYTES];
            hex2bin2(_seed, seed);
            _crypto->sign((unsigned char *) _data.c_str(),
                          (unsigned int) _data.length(),
                          seed);
    }


    /***
    command: ./signer verify $PUBLIC_KEY $SIGNATURE $DATA
    example: ./signer verify GASG2JFZI4XKNQFF5FH2QGBXCROVJBNE43QNJWMXQQIDZZPYP3UVGTW6 CED308BE013B95030752DD223F960DEC02735201F4E238274959ABA09C36D3542E01A0CBD2A342E349DD934A8D51564A08A8ADF9D92487E4D3362D83E9C6890D49206C6F766520424F5341474F5241 hello
    result : bool
     */

    // verify 4bce283c01b2103da1c451375fa472ddfc3b710fbc31dc6887a5e6fedd89cedf  84756611dfc2e8b0eab7da00f18c6edf5941e8d62ff182656db1889ad1d249ae58980b6dd52a83d781f3dffea431add55ff09abdb08b22e70309aab865a44602 hello

    void VerifyCommand::execute() {
        std::cout << "VerifyCommand execute!!" << std::endl;

        unsigned char pk[crypto_sign_PUBLICKEYBYTES]; // 32U
        unsigned char sig[crypto_sign_BYTES]; // 64U

        hex2bin2(_pubkey, pk);
        hex2bin2(_signature, sig);

        _crypto->verify(
                sig,
                pk,
                (unsigned char *) _data.c_str(),
                (unsigned int)  _data.length()
        );
    }

    void KeyPairCommand::execute() {
        std::cout << "KeyPairCommand execute!!" << std::endl;
        _crypto->keypair();
    }

}