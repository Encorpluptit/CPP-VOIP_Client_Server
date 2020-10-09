#pragma once

#include <vector>
#include <cstdint>

class IAudio {
    public:

        virtual bool init_audio() = 0;

        virtual bool stop_audio() = 0;

        virtual std::vector<uint16_t> getVoice() = 0;

        virtual void playVoice(const std::vector<uint16_t> &record) = 0;

    private:
};