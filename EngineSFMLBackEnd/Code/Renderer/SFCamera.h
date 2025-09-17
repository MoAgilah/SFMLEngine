#pragma once

#include <Engine/Interface/Renderer/ICamera.h>
#include <Engine/Collisions/BoundingBox.h>
#include "../Drawables/SFShape.h"
#include <SFML/Graphics/View.hpp>
#include <memory>

class SFCamera : public ICamera
{
public:
    SFCamera();
    ~SFCamera() override = default;

    void Update() override;
    void Reset(IRenderer* renderer) override;
    void RenderDebug(IRenderer* renderer) override;

    bool IsInView(IBoundingVolume* volume) override;
    bool CheckVerticalBounds(IBoundingVolume* volume) override;

    sf::View GetView() const { return m_camera; }

private:
    sf::View m_camera;
    std::shared_ptr<BoundingBox<SFRect>> m_viewBox;
};