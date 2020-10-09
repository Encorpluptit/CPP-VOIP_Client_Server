#pragma once

#include <vector>
#include <stdint.h>

class IAudio {
    public:

        virtual bool init_audio() = 0;

        virtual bool stop_audio() = 0;

        virtual std::vector<uint16_t> getVoice() = 0;

        virtual void playVoice(std::vector<uint16_t> record) = 0;

    private:
};