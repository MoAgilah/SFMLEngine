#pragma once

#include <Resources/SFShader.h>

class TestableSFShader : public SFShader
{
public:
	TestableSFShader()
		: SFShader()
	{}

	std::optional<int> GetNativeShaderTypeForTesting(std::optional<ShaderType> shaderType)
	{
		return GetNativeShaderType(shaderType);
	}
};

