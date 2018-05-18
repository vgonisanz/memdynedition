#ifndef __SECURIZER_H
#define __SECURIZER_H

#include <stdint.h>

namespace memdynedition
{

class Securizer
{
public:
    Securizer();
    ~Securizer() = default;

    void setData(void *data);
    uint32_t update();

    /*
     * /brief Check if CRC32 has changed since last update
     * /return true if it is not altered!
     */
    bool check();

private:
    void* _data;
    uint32_t _crc32;

    /* Process internal data to calculate crc32 */
    uint32_t process();
};

}   /* namespace memdynedition */

#endif /* __SECURIZER_H */
