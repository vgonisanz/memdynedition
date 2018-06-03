#include "securizerCP.h"

#define LOG_TAG "securizerCP"
#include "config.h"

#include <cstring>

namespace memdynedition
{

SecurizerCP::SecurizerCP():
_data(nullptr),
_size(0),
_copy(nullptr)
{

};

SecurizerCP::~SecurizerCP()
{
    if(_copy)
        free(_copy);
}

void SecurizerCP::setData(void *data, uint32_t size)
{
    _data = data;
    _size = size;
    _copy = malloc(size);
    update();   /* Make first copy */
}

void SecurizerCP::update()
{
    std::memcpy(_copy, _data, _size);
}

bool SecurizerCP::check()
{
    return !(std::memcmp(_data, _copy, _size));
}

void SecurizerCP::restore()
{
    std::memcpy(_data, _copy, _size);
}

}   /* namespace memdynedition */
