#include "SFWindow.h"

#include <Engine/Core/Constants.h>
#include <Engine/Core/GameManager.h>


bool SFWindow::Create(const Vector2f& screemDims, const std::string& title)
{
	m_window = std::make_shared<sf::RenderWindow>();
	m_window->create(sf::VideoMode(sf::Vector2u(static_cast<int>(screemDims.x), static_cast<int>(screemDims.y))), title);
	m_window->setFramerateLimit(static_cast<int>(GameConstants::FPS));
	return m_window->isOpen();
}

void SFWindow::PollEvents()
{
	while (auto event = m_window->pollEvent())
	{
		if (event.has_value())
		{
			if (event->is<sf::Event::Closed>())
			{
				Close();
			}
			else if (auto keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					Close();

				GameManager::Get()->GetInputManager()->ProcessPlatformKeyPress(const_cast<sf::Keyboard::Key*>(&keyPressed->code));
			}
			else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				GameManager::Get()->GetInputManager()->ProcessPlatformKeyRelease(const_cast<sf::Keyboard::Key*>(&keyReleased->code));
			}
		}
	}
}

bool SFWindow::ShouldClose() const
{
	return m_shouldClose || !m_window->isOpen();
}

void SFWindow::Close()
{
	if (m_window)
		m_window->close();

	m_shouldClose = true;
}

void* SFWindow::GetNativeHandle()
{
	return static_cast<void*>(m_window.get());
}

sf::RenderWindow* SFWindow::GetWindow()
{
	return m_window.get();
}
