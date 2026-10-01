#pragma once

#include <Engine/Core/Constants.h>
#include <Drawables/SFShape.h>
#include <SFML/Graphics/RectangleShape.hpp>

class TestableSFShape : public SFShape<sf::RectangleShape>
{
public:
	TestableSFShape()
	{
		SetDrawable(std::make_shared<sf::RectangleShape>());
	}

	void ForTestingMakeShapeNull()
	{
		SetDrawable(nullptr);
	}

	void Update(const Vector2f& pos) override {}

	void Render(IRenderer* renderer) override {}
};