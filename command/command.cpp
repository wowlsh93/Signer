//
// Created by hama on 20. 3. 31..
//

#include "command.h"

namespace bos {

    /***
    command: ./signer sign $SEED $DATA
    example: ./signer sign S35UB6VYDIFMQP6HZOINO4BANS5Y6XP5NWIQSA2THMU6JDZCH3IXF2KB hello
    result: 0fb9aba7f5862d055c07ef0b8480f1aeced669fe76858db1ddd6359a63f8976b41788b745d7ce1e967dd8f943a1375eba66213295131dd0e55fb523866e71d0d
    ***/

    void SignCommand::execute() {


            _crypto->sign((unsigned char *) _data.c_str(),
                          (unsigned int) _data.length(),
                          (unsigned char *)_seed.c_str());
    }


    /***
    command: ./signer verify $PUBLIC_KEY $SIGNATURE $DATA
    example: ./signer verify GLCY5BDFM6537PURKTFT7HSKZSNY2P2C5W6JIOZLPHJ7MR4DEHAD2NYW 0fb9aba7f5862d055c07ef0b8480f1aeced669fe76858db1ddd6359a63f8976b41788b745d7ce1e967dd8f943a1375eba66213295131dd0e55fb523866e71d0d hello
    result : bool
     */

    void VerifyCommand::execute() {

        _crypto->verify(
                _signature,
                (unsigned char *)_pubkey.c_str(),
                (unsigned char *) _data.c_str(),
                (unsigned int)  _data.length()
        );
    }


    // Address(public key):  GLCY5BDFM6537PURKTFT7HSKZSNY2P2C5W6JIOZLPHJ7MR4DEHAD2NYW
    // Seed:  S35UB6VYDIFMQP6HZOINO4BANS5Y6XP5NWIQSA2THMU6JDZCH3IXF2KB
    void KeyPairCommand::execute() {
        _crypto->keypair();
    }

}