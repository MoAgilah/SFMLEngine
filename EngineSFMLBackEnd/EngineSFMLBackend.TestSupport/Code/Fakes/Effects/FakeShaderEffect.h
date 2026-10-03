#pragma once

#include <Engine/Interface/Effects/IShaderEffect.h>

class FakeShaderEffect : public IShaderEffect
{
public:
	FakeShaderEffect(IShader* shader)
		: IShaderEffect(shader)
	{}

	void Update(float deltaTime) override
	{
		updateCalled = true;
		passedDeltaTime = deltaTime;
	}

public:

	bool updateCalled = false;
	float passedDeltaTime = 0.f;
};