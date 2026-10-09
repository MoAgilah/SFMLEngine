#include "SFWindow.h"

#include <Engine/Core/Constants.h>
#include <Engine/Core/GameManager.h>
#include <Utilities/Guards.h>
#include <SFML/Graphics.hpp>

bool SFWindow::Create(const Vector2u& screenDims, const std::string& title)
{
	if (screenDims.x == 0 || screenDims.y == 0)
		return false;

	auto newWindow = std::make_shared<sf::RenderWindow>();

	newWindow->create(
		sf::VideoMode(sf::Vector2u(screenDims.x, screenDims.y)),
		title
	);

	if (!newWindow->isOpen())
		return false;

	newWindow->setFramerateLimit(static_cast<unsigned int>(GameConstants::FPS));

	m_window = std::move(newWindow);
	m_shouldClose = false;

	return true;
}

void SFWindow::PollEvents()
{
	if (!CheckNotNull(m_window.get(), "Invalid Pointer 'm_window'"))
		return;

	while (auto event = m_window->pollEvent())
	{
		if (event->is<sf::Event::Closed>())
		{
			Close();
			break;
		}
		else if (event->is<sf::Event::KeyPressed>() ||
			event->is<sf::Event::KeyReleased>())
		{
			const auto keyPressed = event->getIf<sf::Event::KeyPressed>();

			if (keyPressed)
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
				{
					Close();
					break;
				}
			}

			auto* gameMgr = GameManager::Get();
			if (!CheckNotNull(gameMgr, "Invalid Pointer 'gameMgr' from GameManager::Get()"))
				continue;

			auto* inputMgr = gameMgr->GetInputManager();
			if (!CheckNotNull(inputMgr, "Invalid Pointer 'inputMgr' from gameMgr->GetInputManager()"))
				continue;

			if (keyPressed)
			{
				inputMgr->ProcessPlatformKeyPress(
					static_cast<int>(keyPressed->code));
			}
			else if (const auto* keyReleased = event->getIf<sf::Event::KeyReleased>())
			{
				inputMgr->ProcessPlatformKeyRelease(
					static_cast<int>(keyReleased->code));
			}
		}
	}
}

bool SFWindow::ShouldClose() const
{
	if (!CheckNotNull(m_window.get(), "Invalid Pointer 'm_window'"))
		return false;

	return m_shouldClose || !m_window->isOpen();
}

void SFWindow::Close()
{
	if (!CheckNotNull(m_window.get(), "Invalid Pointer 'm_window'"))
		return;

	m_window->close();
	m_shouldClose = true;
}

void* SFWindow::GetNativeHandle()
{
	return static_cast<void*>(m_window.get());
}