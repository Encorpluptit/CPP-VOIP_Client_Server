#pragma once

#include <iostream>
#include <portaudio.h>
#include "IAudio.hpp"

class PortAudio : public IAudio
{
    public:

        PortAudio();

        ~PortAudio();

        bool init_audio();

        bool stop_audio();

        std::vector<uint16_t> getVoice();

        void playVoice(const std::vector<uint16_t> &record);

        PaStreamParameters input;
        PaStreamParameters output;
        PaStream *stream;
};