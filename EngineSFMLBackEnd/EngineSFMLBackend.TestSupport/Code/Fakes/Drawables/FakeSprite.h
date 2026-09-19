#pragma once

#include "FakeDrawable.h"
#include <Engine/Interface/Drawables/ISprite.h>

class FakeSprite : public FakeDrawable<FakeSprite>, public ISprite
{
public:
	FakeSprite(const std::string& texId)
	{
		SetTexture(texId);

        const auto texSize = GetTextureSize();
        SetOrigin(Vector2f(static_cast<float>(texSize.x), static_cast<float>(texSize.y)) * 0.5f);

        renderId = texId;
	}

    void Update(float deltaTime) override
    {
        updateCount++;
        lastDeltaTime = deltaTime;
    }

    void Render(IRenderer* renderer) override
    {
        renderCount++;

        if (renderLog)
        {
            renderLog->push_back(renderId);
        }
    }

	bool SetTexture(const std::string& texId)
	{
		m_texID = texId;
		return true;
	}

	void SetDirection(bool dir) override
    {
        direction = dir;
    }

	virtual Vector2u GetTextureSize() const override { return Vector2u(16, 16); }
	virtual void SetTextureRect(const IntRect& rect) override {}

public:

    int renderCount = 0;
    int updateCount = 0;

    float lastDeltaTime = 0.0f;

    bool direction = true;

    std::vector<std::string>* renderLog = nullptr;
    std::string renderId = "sprite";
};

