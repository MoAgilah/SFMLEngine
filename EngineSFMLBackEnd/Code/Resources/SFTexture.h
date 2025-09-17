#pragma once

#include <Engine/Interface/Resources/ITexture.h>
#include <SFML/Graphics.hpp>
#include <memory>

class SFTexture : public ITexture
{
public:
	bool LoadFromFile(const std::string& filepath) override
	{
        return m_texture.loadFromFile(filepath);
	}

    sf::Texture& GetNativeTexture() { return m_texture; }

private:
    sf::Texture m_texture;
};