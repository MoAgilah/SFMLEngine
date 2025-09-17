#pragma once


#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <Engine/Interface/Renderer/IWindow.h>
#include <Utilities/Vector.h>

class SFWindow : public IWindow<sf::RenderWindow>
{
public:
    bool Create(const Vector2f& screemDims, const std::string& title) override;
    void PollEvents() override;
    bool ShouldClose() const override;
    void Close() override;
    void* GetNativeHandle() override;

    sf::RenderWindow* GetWindow();

private:
    bool m_shouldClose = false;
};
