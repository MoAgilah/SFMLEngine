#pragma once

#include <Engine/Interface/Resources/IMusic.h>
#include <memory>
#include <string>

// forward declare sf::Music so we don't include SFML headers here
namespace sf { class Music; }

class SFMusic : public IMusic
{
public:
    SFMusic();
    ~SFMusic() override;

    // IMusic
    bool LoadFromFile(const std::string& filepath) override;
    void Play() override;
    void Pause() override;
    void Stop() override;
    void SetLoop(bool loop) override;

    // Escape hatch: only available if you include SFMusic.h
    sf::Music& GetNativeMusic();
    const sf::Music& GetNativeMusic() const;

private:

    std::unique_ptr<sf::Music> m_music;
};
