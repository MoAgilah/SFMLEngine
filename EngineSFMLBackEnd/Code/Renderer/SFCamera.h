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

    sf::View* GetView();

private:

    std::unique_ptr<sf::View> m_camera;
};