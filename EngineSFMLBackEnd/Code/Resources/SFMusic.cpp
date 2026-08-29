#include "SFMusic.h"

#include <Utilities/Guards.h>
#include <SFML/Audio/Music.hpp>

SFMusic::SFMusic()
    : m_music(std::make_unique<sf::Music>())
{
    if (!CheckNotNull(m_music.get(), "Invalid Pointer 'm_music'"))
        throw std::invalid_argument("SFMusic requires a valid music");
}

SFMusic::~SFMusic() = default;

bool SFMusic::LoadFromFile(const std::string& filepath)
{
    if (!CheckNotNull(m_music.get(), "Invalid Pointer 'm_music'"))
        return false;

    return m_music->openFromFile(filepath);
}

void SFMusic::Play()
{
    if (!CheckNotNull(m_music.get(), "Invalid Pointer 'm_music'"))
        return;

    m_music->play();
}

void SFMusic::Pause()
{
    if (!CheckNotNull(m_music.get(), "Invalid Pointer 'm_music'"))
        return;

    m_music->pause();
}

void SFMusic::Stop()
{
    if (!CheckNotNull(m_music.get(), "Invalid Pointer 'm_music'"))
        return;

    m_music->stop();
}

void SFMusic::SetLoop(bool loop)
{
    if (!CheckNotNull(m_music.get(), "Invalid Pointer 'm_music'"))
        return;

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
