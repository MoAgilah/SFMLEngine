#pragma once

#include <Engine/Interface/Renderer/ICamera.h>
#include <memory>

namespace sf { class View; }
template <typename T> class BoundingBox;
class SFRect;

class SFCamera : public ICamera
{
public:
    SFCamera();
    ~SFCamera() override;

    void Update() override;
    void Reset(IRenderer* renderer) override;
    void RenderDebug(IRenderer* renderer) override;

    bool IsInView(IBoundingVolume* volume) override;
    bool CheckVerticalBounds(IBoundingVolume* volume) override;

private:

    std::unique_ptr<sf::View> m_camera;
    std::shared_ptr<BoundingBox<SFRect>> m_viewBox;
};