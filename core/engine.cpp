#include "engine.h"

#include <fstream>
#include <cstdlib>
#include <ctime>

#include <chrono>

TEngine::TEngine()
{
	Config();
	SFMLInit();

	Gr = std::make_shared<TGraphics>(Window, WindowSize);
	TCamera::SPtr cam = std::make_shared<TCamera>(WindowSize / 2, 0, 1); /* TCamera with center in upper left Angle */
	Gr->ApplyCamera(cam);

	Init();

	while (Window->isOpen())
	{
		MainLoop();
	}

	Close();
}

TEngine::~TEngine()
{
}

void TEngine::SFMLInit()
{
	Window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(WindowSize.X, WindowSize.Y), 
		"Unnamed", 
		sf::Style::Close);
}

void TEngine::Config()
{
	/* default screen resolution is 800x800 */
	WindowSize = TVec2<int>(1200, 1200);
	WorldSize = {200, 200};
	TickTime = 10;
}

void TEngine::Init()
{
	Control = std::make_shared<TController>();
	MainCamera = std::make_shared<TCamera>();
	Gr->SetCamera(MainCamera);

	World.Generate(WorldSize);
}

void TEngine::Tick()
{
	/// World.Generate(TVec2(800, 800));

	World.Tick(200);
}

void TEngine::Render()
{
	Gr->SetFillColor(TColor(20));
	Gr->Fill();
	Gr->UpdateViewport();

	World.Render(Gr, 6);

	Gr->Present();
}


void TEngine::Events()
{
	sf::Event e;
	while (Window->pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::Closed:
			Window->close();
			break;
		case sf::Event::KeyPressed:
			KeyPressed(e.key);
			Control->KeyPressed(e.key);
			if (e.key.code == sf::Keyboard::Space) {
				World.Generate(WorldSize);
			}
			break;
		case sf::Event::KeyReleased:
			Control->KeyPressed(e.key);
			break;
		case sf::Event::MouseButtonPressed:
			Control->MousePressed(e.mouseButton);
			break;
		case sf::Event::MouseButtonReleased:
			Control->MouseReleased(e.mouseButton);
			break;
		case sf::Event::MouseMoved:
			Control->MouseMoved(e.mouseMove);
			break;
		default:
			break;
		}
	}
}

void TEngine::KeyPressed(sf::Event::KeyEvent key)
{
	if (key.code == sf::Keyboard::Escape)
	{
		Window->close();
	}
}

void TEngine::MousePressed(sf::Event::MouseButtonEvent mouse)
{
}

void TEngine::MainLoop()
{
	sf::Clock clock;

	Events();
	Tick();
	Render();

	sf::Time t = clock.getElapsedTime();

	if (t.asMilliseconds() < TickTime)
	{
		sf::sleep(sf::milliseconds(TickTime - t.asMilliseconds()));
	}
}

void TEngine::Close()
{
}
