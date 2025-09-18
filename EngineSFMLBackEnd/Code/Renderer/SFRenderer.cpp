#include "SFRenderer.h"

#include "SFWindow.h"
#include <SFML/Graphics/RenderWindow.hpp>

#include <Engine/Core/Constants.h>
#include <Engine/Interface/Renderer/IRenderable.h>

namespace
{
    inline sf::RenderWindow* AsSF(void* p)
    {
        return reinterpret_cast<sf::RenderWindow*>(p);
    }
}

void SFRenderer::Initialise(const Vector2f& screenDims, const std::string& title)
{
    // Create a concrete window (still type-erased in the interface)
    m_window = std::make_shared<SFWindow>();
    m_window->Create(screenDims, title);

    // Cache the native handle once (type-erased in the renderer’s header)
    m_nativeWindow = m_window ? m_window->GetNativeHandle() : nullptr;
}

void SFRenderer::PollWindowEvents()
{
    if (m_window)
        m_window->PollEvents();
}

void SFRenderer::Clear()
{
    if (auto* sfw = AsSF(m_nativeWindow))
        sfw->clear(GameConstants::WindowColour);
}

void SFRenderer::Draw(IRenderable* object)
{
    if (!object || !m_window)
        return;

    object->Render(this);
}

void SFRenderer::Present()
{
    if (auto* sfw = AsSF(m_nativeWindow))
        sfw->display();
}