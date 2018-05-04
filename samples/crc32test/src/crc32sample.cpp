#include "crc32sample.h"

#define LOG_TAG "crc32sample"
#include "config.h"

#include "bitopts.h"
#include "crc32.h"

namespace memdynedition
{

void testCRC32()
{
    const uint8_t DW_SIZE = 4;
    const uint32_t EXPECTED = 0xAED1C728;
    const uint8_t bufferInput[] = {
        0x01,   /* DW0: B0 */
        0x23,   /* DW0: B1 */
        0x45,   /* DW0: B2 */
        0x67,   /* DW0: B3 */
        0x89,   /* DW1: B0 */
        0xAB,   /* DW1: B1 */
        0xCD,   /* DW2: B2 */
        0xEF,   /* DW3: B3 */
    };

    uint8_t *buffer = (uint8_t *)bufferInput;
    uint32_t offset = 0;
    uint32_t result = 0;    /* seed null */

    crc32(&result, buffer, sizeof(bufferInput));
    result = swap_uint32(result);
    LOGI("testCRC32      - The result is: 0x%08X vs 0x%08X", result, EXPECTED);
}

void testCRC32PerDW()
{
    const uint8_t DW_SIZE = 4;
    const uint32_t EXPECTED = 0xAED1C728;
    const uint8_t bufferInput[] = {
        0x01,   /* DW0: B0 */
        0x23,   /* DW0: B1 */
        0x45,   /* DW0: B2 */
        0x67,   /* DW0: B3 */
        0x89,   /* DW1: B0 */
        0xAB,   /* DW1: B1 */
        0xCD,   /* DW2: B2 */
        0xEF,   /* DW3: B3 */
    };

    const uint8_t *buffer = bufferInput;
    uint32_t offset = 0;
    uint32_t result = 0;    /* seed null */

    for(offset = 0; offset < sizeof(bufferInput); offset += DW_SIZE)
    {
        /* Read buffer 32 bits */
        uint32_t value = read32_from_buffer_flipped(buffer);    /* Make you own operation here if required */
        crc32(&result, &value, DW_SIZE);
        buffer = buffer + DW_SIZE;
    }
    result = swap_uint32(result);
    LOGI("testCRC32PerDW - The result is: 0x%08X vs 0x%08X", result, EXPECTED);
}

}   /* namespace memdynedition */
