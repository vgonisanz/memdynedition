#include "menu.h"

#include "schifra_galois_field.hpp"
#include "schifra_galois_field_polynomial.hpp"
#include "schifra_sequential_root_generator_polynomial_creator.hpp"
#include "schifra_reed_solomon_encoder.hpp"
#include "schifra_reed_solomon_decoder.hpp"
#include "schifra_reed_solomon_block.hpp"
#include "schifra_error_processes.hpp"
#include "schifra_reed_solomon_bitio.hpp"

#define LOG_TAG "rsstruct"
#include "config.h"

using namespace memdynedition;

/**
 * This example encode data from message strings.
 * Add errors before decoding.
 * Check if is possible to recovery the original message and under
 * what circumstances.
 *
 *     k = data
 *     r = redundance
 *     m = bits per symbol
 *     n = bits per block = r + k = 2^m - 1
 *     t = error correction = (n - k) / 2
 *
 *      Then, GF(2^m) and RS [n, k, n - k + 1] for use is GF(2^8) and RS [255, 32, 224]
 */

/* Finite Field Parameters */
const std::size_t field_descriptor                =   8;    /* m = bit per symbol */
const std::size_t generator_polynomial_index      = 120;    /* normally set to 0 (first consecutive root = 1) */
const std::size_t generator_polynomial_root_count =  32;    /* root shall be equal to redundance */

/* Reed-Solomon parameters */
const std::size_t code_length = 255;                        /* 2^(bit per symbol) - 1 = 2^8 - 1 */
const std::size_t fec_length = 32;                          /* r = redundance */
const std::size_t data_length = code_length - fec_length;   /* k = n - r. Usually code encodes k = 223, so parity are 32 to get 255-symbol block */


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

bool initCheck()
{
    if (
         !schifra::make_sequential_root_generator_polynomial(field,
                                                             generator_polynomial_index,
                                                             generator_polynomial_root_count,
                                                             generator_polynomial)
       )
    {
       std::cout << "Error - Failed to create sequential root generator!" << std::endl;
       return false;
    }

    encoder = new encoder_t(field, generator_polynomial);
    decoder = new decoder_t(field, generator_polynomial_index);

    std::cout << "--- Finite Field Parameters - Field descriptor: " << field_descriptor <<
                                            ", generator index: " << generator_polynomial_index <<
                                            ", generator root count: " << generator_polynomial_root_count << std::endl;

    std::cout << "--- Reed-Solomon [n, k, n − k + 1] q-code - [" << code_length << ", " << fec_length << ", " << data_length <<
                                                                "]" << std::endl << std::endl;
}

/**
 * Encode a message string into a block. The block is cleared.
 * @param  message What message
 * @param  block   Where encode
 * @return         success
 */
bool encode(std::string &message, schifra::reed_solomon::block<code_length,fec_length> &block)
{
    block.clear();

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "* Encoding message into block: " << std::endl;
    std::cout << "--> [" << message << "]" << std::endl;

    /* Transform message into Reed-Solomon encoded codeword */
    if (!encoder->encode(message, block))
    {
       std::cout << "Error - Critical encoding failure! "
                 << "Msg: " << block.error_as_string()  << std::endl;
       return false;
    }
    return true;
}

/**
 * [editData description]
 * @param  message [description]
 * @param  block   [description]
 * @return         [description]
 */
bool editData(std::string &message, schifra::reed_solomon::block<code_length,fec_length> &block)
{
    std::cout << "* Encoding new message into block: " << std::endl;
    std::cout << "--> [" << message << "]" << std::endl;

    schifra::reed_solomon::copy(message.c_str(), block);   /* Copy only data */
    return true;
}

/**
 * Decode a block printing its message
 * @param  block Encoded message + redundant data
 * @return       success
 */
bool decode(schifra::reed_solomon::block<code_length,fec_length> &block)
{
    if (!decoder->decode(block))
    {
       std::cout << "Error - Critical decoding failure! "
                 << "Msg: " << block.error_as_string()  << std::endl;
       return false;
   }
    // else if (!schifra::is_block_equivelent(block, message)) /* No equivalence, message changed so do not check this* /

    std::string decoded;
    decoded.resize(data_length, 0x00);
    block.data_to_string(decoded);

    bool result = block.data_to_string(decoded);
    if(!result)
    {
        std::cout << "Error: String have not the same size that data_length" << std::endl;
        return false;
    }

    std::cout << "* Corrected Message: " << std::endl;
    std::cout << "--> [" << decoded << "]" << std::endl;
    return true;
}

/**
 * Encode a pointer to data into a block. The block is cleared.
 * @param  message What message
 * @param size     How much data copy
 * @param  block   Where encode
 * @return         success
 */
 /* encode/decode with size using copy(const T src_data[],
                  const std::size_t& src_length,
                  block<code_length,fec_length>& dest_block) pointer */
