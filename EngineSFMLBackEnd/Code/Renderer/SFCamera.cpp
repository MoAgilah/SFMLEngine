#include "SFCamera.h"

#include "../Drawables/SFShape.h"
#include <Engine/Collisions/BoundingBox.h>
#include <Engine/Core/Constants.h>
#include <Utilities/Utils.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

SFCamera::SFCamera()
{
    const auto& screenDim = GameConstants::ScreenDim;
    const Vector2f center = screenDim * 0.5f;

    m_camera = std::make_unique<sf::View>();
    ENSURE_VALID(m_camera);
    m_camera->setSize(screenDim);
    m_camera->setCenter(center);
    m_camera->setViewport({ {0.f, 0.f}, {1.f, 1.f} });

    m_viewBox = std::make_shared<BoundingBox<SFRect>>(screenDim, center);
    ENSURE_VALID(m_viewBox);
    m_viewBox->Update(center);
    m_viewBox->GetShape()->SetFillColour(Colour(255, 0, 0, 128));
}

SFCamera::~SFCamera() = default;

void SFCamera::Update()
{
    ENSURE_VALID(m_camera);
    ENSURE_VALID(m_viewBox);

    const float posX = 0.f;
    m_camera->setCenter({ posX + (GameConstants::ScreenDim.x * 0.5f), m_camera->getCenter().y });
    m_viewBox->Update(m_camera->getCenter());
}

void SFCamera::Reset(IRenderer* renderer)
{
    ENSURE_VALID(renderer);
    ENSURE_VALID(m_camera);

    Update();

    // Downcast to SFML window implementation (safe only if this camera is used with SFML)
    auto* sfmlWindow = static_cast<sf::RenderWindow*>(renderer->GetWindow()->GetNativeHandle());
    if (sfmlWindow && m_camera)
        sfmlWindow->setView(*m_camera);
}

void SFCamera::RenderDebug(IRenderer* renderer)
{
    ENSURE_VALID(renderer);
    ENSURE_VALID(m_viewBox);

    m_viewBox->Render(renderer);
}

bool SFCamera::IsInView(IBoundingVolume* volume)
{
    ENSURE_VALID_RET(volume, false);
    ENSURE_VALID_RET(m_viewBox, false);

    return m_viewBox->Intersects(volume);
}

bool SFCamera::CheckVerticalBounds(IBoundingVolume* volume)
{
    ENSURE_VALID_RET(volume, false);
    ENSURE_VALID_RET(m_viewBox, false);

    auto box = dynamic_cast<BoundingBox<SFRect>*>(volume);
    if (box)
    {
        const float cameraBottom = m_camera->getCenter().y + (GameConstants::ScreenDim.y * 0.5f);
        return box->GetPosition().y > (cameraBottom - (box->GetExtents().y * 2.f));
    }

    return false;
}

sf::View* SFCamera::GetView()
{
    if (m_camera)
        return m_camera.get();

    return nullptr;
}