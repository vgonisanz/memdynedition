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
    update();   /* Make first copy */
}

void SecurizerAntiCP::update()
{
    std::memcpy(_anticopy, _data, _size);
}

bool SecurizerAntiCP::check()
{
    return !(std::memcmp(_data, _anticopy, _size));
}

void SecurizerAntiCP::restore()
{
    std::memcpy(_data, _anticopy, _size);
}

void SecurizerAntiCP::reverse()
{
    if(!_anticopy)
        return;

    /* for */
}

}   /* namespace memdynedition */
