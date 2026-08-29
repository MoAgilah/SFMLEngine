#include "SFTexture.h"

#include <Utilities/Guards.h>
#include <SFML/Graphics/Texture.hpp>

SFTexture::SFTexture()
    : m_texture(std::make_unique<sf::Texture>())
{
    if (!CheckNotNull(m_texture.get(), "Invalid Pointer 'm_texture'"))
        throw std::invalid_argument("SFTexture requires a valid texture");
}

SFTexture::~SFTexture() = default;

bool SFTexture::LoadFromFile(const std::string& filepath)
{
    if (!CheckNotNull(m_texture.get(), "Invalid Pointer 'm_texture'"))
        return false;

    return m_texture->loadFromFile(filepath);
}

sf::Texture& SFTexture::GetNativeTexture()
{
    return *m_texture.get();
}

const sf::Texture& SFTexture::GetNativeTexture() const
{
    return *m_texture.get();
}
