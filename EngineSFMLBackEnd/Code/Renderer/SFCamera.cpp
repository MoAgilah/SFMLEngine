#include "SFCamera.h"

#include "../Drawables/SFShape.h"
#include <Engine/Collisions/BoundingBox.h>
#include <Engine/Core/Constants.h>
#include <Utilities/Guards.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

SFCamera::SFCamera()
    : ICamera(std::make_unique<BoundingBox<SFRect>>())
{
    const auto& screenDim = GameConstants::ScreenDim;
    const Vector2f center = screenDim * 0.5f;

    m_camera = std::make_unique<sf::View>();

    m_camera->setSize(screenDim);
    m_camera->setCenter(center);
    m_camera->setViewport({ {0.f, 0.f}, {1.f, 1.f} });

    auto sfBBox = static_cast<BoundingBox<SFRect>*>(m_viewBox.get());

    sfBBox->Reset(screenDim);
    sfBBox->Update(center);
    sfBBox->GetShape()->SetFillColour(Colour(255, 0, 0, 128));
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

sf::View* SFCamera::GetView()
{
    if (m_camera)
        return m_camera.get();

    return nullptr;
}