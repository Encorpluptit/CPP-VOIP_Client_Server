#pragma once

#include <iostream>
#include <portaudio.h>
#include "IAudio.hpp"

class PortAudio : public IAudio
{
    public:

        PortAudio() {

            int err = Pa_Initialize();
            std::cout << "ERROR PORTAUDIO : " << Pa_GetErrorText(err) << std::endl;
            if (err != paNoError)
                std::cout << "Pa_Initialize failed" << std::endl; // THROW
        }

        ~PortAudio() {

            Pa_Terminate();
        }

        bool init_audio() {

            if (Pa_OpenDefaultStream(&stream, 1, 1, paInt16, 48000, 480, nullptr, nullptr) != paNoError)
                Pa_Terminate(); // THROW
            if (Pa_StartStream(stream) != paNoError)
                Pa_Terminate(); // THROW
            return (true);
        }

        bool stop_audio() {

            if (Pa_CloseStream(stream) != paNoError)
                Pa_Terminate(); // THROW
            return (true);
        }

        std::vector<uint16_t> getVoice() {

            long len = Pa_GetStreamReadAvailable(stream);
            std::vector<uint16_t> record(480);

            if (len < 0)
                std::cout << "getVoice" << std::endl; // THROW
            if (len < (long) 480)
                Pa_ReadStream(stream, record.data(), (unsigned long) len);
            else
                Pa_ReadStream(stream, record.data(), 480);
            return (record);
        }

        void playVoice(std::vector<uint16_t> record) {

            long len = 0;
            while ((len = Pa_GetStreamWriteAvailable(stream)) < (long) record.size());
            Pa_WriteStream(stream, record.data(), (unsigned long) record.size());
        }

        PaStreamParameters input;
        PaStreamParameters output;
        PaStream *stream;
};