#include "menu.h"

#include "schifra_galois_field.hpp"
#include "schifra_galois_field_polynomial.hpp"
#include "schifra_sequential_root_generator_polynomial_creator.hpp"
#include "schifra_reed_solomon_encoder.hpp"
#include "schifra_reed_solomon_decoder.hpp"
#include "schifra_reed_solomon_block.hpp"
#include "schifra_error_processes.hpp"

#define LOG_TAG "rsusage"
#include "config.h"

using namespace memdynedition;

/**
 * This example encode data with messages and decode it.
 * Errors are added to check if works or not and in what conditions.
 *
 * Conceptual resources:
 *      * Reed–Solomon error correction:    https://en.wikipedia.org/wiki/Reed%E2%80%93Solomon_error_correction
 *      * Galois Field:                     https://en.wikipedia.org/wiki/Finite_field_arithmetic
 *      * Explanation:                      https://www.cs.cmu.edu/~guyb/realworld/reedsolomon/reed_solomon_codes.html
 *
 *     k = data
 *     r = redundance
 *     m = bits per symbol
 *     n = bits per block = r + k = 2^m - 1
 *     t = error correction = (n - k) / 2
 *
 *     Then, GF(2^m) and RS [n, k, n - k + 1] for use is GF(2^8) and RS [255, 32, 224]
 */

/* Finite Field Parameters */
const std::size_t field_descriptor                =   8;    /* m = bit per symbol */
const std::size_t generator_polynomial_index      = 120;    /* normally set to 0 (first consecutive root = 1) */
const std::size_t generator_polynomial_root_count =  32;    /* root shall be equal to redundance */

/* Reed-Solomon parameters */
const std::size_t code_length = 255;                        /* n = 2^(bit per symbol) - 1 = 2^8 - 1 */
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

    std::cout << "--- Reed-Solomon [n, k, n − k + 1] q-code - [" << code_length << ", " << data_length << ", " << fec_length <<
                                                                "]" << std::endl << std::endl;
    return true;
}

bool encode(std::string &message, schifra::reed_solomon::block<code_length,fec_length> &block)
{
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "* Encoding message into block with size: " << message.length() << std::endl;
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

bool decode(schifra::reed_solomon::block<code_length,fec_length> &block, std::string &message)
{
    if (!decoder->decode(block))
    {
       std::cout << "Error - Critical decoding failure! "
                 << "Msg: " << block.error_as_string()  << std::endl;
       return false;
    }
    else if (!schifra::is_block_equivelent(block, message))
    {
       std::cout << "Error - Error correction failed!" << std::endl;
       return false;
    }
    std::string decoded;
    decoded.resize(data_length, 0x00);

    bool result = block.data_to_string(decoded);
    if(!result)
    {
        std::cout << "Error: String have not the same size that data_length" << std::endl;
        return false;
    }

    std::cout << "* Decoded Message: " << std::endl;
    std::cout << "--> [" << decoded << "]" << std::endl;
    return true;
}

void corrupt(schifra::reed_solomon::block<code_length,fec_length> &block, const std::size_t& error_count, const std::size_t& start_position, const std::size_t& scale)
{
    /* Add n errors from start_position each scale factor */
    schifra::corrupt_message_all_errors(block, error_count, start_position, scale);

    std::cout << "* Corrupted Codeword: " << std::endl;
    std::cout << "--> [" << block << "]" << std::endl;
}

bool process(std::string message, const std::size_t& error_count, const std::size_t& start_position, const std::size_t& scale)
{
    bool result = false;

    /* Pad message with nulls up until the code-word length */
    message.resize(code_length, 0x00);

    /* Instantiate RS Block For Codec */
    schifra::reed_solomon::block<code_length,fec_length> block;

    /* Transform message into Reed-Solomon encoded codeword */
    result = encode(message, block);
    if(!result)
    {
        std::cout << "Error encoding!" << std::endl;
        return false;
    }

    corrupt(block, error_count, start_position, scale);

    result = decode(block, message);
    if(!result)
    {
        std::cout << "Error decoding!" << std::endl;
        return false;
    }

    std::cout << "Encoder parameters [" << encoder_t::trait::code_length << ","
                                        << encoder_t::trait::data_length << ","
                                        << encoder_t::trait::fec_length  << "] ";

    std::cout << " and decoder Parameters [" << decoder_t::trait::code_length << ","
                                        << decoder_t::trait::data_length << ","
                                        << decoder_t::trait::fec_length  << "]" << std::endl << std::endl;
    return true;
}

int main()
{
    LOGI("Executing Reed Solomon usage sample...");

    std::cout << std::endl;
    std::cout << "\tGalois Field GF(p^n) is ring of integers modulo p, where p is a prime number." << std::endl;
    std::cout << "\t\tWe use 2 as prime number, using: " << std::endl;
    std::cout << "\t\tPolynomial: x^8 + x^7 + x^2 + x^1 + 1 | field descriptor: " << field_descriptor << std::endl;
    std::cout << "\t\tBinary: {110000111}" << std::endl;
    std::cout << "\t\tHexadecimal: {187}" << std::endl;
    std::cout << std::endl;
    std::cout << "\tReed Solomon require a proper configuration, the values are: " << std::endl;
    std::cout << "\t\tBlock length\t\tn = " << code_length << std::endl;
    std::cout << "\t\tMessage length\t\tk (dimension) = " << code_length - fec_length << std::endl;
    std::cout << "\t\tHamming distance\tn − k + 1 (minimum)" << std::endl;
    std::cout << "\t\tAlphabet size\t\tq = pm ≥ n  (p prime)" << std::endl;
    std::cout << "\t\tOften\t\t\tn = q − 1." << std::endl;
    std::cout << "\t\tNotation\t\t[n, k, n − k + 1] q-code" << std::endl;
    std::cout << "\t\tError max\t\tt = ( n − k ) / 2 = " << (fec_length >> 1) << std::endl;
    std::cout << "\t\tFEC = Reed-Solomon Forward Error Correction" << std::endl;
    std::cout << std::endl;

    /* This message have less than 255 characters */
    std::string message = "An expert is someone who knows more and more about less and "
                          "less until they know absolutely everything about nothing";

    /* 300 characters!!! over 255, X from character 240 */
    std::string message2 =  "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                            "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890"
                            "1234567890123456789012345678901234567890XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

    if(!initCheck())
        return -1;

    /*  Process messages with Reed Solomon Code Parameters 255 code length and 32 redundance and adding errors in some steps */
    std::cout << "--- Processing message: Message fit perfectly - No errors introduced" << std::endl;
    (void)process(message, 0, 0, 0);

    std::cout << "--- Processing message:  Message fit perfectly - 10 errors each 3 characters" << std::endl;
    (void)process(message, 10, 0, 3);

    std::cout  << "--- Processing message: Message too bit, autocrop message - 15 errors each 2 characters" << std::endl;
    (void)process(message2, 15, 15, 2);

    std::cout << "--- Processing message:  Message fit perfectly - 17 errors > t!!! cannot work" << std::endl;
    (void)process(message, 17, 0, 3);

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "\t\tAll messages has been processed!" << std::endl;
    std::cout << "-------------------------------------------------------------------------" << std::endl;
    return 0;
}
