//
// Created by hama on 20. 3. 31..
//

#ifndef SIGNER_SIGNER_H
#define SIGNER_SIGNER_H

#include <iostream>

namespace bos {
    class Signer {

    public:
        void say_hello(const std::string &cmd) const {
            std::cout << cmd << std::endl;
        }
    };
}




#endif //SIGNER_SIGNER_H
