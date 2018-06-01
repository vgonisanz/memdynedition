#ifndef __SECURIZERRS_H
#define __SECURIZERRS_H

#include <stdint.h>
#include <iostream>

/* Forward declaration block */
namespace schifra
{
    namespace reed_solomon
    {
        template <std::size_t code_length, std::size_t fec_length, std::size_t data_length>
        struct block;
    }
}

/**
 * Generator polynomial related with redundance.
 * k = data
 * r = redundance
 * m = bits per symbol
 * n = bits per block = r + k = 2^m - 1
 * t = error correction = (n - k) / 2
 *
 * Assumptions:
 * - Only data will be corrupted, no redundancy.
 * - To get full recovery n = 3 * k --> r = 2 * k.
 * - n = 255 so r in this case shall be 170.
 *
 * Then, GF(2^m) and RS [n, k, n - k + 1] for use is GF(2^8) and RS [255, 85, 171]
 */

/* Finite Field Parameters - index + root count shall be < field size */
const std::size_t field_descriptor                =   8;    /* m = bit per symbol */
const std::size_t generator_polynomial_index      =   0;    /* normally set to 0 (first consecutive root = 1) */
const std::size_t generator_polynomial_root_count = 170;    /* root shall be equal to redundance */

/* Reed-Solomon parameters */
const std::size_t code_length = 255;                        /* n = 2^m - 1 = 2^8 - 1 bits per block = field size */
const std::size_t fec_length =  170;                        /* r = redundance */
const std::size_t data_length = code_length - fec_length;   /* k = n - r */

namespace memdynedition
{

class SecurizerRS
{
public:
    SecurizerRS();
    ~SecurizerRS();

    /*
     * Set up pointer to data struct to be secured.
     */
    void setData(void *data, uint32_t size);

    /*
     * /brief Check if data changed
     * /return true if it is not altered!
     */
    bool check();

    bool secureBlock();
    bool editBlock();
    bool restoreBlock();    /* Fix only required by user */

private:
    void* _data;        /* Pointer to the struct */
    uint32_t _size;     /* Size of the struct, it cannot be calculated using sizeof(void *) */
    schifra::reed_solomon::block<code_length,fec_length, data_length>* _block;
};

}   /* namespace memdynedition */

#endif /* __SECURIZERRS_H */
