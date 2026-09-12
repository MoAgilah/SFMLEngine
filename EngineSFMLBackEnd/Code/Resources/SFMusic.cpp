#include "SFMusic.h"

#include <Utilities/Guards.h>
#include <SFML/Audio/Music.hpp>

SFMusic::SFMusic()
    : m_music(std::make_unique<sf::Music>())
{}

SFMusic::~SFMusic() = default;

bool SFMusic::LoadFromFile(const std::string& filepath)
{
    if (!CheckNotNull(m_music.get(), "Invalid Pointer 'm_music'"))
        return false;

    m_isLoaded = m_music->openFromFile(filepath);

    return m_isLoaded;
}

void SFMusic::Play()
{
    if (!CheckNotNull(m_music.get(), "Invalid Pointer 'm_music'"))
        return;

    if (!m_isLoaded)
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
