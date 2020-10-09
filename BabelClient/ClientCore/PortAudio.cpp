#include "PortAudio.hpp"
#include "BabelError.hpp"

PortAudio::PortAudio()
{
    int err = Pa_Initialize();
    std::cout << "ERROR PORTAUDIO : " << Pa_GetErrorText(err) << std::endl;
    if (err != paNoError)
        throw (BabelErrors::BabelError("PortAudio Initialization"));
}

PortAudio::~PortAudio()
{
    Pa_Terminate();
}

bool PortAudio::init_audio()
{
    if (Pa_OpenDefaultStream(&stream, 1, 1, paInt16, 48000, 480, nullptr, nullptr) != paNoError) {
        Pa_Terminate();
        throw (BabelErrors::BabelError("PortAudio OpenStream"));
    }
    if (Pa_StartStream(stream) != paNoError) {
        Pa_Terminate();
        throw (BabelErrors::BabelError("PortAudio StartStream"));
    }
    return (true);
}

bool PortAudio::stop_audio()
{
    if (Pa_CloseStream(stream) != paNoError) {
        Pa_Terminate();
        throw (BabelErrors::BabelError("PortAudio CloseStream"));
    }
    return (true);
}

std::vector<uint16_t> PortAudio::getVoice() {

    long len = Pa_GetStreamReadAvailable(stream);
    std::vector<uint16_t> record(480);

    if (len < 0)
        throw (BabelErrors::BabelError("PortAudio Error StreamReadAvailable"));
    while ((len = Pa_GetStreamReadAvailable(stream)) < 480);
    /*if (len < (long) 480)
        Pa_ReadStream(stream, record.data(), (unsigned long) len);
    else*/
    Pa_ReadStream(stream, record.data(), 480);
    return (record);
}

void PortAudio::playVoice(const std::vector<uint16_t> &record)
{
    long len = Pa_GetStreamWriteAvailable(stream);

    while ((len = Pa_GetStreamWriteAvailable(stream)) < (long) record.size());
    Pa_WriteStream(stream, record.data(), record.size());
}