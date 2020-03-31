#include <iostream>
#include "command.h"

int main(int argc, const char** argv) {

    bos::CommmandFactory command_factory;
    auto command = command_factory(argv,argc);
    command->execute();

    std::cout << "exit gracefully" << std::endl;
    return 0;
}
