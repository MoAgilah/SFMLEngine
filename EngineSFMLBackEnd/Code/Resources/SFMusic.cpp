#include "SFMusic.h"

#include <SFML/Audio/Music.hpp>

SFMusic::SFMusic()
    : m_music(std::make_unique<sf::Music>())
{}

SFMusic::~SFMusic() = default;

bool SFMusic::LoadFromFile(const std::string& filepath)
{
    // sf::Music streams from file
    return m_music->openFromFile(filepath);
}

void SFMusic::Play()
{
    m_music->play();
}

void SFMusic::Pause()
{
    m_music->pause();
}

void SFMusic::Stop()
{
    m_music->stop();
}

void SFMusic::SetLoop(bool loop)
{
    m_music->setLooping(loop);
}

sf::Music& SFMusic::GetNativeMusic()
{
    return *m_music;
}

const sf::Music& SFMusic::GetNativeMusic() const
{
    return *m_music;
}
