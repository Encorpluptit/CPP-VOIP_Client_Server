#include "Opus.hpp"
#include "BabelError.hpp"

Opus::Opus()
{
    int err;

    encoder = opus_encoder_create(48000, 1, OPUS_APPLICATION_VOIP, &err);
    decoder = opus_decoder_create(48000, 1, &err);
    if (err != OPUS_OK)
        throw (BabelErrors::BabelError("Opus Error on encoder or decoder"));
}

Opus::~Opus()
{
    if (encoder)
        opus_encoder_destroy(encoder);
    if (decoder)
        opus_decoder_destroy(decoder);
}

std::vector<uint16_t> Opus::encode(const std::vector<uint16_t> &voice) {

    std::vector<uint16_t> compressed(voice.size());
    int bytes = opus_encode(encoder, (opus_int16 const *) voice.data(), (int) voice.size(), (unsigned char *) compressed.data(), (int) compressed.size());
    
    if (bytes < 0)
        throw (BabelErrors::BabelError("Opus compression error"));
    return (compressed);
}

std::vector<uint16_t> Opus::decode(const std::vector<uint16_t> &voice) {

    std::vector<uint16_t> decompressed(voice.size());
    int bytes = opus_decode(decoder, (unsigned char *) voice.data(), (int) voice.size(), (opus_int16 *) decompressed.data(), (int) decompressed.size(), 0);
    
    if (bytes < 0)
        throw (BabelErrors::BabelError("Opus decompression error"));
    return (decompressed);
}