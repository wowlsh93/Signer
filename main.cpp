#include <iostream>
#include "command/command.h"


int main(int argc, const char** argv) {

    bos::CommmandFactory command_factory;
    auto command = command_factory(argv,argc);
    command->execute();
    return 0;
}
