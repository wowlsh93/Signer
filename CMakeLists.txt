cmake_minimum_required(VERSION 3.15)
project(Signer)

set(CMAKE_CXX_STANDARD 17)

add_executable(Signer main.cpp signer.cpp signer.h command.cpp command.h util.h)