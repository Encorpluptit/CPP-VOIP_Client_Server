
#include "tests_run.hpp"
#include "PortAudio.hpp"
#include "Opus.hpp"
#include "BabelError.hpp"
#include "NetworkClientSocket.hpp"
#include "QUdpSocket.hpp"
#include "QtSocket.hpp"

Test(Client, PortAudio_Codec)
{
    std::shared_ptr<IAudio> audio = std::make_shared<PortAudio>();
    std::shared_ptr<ICodec> codec = std::make_shared<Opus>();

    cr_assert_not_null(audio);
    cr_assert_not_null(codec);
}

Test(Client, PortAudio_Codec1)
{
    std::shared_ptr<IAudio> audio = std::make_shared<PortAudio>();
    std::shared_ptr<ICodec> codec = std::make_shared<Opus>();
    std::vector<uint16_t> voice(480);

    codec->encode(voice);
    codec->decode(voice);
    cr_assert_neq(voice.size(), 0);
}

Test(Client, PortAudio_Codec2)
{
    std::shared_ptr<ICodec> codec = std::make_shared<Opus>();
    std::vector<uint16_t> voice;

    cr_assert_throw(
        codec->encode(voice),
        BabelErrors::BabelError
    );
}

Test(Client, PortAudio_Codec3)
{
    std::shared_ptr<ICodec> codec = std::make_shared<Opus>();
    std::vector<uint16_t> voice{2, 3};

    cr_assert_throw(
        codec->decode(voice),
        BabelErrors::BabelError
    );
}

Test(Client, PortAudio_Codec4)
{
    std::shared_ptr<IAudio> audio = std::make_shared<PortAudio>();
    std::shared_ptr<ICodec> codec = std::make_shared<Opus>();
    std::vector<uint16_t> voice;

    audio->init_audio();
    voice = audio->getVoice();
    voice = codec->encode(voice);
    voice = codec->decode(voice);
    audio->playVoice(voice);
    audio->stop_audio();
    cr_assert_neq(voice.size(), 0);
}