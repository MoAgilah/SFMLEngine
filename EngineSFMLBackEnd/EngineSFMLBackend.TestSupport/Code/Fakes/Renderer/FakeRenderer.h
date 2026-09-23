#pragma once

#include <Engine/Interface/Renderer/IRenderer.h>

class FakeRenderer: public IRenderer
{
public:
	FakeRenderer()
	{
		m_window = nullptr;
	}

	bool Initialise(const Vector2f& screenDims, const std::string& title) override { return true; }
	void PollWindowEvents() override {}
	void Clear() override {}
	void Draw(IRenderable* object) override {}
	void Draw(IRenderable* object, IShader* shader) override {}
	void Present() override {}
};