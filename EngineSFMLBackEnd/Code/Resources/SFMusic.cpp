#include "SFMusic.h"

#include <Utilities/Utils.h>
#include <SFML/Audio/Music.hpp>

SFMusic::SFMusic()
    : m_music(std::make_unique<sf::Music>())
{
    ENSURE_VALID(m_music);
}

SFMusic::~SFMusic() = default;

bool SFMusic::LoadFromFile(const std::string& filepath)
{
    ENSURE_VALID_RET(m_music, false);
    // sf::Music streams from file
    return m_music->openFromFile(filepath);
}

void SFMusic::Play()
{
    ENSURE_VALID(m_music);
    m_music->play();
}

void SFMusic::Pause()
{
    ENSURE_VALID(m_music);
    m_music->pause();
}

void SFMusic::Stop()
{
    ENSURE_VALID(m_music);
    m_music->stop();
}

void SFMusic::SetLoop(bool loop)
{
    ENSURE_VALID(m_music);
    m_music->setLooping(loop);
}

sf::Music& SFMusic::GetNativeMusic()
{
    return *m_music.get();
}

const sf::Music& SFMusic::GetNativeMusic() const
{
    return *m_music.get();
}
