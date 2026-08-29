#include "SFSound.h"

#include <Utilities/Guards.h>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

SFSound::SFSound()
    : m_buffer(std::make_unique<sf::SoundBuffer>())
    , m_sound(std::make_unique<sf::Sound>(*m_buffer.get()))
{
    if (!CheckNotNull(m_buffer.get(), "Invalid Pointer 'm_buffer'"))
        throw std::invalid_argument("SFSound requires a valid buffer");

    if (!CheckNotNull(m_sound.get(), "Invalid Pointer 'm_sound'"))
        throw std::invalid_argument("SFSound requires a valid sound");
}

SFSound::~SFSound() = default;

bool SFSound::LoadFromFile(const std::string& filepath)
{
    if (!CheckNotNull(m_buffer.get(), "Invalid Pointer 'm_buffer'"))
        return false;

    if (!CheckNotNull(m_sound.get(), "Invalid Pointer 'm_sound'"))
        return false;

    if (!m_buffer->loadFromFile(filepath))
        return false;

    m_sound->setBuffer(*m_buffer);

    return true;
}

void SFSound::Play()
{
    if (!CheckNotNull(m_sound.get(), "Invalid Pointer 'm_sound'"))
        return;

    m_sound->play();
}

void SFSound::Pause()
{
    if (!CheckNotNull(m_sound.get(), "Invalid Pointer 'm_sound'"))
        return;

    m_sound->pause();
}

void SFSound::Stop()
{
    if (!CheckNotNull(m_sound.get(), "Invalid Pointer 'm_sound'"))
        return;

    m_sound->stop();
}

void SFSound::SetLoop(bool loop)
{
    if (!CheckNotNull(m_sound.get(), "Invalid Pointer 'm_sound'"))
        return;

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
