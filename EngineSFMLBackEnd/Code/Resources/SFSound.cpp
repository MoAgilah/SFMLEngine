#include "SFSound.h"

#include <Utilities/Utils.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

SFSound::SFSound()
    : m_buffer(std::make_unique<sf::SoundBuffer>())
    , m_sound(std::make_unique<sf::Sound>(*m_buffer.get()))
{
    ENSURE_VALID(m_buffer);
    ENSURE_VALID(m_sound);
}

SFSound::~SFSound() = default;

bool SFSound::LoadFromFile(const std::string& filepath)
{
    ENSURE_VALID_RET(m_buffer, false);
    ENSURE_VALID_RET(m_sound, false);

    if (!m_buffer->loadFromFile(filepath))
        return false;

    m_sound->setBuffer(*m_buffer);

    return true;
}

void SFSound::Play()
{
    ENSURE_VALID(m_sound);
    m_sound->play();
}

void SFSound::Pause()
{
    ENSURE_VALID(m_sound);
    m_sound->pause();
}

void SFSound::Stop()
{
    ENSURE_VALID(m_sound);
    m_sound->stop();
}

void SFSound::SetLoop(bool loop)
{
    ENSURE_VALID(m_sound);
    m_sound->setLooping(loop);
}

sf::Sound& SFSound::GetNativeSound()
{
    return *m_sound.get();
}

const sf::Sound& SFSound::GetNativeSound() const
{
    return *m_sound.get();
}
