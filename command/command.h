//
// Created by hama on 20. 3. 31..
//

#include <iostream>
#include <memory>
#include <cstring>
#include <assert.h>
#include "../crypto/signer.h"
#include "../crypto/ed25519.h"

#ifndef SIGNER_COMMAND_H
#define SIGNER_COMMAND_H

namespace bos {

    class Command {
    public:
        virtual void execute() = 0;
    };


    class SignCommand : public Command {

        public:
            SignCommand(std::string opt1, std::string opt2):
                _seed(opt1),
                _data(opt2) {

                _crypto = new bos::crypto::Ed25519();

            }
            ~SignCommand(){
                delete _crypto;
            }
            virtual void execute();
        private:
            std::string _seed;
            std::string _data;

            bos::crypto::Signer * _crypto;
    };


    class VerifyCommand : public Command {
        public:
         VerifyCommand(std::string opt1, std::string opt2, std::string opt3):
             _pubkey(opt1),
             _signature(opt2),
             _data(opt3){
             _crypto = new bos::crypto::Ed25519();

         }
        ~VerifyCommand(){
            delete _crypto;
        }
         virtual void execute();
        private:
            std::string _pubkey;
            std::string _signature;
            std::string _data;
            bos::crypto::Signer * _crypto;
    };


    /***
     command: ./signer keypair
     result : public / private key / seed
    ***/
    class KeyPairCommand : public Command {
        public:
         KeyPairCommand() {
             _crypto = new bos::crypto::Ed25519();
         }

        ~KeyPairCommand(){
            delete _crypto;
        }

         virtual void execute();

        bos::crypto::Signer * _crypto;
    };

    class CommmandFactory {
        public:
         Command* operator()(const char** argv, int argc) {

             if(strcmp(argv[1],"sign") == 0){
                 assert(argc == 4);
                 return new SignCommand(argv[2], argv[3]);
             }
             else if(strcmp(argv[1],"verify") == 0){
                 assert(argc == 5);
                 return new VerifyCommand(argv[2], argv[3], argv[4]);
             }
             else if(strcmp(argv[1] , "keypair") == 0){
                 return new KeyPairCommand();
             }
             else{
                 std::cout << "there is no command => " << argv[1] <<  std::endl;
                 std::string help_msesage  = R"( usage: ./Signer [options] required_input required_input)";
                 std::cout << help_msesage << std::endl;
             }
         }
    };
}

#endif //SIGNER_COMMAND_H
