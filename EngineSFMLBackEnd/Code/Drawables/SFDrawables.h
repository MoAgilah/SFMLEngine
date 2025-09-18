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
