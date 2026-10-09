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

bool SFRenderer::Initialise(const Vector2u& screenDims, const std::string& title)
{
    auto newWindow = std::make_shared<SFWindow>();

    if (!newWindow->Create(screenDims, title))
        return false;

    m_window = std::move(newWindow);
    m_nativeWindow = m_window->GetNativeHandle();

    return true;
}

void SFRenderer::PollWindowEvents()
{
    if (!CheckNotNull(m_window.get(), "Invalid Pointer 'm_window'"))
        return;

    m_window->PollEvents();
}

void SFRenderer::Clear()
{
    auto* sfWindow = AsSF(m_nativeWindow);

    if (!CheckNotNull(sfWindow, "Invalid Pointer 'sfWindow'"))
        return;

    sfWindow->clear(GameConstants::WindowColour);
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