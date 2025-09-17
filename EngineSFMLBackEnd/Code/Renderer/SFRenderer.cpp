#include "SFRenderer.h"

#include <Engine/Core/Constants.h>
#include <Engine/Core/GameManager.h>
#include <Engine/Interface/Renderer/IRenderable.h>

void SFRenderer::Initialise(const Vector2f& screenDims, const std::string& title)
{
	m_window = std::make_shared<SFWindow>();
    m_window->Create(screenDims, title);
}

void SFRenderer::PollWindowEvents()
{
	m_window->PollEvents();
}

void SFRenderer::Clear()
{
    if (auto* windowHandle = m_window.get())
    {
        auto* sfWindow = static_cast<sf::RenderWindow*>(windowHandle->GetNativeHandle());
        if (sfWindow)
            sfWindow->clear(GameConstants::WindowColour);
    }
}

void SFRenderer::Draw(IRenderable* object)
{
    if (!object || !m_window)
        return;

    object->Render(this);
}

void SFRenderer::Present()
{
    if (auto* windowHandle = m_window.get())
    {
        auto* sfWindow = static_cast<sf::RenderWindow*>(windowHandle->GetNativeHandle());
        if (sfWindow)
            sfWindow->display();
    }
}