//
// Created by hama on 20. 3. 31..
//

#include <iostream>
#include <memory>
#include <cstring>
#include <assert.h>
#include "util.h"

#ifndef SIGNER_COMMAND_H
#define SIGNER_COMMAND_H

namespace bos {

    class Command {
    public:
        virtual void execute() = 0;
    };

    /***
    command: ./signer sign $SEED $DATA
    example: ./signer sign SDSBQZ7BD2XZZPEUFWS7WQGB7BFUI7TCH474S6C5OQTNBICD7AZ2FDN6 "I love BOSAGORA"
    result: CED308BE013B95030752DD223F960DEC02735201F4E238274959ABA09C36D3542E01A0CBD2A342E349DD934A8D51564A08A8ADF9D92487E4D3362D83E9C6890D49206C6F766520424F5341474F5241
    ***/

    class SignCommand : public Command {
        public:
            SignCommand(std::string opt1, std::string opt2):
                _seed(opt1),
                _data(opt2) {
            }
            virtual void execute() {
                std::cout << "SignCommand execute!!" << std::endl;
            }
        private:
            std::string _seed;
            std::string _data;
    };

    /***
    command: ./signer verify $PUBLIC_KEY $SIGNATURE
    example: ./signer verify GASG2JFZI4XKNQFF5FH2QGBXCROVJBNE43QNJWMXQQIDZZPYP3UVGTW6 CED308BE013B95030752DD223F960DEC02735201F4E238274959ABA09C36D3542E01A0CBD2A342E349DD934A8D51564A08A8ADF9D92487E4D3362D83E9C6890D49206C6F766520424F5341474F5241
    result : bool
     */


    class VerifyCommand : public Command {
        public:
         VerifyCommand(std::string opt1, std::string opt2):
             _pubkey(opt1),
             _signature(opt2) {
         }
         virtual void execute() {
             std::cout << "VerifyCommand execute!!" << std::endl;
         }
        private:
            std::string _pubkey;
            std::string _signature;
    };


    /***
     command: ./signer keypair
     result : public / private key / seed
    ***/
    class KeyPairCommand : public Command {
        public:
         KeyPairCommand() {}

         virtual void execute() {
             std::cout << "KeyPairCommand execute!!" << std::endl;
         }

    };

    class CommmandFactory {
        public:
         Command* operator()(const char** argv, int argc) {
             if(strcmp(argv[1],"sign") == 0){
                 assert(argc == 4);
                 return new SignCommand(argv[2], argv[3]);
             }
             else if(argv[1] == "verify"){
                 assert(argc == 4);
                 return new VerifyCommand(argv[2], argv[3]);
             }
             else if(argv[1] == "keypair"){
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
