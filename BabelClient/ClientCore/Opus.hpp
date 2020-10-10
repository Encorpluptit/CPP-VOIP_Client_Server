#pragma once

#include <iostream>
#include "ICodec.hpp"
#include <opus/opus.h>

class Opus : public ICodec
{
    public:
        Opus();

        ~Opus();

        std::vector<uint16_t> encode(const std::vector<uint16_t> &voice) override;

        std::vector<uint16_t> decode(const std::vector<uint16_t> &voice);
    
        OpusEncoder *encoder;
        OpusDecoder *decoder;
};