#include "SFDrawables.h"

#include "../Resources/SFShader.h"
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
    auto* drawable = this->GetPrimaryDrawable();
    if (!renderer || !drawable)
        return;

    INativeWindow* win = renderer->GetWindow();
    if (!win)
        return;

    auto* sfw = static_cast<sf::RenderWindow*>(win->GetNativeHandle());
    if (sfw)
        sfw->draw(*drawable);
}

template<typename T>
void SFDrawables<T>::Render(IRenderer* renderer, IShader* shader)
{
    auto* drawable = this->GetPrimaryDrawable();
    if (!renderer || !drawable)
        return;

    INativeWindow* win = renderer->GetWindow();
    if (!win)
        return;

    //auto* sfw = static_cast<sf::RenderWindow*>(win->GetNativeHandle());
    //if (sfw)
    //{
    //    if (auto* sfShader = dynamic_cast<SFShader*>(shader))
    //    {
    //        if (auto& native = sfShader->GetNativeShader()) // sf::Shader*
    //        {
    //            sf::RenderStates states;
    //            states.shader = native;
    //            sfw->draw(*drawable, states);               // draw with states
    //        }
    //    }
    //}
}

template <typename T>
void SFDrawables<T>::SetPosition(const Vector2f& pos)
{
    if (auto* d = this->GetPrimaryDrawable())
        d->setPosition(pos);
}

template <typename T>
Vector2f SFDrawables<T>::GetPosition()
{
    if (auto* d = this->GetPrimaryDrawable())
        return Vector2f(d->getPosition());
    return {};
}

template <typename T>
void SFDrawables<T>::OffsetPosition(const Vector2f& delta)
{
    if (auto* d = this->GetPrimaryDrawable())
        d->move(delta);
}

template <typename T>
void SFDrawables<T>::SetScale(const Vector2f& scl)
{
    this->m_scale = scl;
    if (auto* d = this->GetPrimaryDrawable())
        d->setScale(scl);
}

template <typename T>
Vector2f SFDrawables<T>::GetScale()
{
    return this->m_scale;
}

template <typename T>
Vector2f SFDrawables<T>::GetOrigin()
{
    if (auto* d = this->GetPrimaryDrawable())
        return Vector2f(d->getOrigin());
    return {};
}

template <typename T>
void SFDrawables<T>::SetOrigin(const Vector2f& ori)
{
    if (auto* d = this->GetPrimaryDrawable())
        d->setOrigin(ori);
}

template <typename T>
Vector2f SFDrawables<T>::GetSize()
{
    if (auto* d = this->GetPrimaryDrawable())
    {
        auto bounds = d->getGlobalBounds();
        return Vector2f(bounds.size);
    }
    return {};
}

template <typename T>
void SFDrawables<T>::SetSize(const Vector2f& /*size*/)
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
