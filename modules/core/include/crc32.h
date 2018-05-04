#ifndef __CRC32_H
#define __CRC32_H

/**
* @file crc32.h
*
* @brief This file includes an operation to calculate
* the crc32 from an initial seed using a buffer.
*/

#include <stdint.h>

namespace memdynedition
{

/**
 * @brief Algorithm CRC-32 result with generator type Reversed 0xEDB88320 Big Endian
 * to generate content from a seed and a buffer.
 *
 * It uses polynom x32 + x26 + x23 + x22 + x16 + x12 + x11 + x10 + x8 + x7 + x5 + x4 + x2 + x1 + 1
 *
 * @param crc starting value of crc. It is zero if not previous data computed. The result is stored here.
 * @param buf Pointer to memory buffer to compute. Data do not change.
 * @param size Size of the memory to compute.
 */
void crc32(uint32_t *crc, void *buf, uint16_t size);

}   /* namespace memdynedition */

#endif /* __CRC32_H */
