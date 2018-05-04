#ifndef __CORE_H
#define __CORE_H

#include <stdint.h>

namespace memdynedition
{

/*
 * CRC32 notes:
 *  - Notation: DW = Double word; BX = n-Byte
 *  - Valid for: ISO 3309, ANSI X3.66, FIPS PUB 71, FED-STD-1003, ITU-T V.42, Ethernet, SATA, MPEG-2, Gzip, PKZIP, POSIX cksum, PNG, ZMODEM.
 *  - Check results online in:
 *      https://www.scadacore.com/tools/programming-calculators/online-checksum-calculator/
 */

/*
 * Algorithm CRC-32 result with generator type Reversed 0xEDB88320 Big Endian.

 * Input: 0x0123CDEF
 * Output: 0x2A1612ED
 */
void testCRC32();

/*
 * Algorithm CRC-32 result with generator type Reversed 0xEDB88320 Big Endian.
 * Bucle to read DW to DW. You can use as example to made other operation instead read.
 * Input: 0x0123CDEF
 * Output: 0x2A1612ED
 */
void testCRC32PerDW();

}   /* namespace memdynedition */

#endif /* __CORE_H */
