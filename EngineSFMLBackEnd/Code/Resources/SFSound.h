#pragma once

#include <Engine/Interface/Resources/ISound.h>
#include <memory>
#include <string>

namespace sf
{
    class Sound;
    class SoundBuffer;
}

class SFSound : public ISound
{
public:
    SFSound();
    ~SFSound() override;

    // ISound
    bool LoadFromFile(const std::string& filepath) override;
    void Play() override;
    void Pause() override;
    void Stop() override;
    void SetLoop(bool loop) override;

    // Escape hatch: only visible if you include SFSound.h
    sf::Sound& GetNativeSound();
    const sf::Sound& GetNativeSound() const;

private:

    // Keep lifetime: buffer must outlive sound
    std::unique_ptr<sf::SoundBuffer> m_buffer;
    std::unique_ptr<sf::Sound>       m_sound;
};