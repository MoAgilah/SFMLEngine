#pragma once

#include <Engine/Interface/Resources/ITexture.h>
#include <memory>
#include <string>

// Forward declare to avoid pulling SFML headers into this header
namespace sf { class Texture; }

class SFTexture : public ITexture
{
public:
    SFTexture();
    ~SFTexture() override;

    bool LoadFromFile(const std::string& filepath) override;

    // Escape hatch: only visible where you include SFTexture.h
    sf::Texture& GetNativeTexture();
    const sf::Texture& GetNativeTexture() const;

private:

    std::unique_ptr<sf::Texture> m_texture;
};
