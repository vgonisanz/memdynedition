#include "securizerCRC32.h"
#include "crc32.h"
#include "bitopts.h"

#define LOG_TAG "securizerCRC32"
#include "config.h"

namespace memdynedition
{

SecurizerCRC32::SecurizerCRC32():
_crc32(0)
{
};

void SecurizerCRC32::setData(void *data, uint32_t size)
{
    _data = data;
    _size = size;
}

uint32_t SecurizerCRC32::process()
{
    uint8_t *buffer = (uint8_t *)_data;
    uint32_t result = 0;    /* seed null */

    crc32(&result, buffer, _size);
    return swap_uint32(result);
}

uint32_t SecurizerCRC32::updateCRC32()
{
    _crc32 = process();
    return _crc32;
}

bool SecurizerCRC32::check()
{
    return (process() == _crc32);
}

}   /* namespace memdynedition */
