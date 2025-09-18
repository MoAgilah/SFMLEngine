#pragma once
#include <Engine/Interface/Renderer/IWindow.h>
#include <Utilities/Vector.h>
#include <memory>
#include <string>

// Forward declare instead of including SFML headers
namespace sf { class RenderWindow; }

class SFWindow : public INativeWindow
{
public:
    bool Create(const Vector2f& screenDims, const std::string& title) override;
    void PollEvents() override;
    bool ShouldClose() const override;
    void Close() override;
    void* GetNativeHandle() override;

private:

    bool m_shouldClose = false;
    std::shared_ptr<sf::RenderWindow> m_window; // opaque SFML detail
};
