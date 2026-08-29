#include "SFFont.h"

#include <Utilities/Guards.h>
#include <SFML/Graphics/Font.hpp>

SFFont::SFFont()
    : m_font(std::make_unique<sf::Font>())
{
    if (!CheckNotNull(m_font.get(), "Invalid Pointer 'm_font'"))
        throw std::invalid_argument("SFFont requires a valid font");
}

SFFont::~SFFont() = default;

bool SFFont::LoadFromFile(const std::string& filepath)
{
    if (!CheckNotNull(m_font.get(), "Invalid Pointer 'm_font'"))
        return false;

    return m_font->openFromFile(filepath);
}

sf::Font& SFFont::GetNativeFont()
{
    return *m_font.get();
}

const sf::Font& SFFont::GetNativeFont() const
{
    return *m_font.get();
}
