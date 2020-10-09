#pragma once

#include <vector>
#include <stdint.h>

class ICodec {
    public:

        virtual std::vector<uint16_t> encode(const std::vector<uint16_t> &voice) = 0;

        virtual std::vector<uint16_t> decode(const std::vector<uint16_t> &voice) = 0;

    private:
};