#ifndef __SECURIZERANTICP_H
#define __SECURIZERANTICP_H

#include <stdint.h>
#include <iostream>

namespace memdynedition
{

class SecurizerAntiCP
{
public:
    SecurizerAntiCP();
    ~SecurizerAntiCP();

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

    void* _anticopy;         /* Pointer to the copy data */

    void reverse();     /* Reverse data of anticopy memory region */

};

}   /* namespace memdynedition */

#endif /* __SECURIZERANTICP_H */
