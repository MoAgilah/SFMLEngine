#include "SFFramework.h"

#include "../Input/SFKeyConverter.h"
#include "../Renderer/SFCamera.h"
#include "../Renderer/SFRenderer.h"

SFFramework::SFFramework()
{
	m_gameMgr.SetInputManager(std::make_shared<InputManager>(std::make_shared<SFKeyConverter>()));
	m_gameMgr.SetCamera(std::make_shared<SFCamera>());
	m_gameMgr.SetRenderer(std::make_shared<SFRenderer>());
}