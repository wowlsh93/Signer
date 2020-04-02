//
// Created by hama on 20. 4. 2..
//

#ifndef SIGNER_CRC16_H
#define SIGNER_CRC16_H

#include <cstdint>
namespace bos::util {

    uint16_t crc16(const char *buf, int len);
}
#endif //SIGNER_CRC16_H
