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
    if (!m_toFollow)
        return;

    const float halfWidth = m_camera->getSize().x * 0.5f;

    float posX = m_toFollow->GetPosition().x - halfWidth;

    if (posX < 0.f)
        posX = 0.f;

    m_camera->setCenter({ posX + halfWidth, m_camera->getCenter().y });
    m_viewBox->Update(m_camera->getCenter());
}

void SFCamera::Reset(IRenderer* renderer)
{
    if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
        return;

    auto* window = renderer->GetWindow();
    if (!CheckNotNull(window, "Invalid Pointer 'window'"))
        return;

    auto* sfWindow = static_cast<sf::RenderWindow*>(window->GetNativeHandle());
    if (!CheckNotNull(sfWindow, "Invalid Pointer 'sfWindow'"))
        return;

    sfWindow->setView(*m_camera);
}

sf::View* SFCamera::GetView()
{
    return m_camera.get();
}