#include "SFCamera.h"

#include <Engine/Core/Constants.h>

SFCamera::SFCamera()
{
    const auto& screenDim = GameConstants::ScreenDim;
    const Vector2f center = screenDim * 0.5f;

    m_camera.setSize(screenDim);
    m_camera.setCenter(center);
    m_camera.setViewport({ {0.f, 0.f}, {1.f, 1.f} });

    m_viewBox = std::make_shared<BoundingBox<SFRect>>(screenDim, center);
    m_viewBox->Update(center);
    m_viewBox->GetShape()->SetFillColour(Colour(255, 0, 0, 128));
}

void SFCamera::Update()
{
    const float posX = 0.f;
    m_camera.setCenter({ posX + (GameConstants::ScreenDim.x * 0.5f), m_camera.getCenter().y });
    m_viewBox->Update(m_camera.getCenter());
}

void SFCamera::Reset(IRenderer* renderer)
{
    Update();

    if (renderer)
    {
        // Downcast to SFML window implementation (safe only if this camera is used with SFML)
        auto* sfmlWindow = static_cast<sf::RenderWindow*>(renderer->GetWindow()->GetNativeHandle());
        if (sfmlWindow)
            sfmlWindow->setView(m_camera);
    }
}

void SFCamera::RenderDebug(IRenderer* renderer)
{
    m_viewBox->Render(renderer);
}

bool SFCamera::IsInView(IBoundingVolume* volume)
{
    return m_viewBox->Intersects(volume);
}

bool SFCamera::CheckVerticalBounds(IBoundingVolume* volume)
{
    auto box = dynamic_cast<BoundingBox<SFRect>*>(volume);
    if (box)
    {
        const float cameraBottom = m_camera.getCenter().y + (GameConstants::ScreenDim.y * 0.5f);
        return box->GetPosition().y > (cameraBottom - (box->GetExtents().y * 2.f));
    }

    return false;
}
