#pragma once

#include <iostream>
#include <portaudio.h>
#include "IAudio.hpp"

class PortAudio : public IAudio
{
    public:

        PortAudio();

        ~PortAudio();

        bool init_audio() override;

        bool stop_audio() override;

        std::vector<uint16_t> getVoice() override;

        void playVoice(const std::vector<uint16_t> &record) override;

        PaStreamParameters input{};
        PaStreamParameters output{};
        PaStream *stream{};
};