//
// Created by hama on 20. 3. 31..
//

#ifndef SIGNER_UTIL_H
#define SIGNER_UTIL_H

#include <iostream>
#include <iomanip>

namespace bos::util {


    std::string hexStr(const unsigned char *data, int len)
    {
        std::stringstream ss;
        ss << std::hex;

        for( int i(0) ; i < len; ++i )
            ss << std::setw(2) << std::setfill('0') << (int)data[i];

        return ss.str();
    }


    void hex2bin(const std::string& hex, uint8_t* data) {

        for (unsigned int i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            (*data) = (char)strtol(byteString.c_str(), NULL, 16);
            data += 1;
        }
    }

    bool compareByte(uint8_t* data1, uint8_t* data2, int size) {

        for (int i = 0; i < size; i++) {
            if (data1[i] != data2[i]) {
                return false;
            }
        }

        return true;
    }

}
#endif //SIGNER_UTIL_H