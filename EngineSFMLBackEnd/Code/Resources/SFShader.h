#pragma once

#include <Engine/Interface/Resources/IShader.h>
#include <filesystem>
#include <memory>
#include <optional>
#include <string>

namespace fs = std::filesystem;

// Forward declare sf::Shader to avoid pulling SFML headers here
namespace sf { class Shader; }

class SFShader : public IShader
{
public:
    SFShader();
    ~SFShader() override;

    bool LoadFromFile(const std::string& filepath) override;

    // Escape hatch: only leaks SFML where you *explicitly* include this header.
    sf::Shader& GetNativeShader();
    const sf::Shader& GetNativeShader() const;

private:
    // Helper that maps engine ShaderType -> sf::Shader::Type
    std::optional<int> GetNativeShaderType(std::optional<ShaderType> shaderType);

private:
    // Keep your original name
    std::unique_ptr<sf::Shader> m_shader;
};
