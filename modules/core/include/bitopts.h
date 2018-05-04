#ifndef __BITOPTS_H
#define __BITOPTS_H

#include <stdint.h>

namespace memdynedition
{

/**
 * @brief reverse Flip bytes for a 32 bit double word.
 * @param  DW to be flipped
 * @return Flipped DW
 */
static inline uint32_t swap_uint32(uint32_t data)
{
    return  ((data >> 24)  & 0x000000FF) |
            ((data >>  8)  & 0x0000FF00) |
            ((data <<  8)  & 0x00FF0000) |
            ((data << 24)  & 0xFF000000);
}

/**
 * @brief Read a 32 bit word from a buffer flipping data
 * @param  DW to be flipped
 * @return Flipped DW
 */
static inline uint32_t read32_from_buffer_flipped(const uint8_t *buffer)
{
    return  ((*(buffer + 0)      )  & 0x000000FF) |
            ((*(buffer + 1) <<  8)  & 0x0000FF00) |
            ((*(buffer + 2) << 16)  & 0x00FF0000) |
            ((*(buffer + 3) << 24)  & 0xFF000000);
}

/**
 * @brief Read a 32 bit word from a buffer in raw
 * @param  buffer big endian
 * @return DW
 */
static inline uint32_t read32_from_buffer(const uint8_t *buffer)
{
    return  ((*(buffer + 0)      )  & 0xFF000000) |
            ((*(buffer + 1) <<  8)  & 0x00FF0000) |
            ((*(buffer + 2) << 16)  & 0x0000FF00) |
            ((*(buffer + 3) << 24)  & 0x000000FF);
}

}   /* namespace memdynedition */

#endif /* __BITOPTS_H */
