#include "SFTexture.h"

#include <Utilities/Utils.h>
#include <SFML/Graphics/Texture.hpp>

SFTexture::SFTexture()
    : m_texture(std::make_unique<sf::Texture>())
{
    ENSURE_VALID(m_texture);
}

SFTexture::~SFTexture() = default;

bool SFTexture::LoadFromFile(const std::string& filepath)
{
    ENSURE_VALID_RET(m_texture, false);
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
