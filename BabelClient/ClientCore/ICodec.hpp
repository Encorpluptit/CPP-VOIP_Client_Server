#pragma once

#include <vector>
#include <cstdint>

class ICodec {
    public:

        virtual std::vector<uint16_t> encode(const std::vector<uint16_t> &voice) = 0;

        virtual std::vector<uint16_t> decode(const std::vector<uint16_t> &voice) = 0;

    private:
};