#pragma once

#include <Engine/Interface/Drawables/IDrawable.h>

template <typename T>
class FakeDrawable: public IDrawable, public CompoundDrawableHolder<T>
{
public:
    virtual ~FakeDrawable() = default;

    void Render(IRenderer* renderer) {}
    void Render(IRenderer* renderer, IShader* shader) {}

    void SetPosition(const Vector2f& pos) { m_position = pos; }

    Vector2f GetPosition() override { return m_position; }

    void SetScale(const Vector2f& scl) override { m_scale = scl; }

    Vector2f GetScale() override { return m_scale; }

    Vector2f GetOrigin() override { return m_origin; }

    void SetOrigin(const Vector2f& ori) override { m_origin = ori; }

    Vector2f GetSize() override { return m_size; }

    void SetSize(const Vector2f& size) override { m_size = size; }

    Vector2f GetGlobalSize() override { return { m_size.x * m_scale.x, m_size.y * m_scale.y }; }

    Vector2f GetLocalSize() override { return m_size; }
    void SetLocalSize(const Vector2f& size) override { m_size = size; }

protected:

    Vector2f m_position;
    Vector2f m_origin;
    Vector2f m_size;
};

