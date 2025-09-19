#include "SFTexture.h"

#include <SFML/Graphics/Texture.hpp>

SFTexture::SFTexture()
    : m_texture(std::make_unique<sf::Texture>())
{}

SFTexture::~SFTexture() = default;

bool SFTexture::LoadFromFile(const std::string& filepath)
{
    return m_texture->loadFromFile(filepath);
}

sf::Texture& SFTexture::GetNativeTexture()
{
    return *m_texture;
}

const sf::Texture& SFTexture::GetNativeTexture() const
{
    return *m_texture;
}
