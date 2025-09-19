#include "SFShader.h"

#include <SFML/Graphics/Shader.hpp>
#include <utility>

SFShader::SFShader()
    : m_shader(std::make_unique<sf::Shader>())
{}

SFShader::~SFShader() = default;

bool SFShader::LoadFromFile(const std::string& filepath)
{
    fs::path entry = fs::path(filepath);

    auto type = GetNativeShaderType(
        ShaderTypeFromExtension(entry.extension().string().substr(1))
    );

    if (!type)
        return false;

    // reinterpret_cast because we stored the enum underlying as int in GetNativeShaderType
    auto nativeType = static_cast<sf::Shader::Type>(*type);

    return m_shader->loadFromFile(filepath, nativeType);
}

sf::Shader& SFShader::GetNativeShader()
{
    return *m_shader;
}

const sf::Shader& SFShader::GetNativeShader() const
{
    return *m_shader;
}

std::optional<int> SFShader::GetNativeShaderType(std::optional<ShaderType> shaderType)
{
    if (!shaderType)
        return std::nullopt;

    switch (shaderType.value())
    {
    case ShaderType::Vertex:   return static_cast<int>(sf::Shader::Type::Vertex);
    case ShaderType::Fragment: return static_cast<int>(sf::Shader::Type::Fragment);
    case ShaderType::Geometry: return static_cast<int>(sf::Shader::Type::Geometry);
    default:                   return std::nullopt;
    }
}