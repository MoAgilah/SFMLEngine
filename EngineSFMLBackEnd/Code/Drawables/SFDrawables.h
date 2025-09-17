#pragma once

#include "../Renderer/SFRenderer.h"
#include <Engine/Interface/Drawables/IDrawable.h>
#include <memory>

template <typename T>
class SFDrawables : public IDrawable, public CompoundDrawableHolder<T>
{
public:
    virtual ~SFDrawables() = default;

    // Render only the primary drawable for base case
    void Render(IRenderer* renderer) override
    {
        auto* sfRenderer = dynamic_cast<SFRenderer*>(renderer);
        auto* drawable = this->GetPrimaryDrawableAs<T>();
        if (!sfRenderer || !drawable)
            return;

        sf::RenderWindow* window = static_cast<sf::RenderWindow*>(sfRenderer->GetWindow()->GetNativeHandle());
        if (window)
        {
            window->draw(*drawable);
        }
    }

    // Now these all work on the primary
    void SetPosition(const Vector2f& pos) override
    {
        auto* drawable = this->GetPrimaryDrawableAs<T>();
        if (drawable) drawable->setPosition(pos);
    }

    Vector2f GetPosition() override
    {
        auto* drawable = this->GetPrimaryDrawableAs<T>();
        return drawable ? Vector2f(drawable->getPosition()) : Vector2f();
    }

    void SetScale(const Vector2f& scl) override
    {
        m_scale = scl;
        auto* drawable = this->GetPrimaryDrawableAs<T>();
        if (drawable) drawable->setScale(scl);
    }

    Vector2f GetScale() override
    {
        return m_scale;
    }

    Vector2f GetOrigin() override
    {
        auto* drawable = this->GetPrimaryDrawableAs<T>();
        return drawable ? Vector2f(drawable->getOrigin()) : Vector2f();
    }

    void SetOrigin(const Vector2f& ori) override
    {
        auto* drawable = this->GetPrimaryDrawableAs<T>();
        if (drawable) drawable->setOrigin(ori);
    }

    Vector2f GetSize() override
    {
        auto* drawable = this->GetPrimaryDrawableAs<T>();
        if (drawable)
        {
            auto bounds = drawable->getGlobalBounds();
            return bounds.size;
        }
        return Vector2f();
    }

    void SetSize(const Vector2f& size) override
    {
        // Implement if needed for specific shape types
    }
};
