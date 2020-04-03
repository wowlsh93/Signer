#include <iostream>
#include "command/command.h"
#include "test.h"
// mkdir build
// cd build
// cmake ..
// cmake --build .
// ./Signer



int main(int argc, const char** argv) {

//    testall();


    bos::CommmandFactory command_factory;
    auto command = command_factory(argv,argc);
    command->execute();
    return 0;
}
