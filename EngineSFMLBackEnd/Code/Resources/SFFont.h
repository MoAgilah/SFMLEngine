#pragma once

#include <Engine/Interface/Resources/IFont.h>
#include <SFML/Graphics/Font.hpp>
#include <memory>

class SFFont : public IFont
{
public:
    bool LoadFromFile(const std::string& filepath) override
    {
        return font.openFromFile(filepath);
    }

    sf::Font& GetNativeFont() { return font; }

private:

    sf::Font font;
};