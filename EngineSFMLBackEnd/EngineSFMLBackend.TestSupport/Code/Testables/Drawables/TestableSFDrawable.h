#pragma once

#include <Engine/Core/Constants.h>
#include <Drawables/SFDrawables.h>
#include <SFML/Graphics/RectangleShape.hpp>

class TestableSFDrawable : public SFDrawables<sf::RectangleShape>
{
public:
	TestableSFDrawable()
	{
		SetDrawable(std::make_shared<sf::RectangleShape>());
	}

	TestableSFDrawable(const Vector2f& size)
	{
		SetDrawable(std::make_shared<sf::RectangleShape>(size));
	}

	void ForTestingMakeDrawableNull()
	{
		SetDrawable(nullptr);
	}
};