bool encode(const uint8_t src_data[], const uint8_t size, schifra::reed_solomon::block<code_length,fec_length> &block)
{
    block.clear();

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "* Encoding struct data " << std::endl;

    schifra::reed_solomon::copy(src_data, size, block);

    /* Transform message into Reed-Solomon encoded codeword */
    if (!encoder->encode(block))
    {
       std::cout << "Error - Critical encoding failure! "
                 << "Msg: " << block.error_as_string()  << std::endl;
       return false;
    }
    return true;
}

/**
 * [editData description]
 * @param  message [description]
 * @param  block   [description]
 * @return         [description]
 */
bool editData(const uint8_t src_data[], const uint8_t size, schifra::reed_solomon::block<code_length,fec_length> &block)
{
    std::cout << "* Encoding new data into block " << std::endl;
    schifra::reed_solomon::copy(src_data, size, block);   /* Copy only data */
    return true;
}

/**
 * [decodeAndRestore description]
 * @param  block    [description]
 * @param  dst_data [description]
 * @return          [description]
 */
bool decodeAndRestore(schifra::reed_solomon::block<code_length,fec_length> &block, uint8_t dst_data[], const uint8_t size)
{
    if (!decoder->decode(block))
    {
       std::cout << "Error - Critical decoding failure! "
                 << "Msg: " << block.error_as_string()  << std::endl;
       return false;
   }
    // else if (!schifra::is_block_equivelent(block, message)) /* No equivalence, message changed so do not check this* /

    /* Restore struct */
    schifra::reed_solomon::copy(block, dst_data, size);
    return true;
}

int main()
{
    LOGI("Executing Reed Solomon struct sample...");

    std::cout << std::endl;
    std::cout << "\tReed Solomon [" << code_length << ", " << fec_length << ", " << (code_length - fec_length) << "]" << std::endl;
    std::cout << "\tcorrecting t " << (fec_length >> 1) << " errors." << std::endl;
    std::cout << std::endl;

    initCheck();

    std::string message;
    schifra::reed_solomon::block<code_length,fec_length> block;

    /* Example I: Try to code and decode a message, change a little (4 errors < 16) and decode */
    message.reserve(code_length);
    message.assign(code_length, 0x00);
    message = "This is real message.";

    (void)encode(message, block);

    /* Edit message, this data will be copy (only data) into block */
    message = "This is FAKE message.";

    /* Add only data to old block */
    (void)editData(message, block);

    /* Check if changes are undo */
    (void)decode(block);

    /* Example II: Try to code and decode a message, change a more than allowed errors (4 errors < 16) and decode */
    message.reserve(code_length);
    message.assign(code_length, 0x00);
    message = "This is real message.";

    (void)encode(message, block);

    message = "XXXXXXXXXXX this message changed too much, no way to recovery it! :-D";
    (void)editData(message, block);

    (void)decode(block);

    /* Example III: Try it copying struct content into an string , edit a little, and decode */
    static struct
    {
        int32_t x;
        int32_t y;
        int32_t z;
    } coordinate =
    {   .x = 120,   /* x ASCII code, using printable data */
        .y = 121,
        .z = 122
    };

    std::cout << std::endl << "Origin coordinate struct has " << sizeof(coordinate) << " bytes." << std::endl;
    std::cout << "Coordinate struct contains: [" << coordinate.x << ", " << coordinate.y << ", " << coordinate.z << "]" << std::endl;

    uint8_t *buffer = (uint8_t *)&coordinate;   /* Get a pointer to the struct to store as message */

    message.reserve(code_length);
    message.assign(code_length, 0x00);
    message.assign(buffer, buffer + sizeof(coordinate));    /* Copy data to string, bad performance */

    (void)encode(message, block);

    /* Edit coordinates and convert again to message */
    coordinate.x = 88;
    coordinate.y = 89;
    coordinate.z = 90;
    message.assign(buffer, buffer + sizeof(coordinate));    /* Copy data to string, bad performance */

    std::cout << "Coordinate struct is edit with: [" << coordinate.x << ", " << coordinate.y << ", " << coordinate.z << "]" << std::endl;
    (void)editData(message, block);
    std::cout << "Decode without restoring data" << std::endl;
    (void)decode(block);    /* This decode do not restore changes */

    /* Example IV: Try it copying struct directly with a pointer to the array.
        Pointer contain XYZ data from example III! */
    (void)encode(buffer, sizeof(coordinate), block);

    /* Try to restore coordinates but decode check content with redundant data */
    coordinate.x = 120;
    coordinate.y = 121;
    coordinate.z = 122;
    std::cout << "Coordinate struct is edit with: [" << coordinate.x << ", " << coordinate.y << ", " << coordinate.z << "]" << std::endl;
    (void)editData(buffer, sizeof(coordinate), block);
    std::cout << "Decode restoring changed data" << std::endl;
    (void)decodeAndRestore(block, buffer, sizeof(coordinate));
    std::cout << "Coordinate struct contains: [" << coordinate.x << ", " << coordinate.y << ", " << coordinate.z << "]" << std::endl;

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "\t\tAll messages has been processed!" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    return 0;
}
