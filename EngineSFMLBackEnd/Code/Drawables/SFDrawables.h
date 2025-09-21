#pragma once

#include <Engine/Interface/Drawables/IDrawable.h>
#include <memory>

template <typename T>
class SFDrawables : public IDrawable, public CompoundDrawableHolder<T>
{
public:
    virtual ~SFDrawables() = default;

    // Render only the primary drawable for base case
    void Render(IRenderer* renderer) override;

    // Now these all work on the primary
    void SetPosition(const Vector2f& pos) override;

    Vector2f GetPosition() override;

    void SetScale(const Vector2f& scl) override;

    Vector2f GetScale() override;

    Vector2f GetOrigin() override;

    void SetOrigin(const Vector2f& ori) override;

    Vector2f GetSize() override;

    void SetSize(const Vector2f& size) override;
};

namespace sf { class Sprite; class Shape; class Text; class RectangleShape; class CircleShape; class ConvexShape; }

extern template class SFDrawables<sf::Sprite>;
extern template class SFDrawables<sf::Shape>;
extern template class SFDrawables<sf::Text>;
extern template class SFDrawables<sf::RectangleShape>;
extern template class SFDrawables<sf::CircleShape>;
extern template class SFDrawables<sf::ConvexShape>;