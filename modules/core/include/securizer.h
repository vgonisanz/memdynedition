#ifndef __SECURIZER_H
#define __SECURIZER_H

#include <stdint.h>
#include <iostream>
namespace memdynedition
{

class Securizer
{
public:
    Securizer();
    ~Securizer() = default;

    /*
     * \brief Update a value if is a protected memory.
     * Auto update CRC32 with "critical section" to avoid unwanted
     * edition during the process. It could fail if in that
     * moment the CPU go to the hacker process, and edit it before
     * calculate CRC32. You cannot control that assignation in non
     * real time OS.
     */
    template <typename T>
    bool assign(T* variable, T value)
    {
        /* Check if is my protected data using byte address */
        if((uint8_t *)variable < _data)
            return false;
        if((uint8_t *)variable > ((uint8_t *)_data + _size))
            return false;

        /* Critical section START: If value change before process CRC32, then the modification is not detected */
        *variable = value;
        updateCRC32();

        /*
         * Wait or observer to monitor this value after a while? It is not detected here,
         * but it is detected the next time. It depends external process that block the value
         */
        bool result = (*variable == value);

        /* Critic section END */
        return result;
    }

    /*
     * Set up pointer to data struct to be secured.
     */
    void setData(void *data, uint32_t size);

    /*
     * /brief Process the secured struct to calculate its CRC32.
     * If you assign a value manually and want to update the CRC32,
     * you can do it manually with this method. No need to be called
     * if you are using assign function to do it.
     * /return Returns the new CRC32 calculated.
     */
    uint32_t updateCRC32();

    /*
     * /brief Check if CRC32 has changed since last update
     * This method detect if something changed in the struct
     * since the last time it was update. Call updateCRC32
     * after a legal edition to be sure that is propertly updated.
     * /return true if it is not altered!
     */
    bool check();

    uint32_t getCRC32() { return _crc32; }

private:
    void* _data;        /* Pointer to the struct */
    uint32_t _size;     /* Size of the struct, it cannot be calculated using sizeof(void *) */

    uint32_t _crc32;    /* CRC32 calculated with update using _data and _size */

    /*
     * /brief Process internal data to calculate crc32
     */
    uint32_t process();
};

}   /* namespace memdynedition */

#endif /* __SECURIZER_H */
