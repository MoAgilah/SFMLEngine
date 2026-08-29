#include "SFRenderer.h"

#include "SFWindow.h"
#include <Engine/Core/Constants.h>
#include <Engine/Interface/Renderer/IRenderable.h>
#include <Utilities/Guards.h>
#include <SFML/Graphics/RenderWindow.hpp>

namespace
{
    inline sf::RenderWindow* AsSF(void* p)
    {
        return reinterpret_cast<sf::RenderWindow*>(p);
    }
}

bool SFRenderer::Initialise(const Vector2f& screenDims, const std::string& title)
{
    // Create a concrete window (still type-erased in the interface)
    m_window = std::make_shared<SFWindow>();
    if (!CheckNotNull(m_window.get(), "Invalid Pointer 'm_window'"))
        return false;

    if (m_window->Create(screenDims, title))
    {
        // Cache the native handle once (type-erased in the renderer’s header)
        m_nativeWindow = m_window->GetNativeHandle();
        return true;
    }

    return false;
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
    if (!CheckNotNull(object, "Invalid Pointer 'object'"))
        return;

    if (!CheckNotNull(m_window.get(), "Invalid Pointer 'm_window'"))
        return;

    object->Render(this);
}

void SFRenderer::Draw(IRenderable* object, IShader* shader)
{
    if (!CheckNotNull(object, "Invalid Pointer 'object'"))
        return;

    if (!CheckNotNull(shader, "Invalid Pointer 'shader'"))
        return;

    if (!CheckNotNull(m_window.get(), "Invalid Pointer 'm_window'"))
        return;

    object->Render(this, shader);
}

void SFRenderer::Present()
{
    auto* sfWindow = AsSF(m_nativeWindow);
    if (!CheckNotNull(sfWindow, "Invalid Pointer 'sfWindow'"))
        return;

    sfWindow->display();
}