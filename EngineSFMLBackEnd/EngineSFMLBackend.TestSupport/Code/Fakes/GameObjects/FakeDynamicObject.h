#pragma once

#include <GameObjects/GameObject.h>

class FakeDynamicGameObject : public DynamicGameObject
{
public:
    void SetTestDrawable(std::shared_ptr<IDrawable> drawable)
    {
        m_drawable = std::move(drawable);
    }

    void SetTestVolume(std::shared_ptr<IBoundingVolume> volume)
    {
        m_volume = std::move(volume);
    }

    void Update(float deltaTime) {}
    void OnCollisionEnter(IGameObject* obj) {}
    void OnCollisionStay(IGameObject* obj) {}
    void OnCollisionExit(IGameObject* obj) {}
    void ResolveCollisions(float time, const Vector2f& separationVector, float relativeHitPosition) {}
};