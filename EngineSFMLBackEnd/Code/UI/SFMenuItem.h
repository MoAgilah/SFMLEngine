#pragma once

#include "../Drawables/SFText.h"
#include "../Drawables/SFSprite.h"
#include <Engine/Interface/UI/IMenuItem.h>
#include <Utilities/Vector.h>

class SFMenuItem : public IMenuItem
{
public:
	SFMenuItem(const Vector2f& menuSize, float outlineThickness);
	~SFMenuItem() = default;

	Vector2f GetPosition() const override;
	void SetPosition(const Vector2f& position) override;

	Vector2f GetOrigin() const override;
	Vector2f GetSize() const override;

	IText* AddTextElement(std::shared_ptr<IText>  text) override;
	ISprite* AddSpriteElement(std::shared_ptr<ISprite>  spr) override;
};