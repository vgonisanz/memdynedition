#include "securizerRS.h"

#define LOG_TAG "securizerRS"
#include "config.h"

#include "schifra_galois_field.hpp"
#include "schifra_galois_field_polynomial.hpp"
#include "schifra_sequential_root_generator_polynomial_creator.hpp"
#include "schifra_reed_solomon_encoder.hpp"
#include "schifra_reed_solomon_decoder.hpp"
#include "schifra_reed_solomon_block.hpp"
#include "schifra_error_processes.hpp"
#include "schifra_reed_solomon_bitio.hpp"

#include <string.h>

namespace memdynedition
{
 /* Instantiate Finite Field and Generator Polynomials */
 const schifra::galois::field field(field_descriptor,
                                    schifra::galois::primitive_polynomial_size06,
                                    schifra::galois::primitive_polynomial06);

 schifra::galois::field_polynomial generator_polynomial(field);

 /* Instantiate Encoder and Decoder (Codec) */
 typedef schifra::reed_solomon::encoder<code_length, fec_length, data_length> encoder_t;
 typedef schifra::reed_solomon::decoder<code_length, fec_length, data_length> decoder_t;

 const encoder_t* encoder;
 const decoder_t* decoder;

SecurizerRS::SecurizerRS()
{
    if (
         !schifra::make_sequential_root_generator_polynomial(field,
                                                             generator_polynomial_index,
                                                             generator_polynomial_root_count,
                                                             generator_polynomial)
       )
    {
       throw std::invalid_argument("Error - Failed to create sequential root generator");
    }

    _block = new schifra::reed_solomon::block<code_length,fec_length, data_length>;
    encoder = new encoder_t(field, generator_polynomial);
    decoder = new decoder_t(field, generator_polynomial_index);

    LOGI("Securizer create with FFP[%d, %d, %d] and RS[%d, %d, %d]", field_descriptor, generator_polynomial_index, generator_polynomial_root_count,
                                                                        code_length, fec_length, data_length);
};

SecurizerRS::~SecurizerRS()
{
    delete _block;
    delete encoder;
    delete decoder;
}

void SecurizerRS::setData(void *data, uint32_t size)
{
    _data = data;
    _size = size;
}

bool SecurizerRS::check()
{
    if(!memcmp(_data, _block, _size))
        return true;
    return false;
}

bool SecurizerRS::secureBlock()
{
    _block->clear();
    schifra::reed_solomon::copy((uint8_t*)_data, _size, *_block);

    /* Transform message into Reed-Solomon encoded codeword */
    if (!encoder->encode(*_block))
    {
        LOGE("Critical encoding failure: %s", _block->error_as_string());
        return false;
    }
    return true;
}

bool SecurizerRS::editBlock()
{
    LOGD("Encoding new data into block ");
    schifra::reed_solomon::copy((uint8_t*)_data, _size, *_block);   /* Copy only data */
    return true;
}

bool SecurizerRS::restoreBlock()
{
    if (!decoder->decode(*_block))
    {
        LOGE("Critical decoding failure: %s", _block->error_as_string());
        return false;
    }
    // else if (!schifra::is_block_equivelent(_block, message)) /* No equivalence, message changed so do not check this* /

    /* Restore struct */
    schifra::reed_solomon::copy(*_block, (uint8_t*)_data, _size);
    return true;
}

}   /* namespace memdynedition */
