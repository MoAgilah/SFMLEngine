#include "SFFont.h"

#include <Utilities/Utils.h>
#include <SFML/Graphics/Font.hpp>

SFFont::SFFont()
    : m_font(std::make_unique<sf::Font>())
{
    ENSURE_VALID(m_font);
}

SFFont::~SFFont() = default;

bool SFFont::LoadFromFile(const std::string& filepath)
{
    ENSURE_VALID_RET(m_font, false);
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
