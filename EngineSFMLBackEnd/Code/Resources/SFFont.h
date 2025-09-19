#pragma once

#include <Engine/Interface/Resources/IFont.h>
#include <memory>
#include <string>

// forward declare sf::Font
namespace sf { class Font; }

class SFFont : public IFont
{
public:
    SFFont();
    ~SFFont() override;

    bool LoadFromFile(const std::string& filepath) override;

    // Escape hatch, only visible if you include SFFont.h
    sf::Font& GetNativeFont();
    const sf::Font& GetNativeFont() const;

private:
    std::unique_ptr<sf::Font> m_font; // opaque to engine users
};
