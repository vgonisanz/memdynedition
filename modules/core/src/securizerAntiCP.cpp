#include "securizerAntiCP.h"

#define LOG_TAG "securizerAntiCP"
#include "config.h"

#include <cstring>

namespace memdynedition
{

SecurizerAntiCP::SecurizerAntiCP():
_data(nullptr),
_size(0),
_anticopy(nullptr)
{

};

SecurizerAntiCP::~SecurizerAntiCP()
{
    if(_anticopy)
        free(_anticopy);
}

void SecurizerAntiCP::setData(void *data, uint32_t size)
{
    _data = data;
    _size = size;
    _anticopy = malloc(size);
    update();                   /* Make first copy */
}

void SecurizerAntiCP::update()
{
    std::memcpy(_anticopy, _data, _size);
    reverse();                  /* !copy */
}

bool SecurizerAntiCP::check()
{
    reverse();  /* copy to compare */
    bool result = std::memcmp(_data, _anticopy, _size); /* Better !cmp, but this works */
    reverse();  /* !copy */
    return !(result);
}

void SecurizerAntiCP::restore()
{
    std::memcpy(_data, _anticopy, _size);
}

void SecurizerAntiCP::reverse()
{
    size_t len = _size;
    uint8_t *d = (uint8_t *)_anticopy;
    const uint8_t *s = (const uint8_t *)_anticopy;
    while (len--)
        *d++= *s++;
}

}   /* namespace memdynedition */
