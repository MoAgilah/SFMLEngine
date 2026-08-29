#include "SFDrawables.h"

#include "../Resources/SFShader.h"
#include <Utilities/Guards.h>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

template <typename T>
void SFDrawables<T>::Render(IRenderer* renderer)
{
    if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
        return;

    auto* drawable = this->GetPrimaryDrawable();
    if (!CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
        return;

    auto* win = renderer->GetWindow();
    if (!CheckNotNull(win, "Invalid Pointer 'win'"))
        return;

    auto* sfw = static_cast<sf::RenderWindow*>(win->GetNativeHandle());
    if (!CheckNotNull(sfw, "Invalid Pointer 'sfw'"))
        return;

    sfw->draw(*drawable);
}

template<typename T>
void SFDrawables<T>::Render(IRenderer* renderer, IShader* shader)
{
    if (!CheckNotNull(renderer, "Invalid Pointer 'renderer'"))
        return;

    auto* drawable = this->GetPrimaryDrawable();
    if (!CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
        return;

    auto* win = renderer->GetWindow();
    if (!CheckNotNull(win, "Invalid Pointer 'win'"))
        return;

    auto* sfw = static_cast<sf::RenderWindow*>(win->GetNativeHandle());
    if (!CheckNotNull(sfw, "Invalid Pointer 'sfw'"))
        return;

    auto* sfShader = dynamic_cast<SFShader*>(shader);
    if (!CheckNotNull(sfShader, "Invalid Pointer 'sfShader'"))
        return;

    sf::RenderStates states;
    states.shader = &sfShader->GetNativeShader();

    sfw->draw(*drawable, states);
}

template <typename T>
void SFDrawables<T>::SetPosition(const Vector2f& pos)
{
    auto* drawable = this->GetPrimaryDrawable();
    if (!CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
        return;

    drawable->setPosition(pos);
}

template <typename T>
Vector2f SFDrawables<T>::GetPosition()
{
    auto* drawable = this->GetPrimaryDrawable();
    if (CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
        return Vector2f(drawable->getPosition());

    return {};
}

template <typename T>
void SFDrawables<T>::OffsetPosition(const Vector2f& delta)
{
    auto* drawable = this->GetPrimaryDrawable();
    if (!CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
        return;

    drawable->move(delta);
}

template <typename T>
void SFDrawables<T>::SetScale(const Vector2f& scl)
{
    this->m_scale = scl;

    auto* drawable = this->GetPrimaryDrawable();
    if (!CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
        return;

    drawable->setScale(scl);
}

template <typename T>
Vector2f SFDrawables<T>::GetScale()
{
    return this->m_scale;
}

template <typename T>
Vector2f SFDrawables<T>::GetOrigin()
{
    auto* drawable = this->GetPrimaryDrawable();
    if (CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
        return Vector2f(drawable->getOrigin());

    return {};
}

template <typename T>
void SFDrawables<T>::SetOrigin(const Vector2f& ori)
{
    auto* drawable = this->GetPrimaryDrawable();
    if (!CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
        return;

    drawable->setOrigin(ori);
}

template<typename T>
Vector2f SFDrawables<T>::GetSize()
{
    return ITransforms::GetSize();
}

template<typename T>
void SFDrawables<T>::SetSize(const Vector2f& size)
{
   ITransforms::SetSize(size);
}

template<typename T>
Vector2f SFDrawables<T>::GetGlobalSize()
{
    auto* drawable = this->GetPrimaryDrawable();
    if (CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
    {
        auto bounds = drawable->getGlobalBounds();
        return Vector2f(bounds.size);
    }

    return {};
}

template<typename T>
Vector2f SFDrawables<T>::GetLocalSize()
{
    auto* drawable = this->GetPrimaryDrawable();
    if (CheckNotNull(drawable, "Invalid Pointer 'drawable'"))
    {
        auto bounds = drawable->getLocalBounds();
        return Vector2f(bounds.size);
    }

    return {};
}

template<typename T>
void SFDrawables<T>::SetLocalSize(const Vector2f& size)
{
    // Intentionally empty; depends on concrete SFML type
}

// Explicit instantiations for the SFML drawables you actually use
template class SFDrawables<sf::Sprite>;
template class SFDrawables<sf::Shape>;
template class SFDrawables<sf::Text>;
template class SFDrawables<sf::RectangleShape>;
template class SFDrawables<sf::CircleShape>;
template class SFDrawables<sf::ConvexShape>;
