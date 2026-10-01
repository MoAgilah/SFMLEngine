#pragma once

#include <Engine/Interface/Resources/IShader.h>

class FakeShader : public IShader
{
public:
	FakeShader() = default;

	bool LoadFromFile(const std::string& filepath) override
	{
		return true;
	}
};