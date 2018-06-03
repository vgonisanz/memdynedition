#ifndef __SECURIZERCP_H
#define __SECURIZERCP_H

#include <stdint.h>
#include <iostream>

namespace memdynedition
{

class SecurizerCP
{
public:
    SecurizerCP();
    ~SecurizerCP();

    /*
     * Set up pointer to data struct to be secured.
     */
    void setData(void *data, uint32_t size);

    /*
     * /brief Update the copy with new data
     */
    void update();

    /*
     * /brief Check if data is equal to copy
     * /return true if it is not altered!
     */
    bool check();

    /*
     * /brief Restore the original data with the copy if user detect corruption
     */
    void restore();

private:
    void* _data;        /* Pointer to the original struct */
    uint32_t _size;     /* Size of the struct, it cannot be calculated using sizeof(void *) */

    void* _copy;         /* Pointer to the copy data */

};

}   /* namespace memdynedition */

#endif /* __SECURIZERCP_H */
