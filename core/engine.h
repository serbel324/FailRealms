#pragma once

#include <vector>
#include <memory>

#include <util/vec2.h>
#include <core/graphics.h>
#include <core/controller.h>
#include <core/camera.h>

#include <SFML/Graphics.hpp>

#include <core/world.h>

using RenderWindowPtr = std::shared_ptr<sf::RenderWindow>;

/* Main class, contains renderer, event handlers and main logic */
class TEngine
{
public:
	TEngine();
	~TEngine();

private:
	TVec2<int> WindowSize;

	/* minimal time in ms for main_loop() iteration */
	float TickTime;


	TGraphics::SPtr Gr;
	std::shared_ptr<sf::RenderWindow> Window;

	TController::SPtr Control;


	/* ======== METHODS ======== */

	/* initialize SFML, create main Window */
	void SFMLInit();

	/* Set properties, load configs */
	void Config();

	/* reset all variables to initial values */
	void Init();

	/* update */
	void Tick();
	
	/* draw */
	void Render();

	/* handle Events */
	void Events();

	void KeyPressed(sf::Event::KeyEvent key);
	void MousePressed(sf::Event::MouseButtonEvent mouse);

	/* main loop iteration */
	void MainLoop();

	/* after main Window is closed */
	void Close();

private:
	TWorld World;
	TVec2i WorldSize;
	TCamera::SPtr MainCamera;
};