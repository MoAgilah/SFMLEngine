#include "SFFont.h"

#include <SFML/Graphics/Font.hpp>

SFFont::SFFont()
    : m_font(std::make_unique<sf::Font>())
{}

SFFont::~SFFont() = default;

bool SFFont::LoadFromFile(const std::string& filepath)
{
    return m_font->openFromFile(filepath);
}

sf::Font& SFFont::GetNativeFont()
{
    return *m_font;
}

const sf::Font& SFFont::GetNativeFont() const
{
    return *m_font;
}
