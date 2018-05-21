#include "securizer.h"
#include "crc32.h"
#include "bitopts.h"

#define LOG_TAG "securizer"
#include "config.h"

namespace memdynedition
{

Securizer::Securizer():
_crc32(0)
{
};

void Securizer::setData(void *data, uint32_t size)
{
    _data = data;
    _size = size;
}

uint32_t Securizer::process()
{
    uint8_t *buffer = (uint8_t *)_data;
    uint32_t result = 0;    /* seed null */

    crc32(&result, buffer, _size);
    return swap_uint32(result);
}

uint32_t Securizer::updateCRC32()
{
    _crc32 = process();
    return _crc32;
}

bool Securizer::check()
{
    return (process() == _crc32);
}

}   /* namespace memdynedition */
