#pragma once

#include <Singleton.hpp>
#include <Logger.hpp>
#include <GameManager.hpp>
#include <VariousUI.hpp>

#include <Graphics/Window.hpp>
#include <Graphics/Events.hpp>
#include <Flashlight.hpp>

class EventHandler
{
public:
	void eventQueue(Graphics::Window* window);

private:
	GameManager* gameManager = &Singleton<GameManager>::GetInstance();
	VariousUI* variousUI = &Singleton<VariousUI>::GetInstance();
};