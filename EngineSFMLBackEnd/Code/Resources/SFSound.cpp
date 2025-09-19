#include "SFSound.h"

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

SFSound::SFSound()
    : m_buffer(std::make_unique<sf::SoundBuffer>())
    , m_sound(std::make_unique<sf::Sound>(*m_buffer.get()))
{}

SFSound::~SFSound() = default;

bool SFSound::LoadFromFile(const std::string& filepath)
{
    if (!m_buffer->loadFromFile(filepath))
        return false;

    m_sound->setBuffer(*m_buffer);

    return true;
}

void SFSound::Play()
{
    m_sound->play();
}

void SFSound::Pause()
{
    m_sound->pause();
}

void SFSound::Stop()
{
    m_sound->stop();
}

void SFSound::SetLoop(bool loop)
{
    m_sound->setLooping(loop);
}

sf::Sound& SFSound::GetNativeSound()
{
    return *m_sound;
}

const sf::Sound& SFSound::GetNativeSound() const
{
    return *m_sound;
}
