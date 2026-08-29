#include "SFCamera.h"

#include "../Drawables/SFShape.h"
#include <Engine/Collisions/BoundingBox.h>
#include <Engine/Core/Constants.h>
#include <Utilities/Guards.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

SFCamera::SFCamera()
{
    const auto& screenDim = GameConstants::ScreenDim;
    const Vector2f center = screenDim * 0.5f;

    m_camera = std::make_unique<sf::View>();
    if (!CheckNotNull(m_camera.get(), "Invalid Pointer 'm_camera'"))
        throw std::invalid_argument("SFCamera requires a valid camera");

    m_camera->setSize(screenDim);
    m_camera->setCenter(center);
    m_camera->setViewport({ {0.f, 0.f}, {1.f, 1.f} });



    m_viewBox = std::make_shared<BoundingBox<SFRect>>(screenDim, center);
    if (!CheckNotNull(m_viewBox.get(), "Invalid Pointer 'm_viewBox'"))
        throw std::invalid_argument("SFCamera requires a valid BoundingBox<SFRect>");

    m_viewBox->Update(center);
    m_viewBox->GetShape()->SetFillColour(Colour(255, 0, 0, 128));
}

SFCamera::~SFCamera() = default;

void SFCamera::Update()
{
    if (!CheckNotNull(m_camera.get(), "Invalid Pointer 'm_camera'"))
        return;

    if (!CheckNotNull(m_viewBox.get(), "Invalid Pointer 'm_viewBox'"))
        return;

    float posX = 0.f;

    if (m_toFollow)
    {
        posX = m_toFollow->GetPosition().x - GameConstants::ScreenDim.x * 0.5f;

        if (posX < 0)
            posX = 0;
    }

    m_camera->setCenter({ posX + (GameConstants::ScreenDim.x * 0.5f), m_camera->getCenter().y });
    m_viewBox->Update(m_camera->getCenter());
}

void SFCamera::Reset(IRenderer* renderer)
{
    if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
        return;

    if (!CheckNotNull(m_camera.get(), "Invalid Pointer 'm_camera'"))
        return;

    // Downcast to SFML window implementation (safe only if this camera is used with SFML)
    auto* sfmlWindow = static_cast<sf::RenderWindow*>(renderer->GetWindow()->GetNativeHandle());
    if (sfmlWindow && m_camera)
        sfmlWindow->setView(*m_camera);
}

void SFCamera::RenderDebug(IRenderer* renderer)
{
    if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
        return;

    if (!CheckNotNull(m_viewBox.get(), "Invalid Pointer 'm_viewBox'"))
        return;

    m_viewBox->Render(renderer);
}

bool SFCamera::IsInView(IBoundingVolume* volume)
{
    if (!CheckNotNull(volume, "Invalid Pointer 'volume'"))
        return false;

    if (!CheckNotNull(m_viewBox.get(), "Invalid Pointer 'm_viewBox'"))
        return false;

    return m_viewBox->Intersects(volume);
}

bool SFCamera::CheckVerticalBounds(IBoundingVolume* volume)
{
    if (!CheckNotNull(volume, "Invalid Pointer 'volume'"))
        return false;

    if (!CheckNotNull(m_viewBox.get(), "Invalid Pointer 'm_viewBox'"))
        return false;

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