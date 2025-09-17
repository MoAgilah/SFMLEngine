#pragma once

#include "SFWindow.h"
#include <Engine/Interface/Renderer/IRenderer.h>
#include <Utilities/Vector.h>

class SFRenderer : public IRenderer
{
public:
    void Initialise(const Vector2f& screenDims, const std::string& title) override;
	void PollWindowEvents() override;
	void Clear() override;
	void Draw(IRenderable* object) override;
	void Present() override;
};